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
        assert "Simulation completed safely." in result.stdout
        outputs[scenario] = result.stdout

    assert "Rejected invalid event" in outputs["validation-errors"]
    assert "Rejected invalid event" not in outputs["attack-only"]
    assert "UNKNOWN_ACTION" in outputs["response-failure"]
    assert "Synchronized events processed: 8" in outputs["high-volume"]

    invalid = subprocess.run(
        [binary, "not-allowed"], cwd=ROOT, capture_output=True, text=True
    )
    assert invalid.returncode == 2

print("All public scenarios passed.")
