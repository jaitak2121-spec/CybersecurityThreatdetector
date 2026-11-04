# Problem Statement

Security systems receive events such as login attempts and network
connections. Analysts need a safe way to understand how those events are
validated, checked against rules, classified, investigated, and handled.

This project simulates that complete path. A device supplies login and network
events. Invalid events are rejected with custom exceptions. Valid events are
evaluated by detection rules, converted into threat records, and grouped into
an alert and incident when a suspicious pattern is found. Evidence is attached,
response actions are simulated, and all important results are logged and
reported.

The system is educational only. Blocking, locking, isolating, and resetting are
represented by status changes and console messages; no live security action is
performed.
