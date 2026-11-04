# Noun Analysis

## Candidate nouns

Security event, login event, network event, device, detection rule, threat
detector, threat, alert, incident, evidence, response action, security log,
security report, analyst, source IP, severity, status, event summary, security
exception, thread, runnable task, synchronized metrics.

## Filtering

| Candidate | Decision |
|---|---|
| Analyst | Actor, shown in the use-case diagram rather than a domain class |
| Source IP, severity, status | Attributes of domain classes |
| Login event, network event | Specialized subclasses of `SecurityEvent` |
| Threat detector | Kept as a service class because it owns rules and overloaded detection operations |
| Event summary | Kept as a small conversion/view class |
| Security exception | Kept as a validation hierarchy used by event construction |
| Thread and runnable task | Kept as infrastructure classes because the lab requires both thread-creation styles |
| Synchronized metrics | Kept as shared state that demonstrates mutex protection |

## Final model

- Event hierarchy: `EventInfo`, `SecurityEvent`, `LoginEvent`, `NetworkEvent`
- Detection: `DetectionRule`, `ThreatDetector`, `Threat`
- Investigation/response: `Alert`, `Incident`, `Evidence`, `ResponseAction`, `Device`
- Audit/reporting: `SecurityLog`, `SecurityReport`
- Supporting concepts: `NumericSeverity`, `SecurityEventSummary`,
  `SecurityException`, `InvalidSeverityException`, `InvalidEventException`
- Multithreading: `Runnable`, `Thread`, `EventMonitoringThread`,
  `EventMonitoringTask`, `ThreadSafeEventMetrics`

This list matches the implemented class diagram rather than describing
unimplemented event or module types.
