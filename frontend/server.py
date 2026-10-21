#!/usr/bin/env python3
"""
Simple presentation frontend for the
Cybersecurity Threat Detection & Incident Response Simulator.

What it does
------------
- Serves a single web page (index.html) at http://localhost:8000
- When you click "Run Simulation", it compiles the C++ project (only if
  needed) and runs the real ./simulator binary, then streams the console
  output back to the browser where it is shown nicely formatted.

It uses ONLY the Python standard library - no pip installs, no frameworks.
Nothing about the simulation changes: this is just a viewer/launcher for the
existing C++ program so it is pleasant to present.

Usage
-----
    python3 frontend/server.py            # then open http://localhost:8000
    python3 frontend/server.py 9000       # use a different port

This does not perform any real security action. The C++ program it runs is a
safe simulation.
"""

import glob
import json
import os
import subprocess
import sys
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer

# ---------------------------------------------------------------------------
# Paths: the project root is the folder ABOVE this frontend/ folder.
# ---------------------------------------------------------------------------
FRONTEND_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(FRONTEND_DIR)
SRC_DIR = os.path.join(PROJECT_ROOT, "src")
BINARY = os.path.join(PROJECT_ROOT, "simulator")
INDEX_HTML = os.path.join(FRONTEND_DIR, "index.html")


def source_files():
    """All C++ source files that make up the simulator."""
    return sorted(glob.glob(os.path.join(SRC_DIR, "*.cpp")))


def needs_build():
    """True if the binary is missing or older than any source file."""
    if not os.path.exists(BINARY):
        return True
    bin_mtime = os.path.getmtime(BINARY)
    for src in source_files():
        if os.path.getmtime(src) > bin_mtime:
            return True
    return False


def build():
    """
    Compile the project with g++ (C++17).
    Returns (ok: bool, log: str).
    """
    cmd = ["g++", "-std=c++17", "-Wall", "-o", BINARY] + source_files()
    try:
        proc = subprocess.run(
            cmd,
            cwd=PROJECT_ROOT,
            capture_output=True,
            text=True,
            timeout=120,
        )
    except FileNotFoundError:
        return False, (
            "g++ was not found on this machine.\n"
            "On macOS install the command line tools with:\n"
            "    xcode-select --install"
        )
    except subprocess.TimeoutExpired:
        return False, "Compilation timed out after 120 seconds."

    log = (proc.stdout or "") + (proc.stderr or "")
    return proc.returncode == 0, log.strip()


def run_simulator():
    """
    Run the compiled simulator and capture its console output.
    Returns a dict ready to be sent back as JSON.
    """
    built = False
    if needs_build():
        ok, log = build()
        built = True
        if not ok:
            return {
                "ok": False,
                "stage": "build",
                "built": True,
                "buildLog": log,
                "output": "",
            }

    try:
        proc = subprocess.run(
            [BINARY],
            cwd=PROJECT_ROOT,
            capture_output=True,
            text=True,
            timeout=30,
        )
    except Exception as exc:  # noqa: BLE001 - report any run failure plainly
        return {
            "ok": False,
            "stage": "run",
            "built": built,
            "buildLog": "",
            "output": f"Failed to run the simulator: {exc}",
        }

    return {
        "ok": proc.returncode == 0,
        "stage": "run",
        "built": built,
        "buildLog": "",
        "output": (proc.stdout or "") + (proc.stderr or ""),
        "exitCode": proc.returncode,
    }


class Handler(BaseHTTPRequestHandler):
    # Quieter logging - one tidy line per request.
    def log_message(self, fmt, *args):
        sys.stderr.write("  %s - %s\n" % (self.address_string(), fmt % args))

    def _send(self, code, body, content_type):
        if isinstance(body, str):
            body = body.encode("utf-8")
        self.send_response(code)
        self.send_header("Content-Type", content_type)
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def do_GET(self):
        # SECURITY: this server exposes a STRICT allow-list of routes only.
        # No part of the request (path, query string, headers or body) is
        # ever passed to a shell or used to build a command line. The
        # /api/run route always runs the SAME fixed binary with NO
        # arguments and shell=False, so a client cannot influence what is
        # executed - arbitrary command execution is not possible.
        path = self.path.split("?", 1)[0]  # ignore any query string

        if path in ("/", "/index.html"):
            try:
                with open(INDEX_HTML, "r", encoding="utf-8") as f:
                    self._send(200, f.read(), "text/html; charset=utf-8")
            except FileNotFoundError:
                self._send(500, "index.html not found next to server.py",
                           "text/plain")
            return

        if path == "/api/run":
            result = run_simulator()
            self._send(200, json.dumps(result), "application/json")
            return

        # Anything else is rejected. (Other HTTP methods such as POST/PUT
        # are not implemented, so they return 501 automatically.)
        self._send(404, "Not found", "text/plain")


def main():
    # Render (and most hosting platforms) tell the app which port to use
    # through the PORT environment variable. Default to 10000, which is
    # Render's default web-service port. An optional command-line argument
    # overrides it for convenient local use.
    port = int(os.environ.get("PORT", "10000"))
    if len(sys.argv) > 1:
        try:
            port = int(sys.argv[1])
        except ValueError:
            print(f"Port argument must be a number. Using {port}.")

    # Bind all interfaces so the server is reachable from outside the
    # container (required on Render). Locally you still open localhost.
    host = "0.0.0.0"

    server = ThreadingHTTPServer((host, port), Handler)
    print("=" * 56)
    print(" Cybersecurity Simulator - presentation frontend")
    print("=" * 56)
    print(f" Project root : {PROJECT_ROOT}")
    print(f" Listening on : {host}:{port}")
    print(f" Local URL    : http://localhost:{port}")
    print(" Press Ctrl+C to stop.")
    print("=" * 56)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        print("\nStopping server. Bye!")
        server.server_close()


if __name__ == "__main__":
    main()
