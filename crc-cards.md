# CRC Cards

| Class | Responsibilities | Main collaborators |
|---|---|---|
| `EventInfo` | Store and display a source IP | `SecurityEvent` |
| `SecurityEvent` | Validate and expose common event data; define polymorphic display/clone | `EventInfo`, exception hierarchy, `DetectionRule` |
| `LoginEvent` | Represent login outcome and username | `SecurityEvent`, `DetectionRule`, `ThreatDetector` |
| `NetworkEvent` | Represent protocol and destination port | `SecurityEvent`, `DetectionRule`, `ThreatDetector` |
| `DetectionRule` | Match an enabled condition against an event | Event subclasses |
| `ThreatDetector` | Own rules; detect single-event, raw-field, and pattern threats | `DetectionRule`, `SecurityEvent`, `Threat` |
| `Threat` | Store detected risk and status; provide nested risk label | `Alert`, `Incident`, `SecurityReport` |
| `Alert` | Describe and track a warning | `Threat`, `Incident` |
| `Incident` | Group alerts, evidence, and actions; coordinate response | `Alert`, `Evidence`, `ResponseAction`, `Device` |
| `Evidence` | Store an investigation artifact | `Incident` |
| `ResponseAction` | Execute a safe simulated response and record outcome | `Incident`, `Device` |
| `Device` | Represent the affected host and simulated isolation state | `SecurityEvent`, `ResponseAction` |
| `SecurityLog` | Store nested log entries and answer simple counts | All workflow services, `SecurityReport` |
| `SecurityReport` | Aggregate threats, alerts, incidents, and log counts | `Threat`, `Alert`, `Incident`, `SecurityLog` |
| `NumericSeverity` | Convert numeric severity to/from an object | `SecurityEvent`, exception hierarchy |
| `SecurityEventSummary` | Create a compact view by class-to-class conversion | `SecurityEvent` |
| Exception hierarchy | Reject invalid event data with specific error types | `SecurityEvent`, `NumericSeverity` |
| `Runnable` | Define the `run()` contract for a task | `Thread`, `EventMonitoringTask` |
| `Thread` | Manage lifecycle and expose `start`, `run`, `sleep`, `join`, and `yield` | `Runnable`, `EventMonitoringThread` |
| `EventMonitoringThread` | Process one event range by extending `Thread` | `SecurityEvent`, `ThreadSafeEventMetrics` |
| `EventMonitoringTask` | Process another range by implementing `Runnable` | `Thread`, `ThreadSafeEventMetrics` |
| `ThreadSafeEventMetrics` | Synchronize shared event counters with a mutex | Both monitoring workers |

Pointers held by `Incident` are non-owning links. `main.cpp` owns events with
`std::unique_ptr` and keeps the scenario's other linked objects alive on the
stack for the duration of the report.
