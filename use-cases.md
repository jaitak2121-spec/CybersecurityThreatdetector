# Use Cases

## UC-00 — Run a public simulation scenario

**Actor:** Visitor or security analyst

1. The visitor selects one of the predefined datasets or error paths.
2. The public server validates the scenario name against its allow-list.
3. The server runs the simulator with a time and concurrency limit.
4. The frontend displays scenario-specific data, errors, log entries, and report totals.
5. The frontend compares the new summary with the previous run in the same browser session.

**Alternate:** Unknown scenarios return an error and never reach the executable.

## UC-01 — Process security events

**Actor:** Event source

**Precondition:** A device and detector configuration exist.

**Postcondition:** Each valid event is logged and evaluated.

1. The event source submits a login or network event.
2. The system validates the event id, type, and severity.
3. The system stores and displays the valid event polymorphically.
4. Two monitoring threads process separate event ranges and update synchronized metrics.
5. The main flow joins both workers before reading their results.
6. The detector evaluates the event using enabled rules.
7. The system records the resulting threat and audit entry.

**Alternate: invalid input:** A custom exception rejects the event, RAII cleanup
runs, and the validation failure is logged. The invalid event is not detected.

## UC-02 — Investigate and create an incident

**Actor:** Security analyst

**Precondition:** A serious threat has produced an alert.

**Postcondition:** An open incident contains its alert and evidence.

1. The analyst reviews the alert and threat.
2. The analyst escalates the alert.
3. The system creates an incident and links the alert.
4. The analyst attaches authentication and network evidence.
5. The system records the incident.

**Alternate: false positive:** The analyst calls `markFalsePositive(reason)`;
the alert closes and no incident is required.

## UC-03 — Respond to an incident

**Actor:** Security analyst

**Precondition:** An investigated incident exists.

**Postcondition:** Every simulated action and outcome is stored and logged.

1. The analyst chooses a response action.
2. The incident executes it against the simulated target.
3. Successful actions update their status and may isolate the device.
4. The incident becomes contained after a successful response.
5. The system logs the outcome and includes it in the report.

**Alternate: unsupported action:** The action is marked `FAILED`, recorded, and
the remaining workflow continues safely.
