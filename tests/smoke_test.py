#!/usr/bin/env python3
"""Compile once and verify every public simulation scenario."""

import subprocess
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SCENARIOS = (
    "full-demo",
    "attack-only",
    "validation-errors",
    "response-failure",
    "high-volume",
)


with tempfile.TemporaryDirectory() as directory:
    binary = Path(directory) / "simulator"
    sources = sorted(str(path) for path in (ROOT / "src").glob("*.cpp"))
    subprocess.run(
        ["g++", "-std=c++17", "-Wall", "-pthread", "-o", binary, *sources],
        cwd=ROOT,
        check=True,
    )

    outputs = {}
    for scenario in SCENARIOS:
        result = subprocess.run(
            [binary, scenario], cwd=ROOT, capture_output=True, text=True
        )
        assert result.returncode == 0, result.stderr
        assert f"Scenario: {scenario}" in result.stdout
        assert "Severity scoring is automatic" in result.stdout
        assert "Simulation completed safely." in result.stdout
        outputs[scenario] = result.stdout

    assert "Rejected invalid event" in outputs["validation-errors"]
    assert "Rejected invalid event" not in outputs["attack-only"]
    assert "UNKNOWN_ACTION" in outputs["response-failure"]
    assert "Synchronized events processed: 8" in outputs["high-volume"]
    assert "Severity Score  : 3 (calculated)" in outputs["full-demo"]
    assert "Severity Score  : 5 (calculated)" in outputs["full-demo"]
    assert "Risk Level  : MEDIUM (3)" in outputs["full-demo"]
    assert "Highest severity score  : 5" in outputs["full-demo"]
    assert "Risk Level  : HIGH (4)" in outputs["high-volume"]

    invalid = subprocess.run(
        [binary, "not-allowed"], cwd=ROOT, capture_output=True, text=True
    )
    assert invalid.returncode == 2

    portal_login = subprocess.run(
        [
            binary, "portal-event", "portal-login", "teacher-demo",
            "failed", "3", "203.0.113.50",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    assert portal_login.returncode == 0, portal_login.stderr
    assert "Portal event accepted: incorrect login" in portal_login.stdout
    assert "Synchronized events processed: 1" in portal_login.stdout
    assert "Severity Score  : 3 (calculated)" in portal_login.stdout
    assert "Threats detected        : 1" in portal_login.stdout
    assert "Highest severity score  : 3" in portal_login.stdout

    portal_success = subprocess.run(
        [
            binary, "portal-event", "portal-login", "teacher-demo",
            "success", "0", "203.0.113.50",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    assert portal_success.returncode == 0, portal_success.stderr
    assert "Severity Score  : 1 (calculated)" in portal_success.stdout
    assert "Synchronized events processed: 1" in portal_success.stdout
    assert "Threats detected        : 1" in portal_success.stdout
    assert "  HIGH                  : 0" in portal_success.stdout
    assert "Highest severity score  : 1" in portal_success.stdout
    assert "Alerts raised           : 0" in portal_success.stdout
    assert "Incidents created       : 0" in portal_success.stdout

    portal_network = subprocess.run(
        [
            binary, "portal-event", "portal-network", "443", "UDP",
            "198.51.100.10",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    assert portal_network.returncode == 0, portal_network.stderr
    assert "Portal event accepted: UDP connection to port 443" in portal_network.stdout
    assert "Severity Score  : 1 (calculated)" in portal_network.stdout
    assert "Highest severity score  : 1" in portal_network.stdout

    # All login thresholds and network flag combinations; protocols must score equally.
    for failures, locked, expected in [(1,0,2),(2,0,2),(3,0,3),(4,0,3),(5,0,4),(10,0,4),(5,1,5)]:
        result = subprocess.run(
            [binary, "portal-event", "portal-login", "admin", "failed", str(failures), "203.0.113.50", str(locked)],
            capture_output=True, text=True, check=True,
        )
        assert f"Highest severity score  : {expected}" in result.stdout
    for port in (22, 3389, 443):
        for attempts in (1, 3):
            for unauthorized in (0, 1):
                expected = 1 + 2 * (port in (22,3389)) + (attempts >= 3) + unauthorized
                for protocol in ("TCP", "UDP"):
                    result = subprocess.run(
                        [binary, "portal-event", "portal-network", str(port), protocol, "203.0.113.50", str(attempts), str(unauthorized)],
                        capture_output=True, text=True, check=True,
                    )
                    assert f"Highest severity score  : {expected}" in result.stdout

print("All public scenarios passed.")
