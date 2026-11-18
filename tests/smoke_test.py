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
    assert "Severity Score  : 4 (calculated)" in outputs["full-demo"]
    assert "Risk Level  : HIGH (4)" in outputs["full-demo"]
    assert "Risk Level  : CRITICAL (5)" in outputs["high-volume"]

    invalid = subprocess.run(
        [binary, "not-allowed"], cwd=ROOT, capture_output=True, text=True
    )
    assert invalid.returncode == 2

    portal_login = subprocess.run(
        [
            binary, "attack-only", "portal-login", "teacher-demo",
            "failed", "3", "203.0.113.50",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    assert portal_login.returncode == 0, portal_login.stderr
    assert "Portal event accepted: incorrect login" in portal_login.stdout
    assert "Synchronized events processed: 6" in portal_login.stdout
    assert "Severity Score  : 4 (calculated)" in portal_login.stdout

    portal_network = subprocess.run(
        [
            binary, "attack-only", "portal-network", "443", "UDP",
            "198.51.100.10",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    assert portal_network.returncode == 0, portal_network.stderr
    assert "Portal event accepted: UDP connection to port 443" in portal_network.stdout
    assert "Severity Score  : 1 (calculated)" in portal_network.stdout

print("All public scenarios passed.")
