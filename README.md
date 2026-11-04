# Cybersecurity Threat Detection & Incident Response Simulator

A safe C++17 simulation of a small security-monitoring pipeline. It validates
events, applies detection rules, creates threats and alerts, investigates an
incident, performs simulated responses, writes an audit log, and prints a
report. No real account, device, or network operation is performed.

## Build and run

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -o simulator src/*.cpp
./simulator
```

For the presentation frontend:

```bash
python3 frontend/server.py
```

Open <http://localhost:10000> and select **Run Simulation**. The frontend
compiles and runs the same C++ program; it does not reimplement the model.

## Simplified workflow

```text
Device
  -> validated LoginEvent / NetworkEvent objects
  -> DetectionRule evaluation by ThreatDetector
  -> Threat and Alert
  -> Incident with Evidence
  -> simulated ResponseAction objects
  -> SecurityLog and SecurityReport
```

The example uses three failed logins from one source and one risky SSH event.
An invalid severity and a missing event identity are also submitted and rejected
before detection, exercising both derived and base exception handlers.

## How type conversion and exceptions are connected

They are no longer stand-alone demonstrations at the end of `main()`:

- `SecurityEvent` calls `ExceptionHandling::validateEventInput()` during
  construction. Invalid input throws a custom `SecurityException` subtype.
- An RAII validation guard performs cleanup on both the normal and exception
  paths (the C++ equivalent of `finally`).
- `NumericSeverity` converts a real event severity from `int` to a class and
  back to `int`.
- `SecurityEventSummary` converts a real `SecurityEvent` into a compact summary.
- `printMetric<T>()` prints report metrics of several types.

## Class structure

| Area | Classes | Purpose |
|---|---|---|
| Events | `EventInfo`, `SecurityEvent`, `LoginEvent`, `NetworkEvent` | Common event data and polymorphic event types |
| Detection | `DetectionRule`, `ThreatDetector`, `Threat` | Match events, find patterns, classify risk |
| Response | `Alert`, `Incident`, `Evidence`, `ResponseAction`, `Device` | Investigate and contain a simulated incident |
| Audit | `SecurityLog`, `SecurityReport` | Record and summarize the run |
| Validation/conversion | exception hierarchy, `NumericSeverity`, `SecurityEventSummary` | Validate and convert actual workflow data |

## OOP concept map

| Concept | Implementation |
|---|---|
| Encapsulation and abstraction | Private fields and small public operations on all domain classes |
| Inheritance | `LoginEvent` and `NetworkEvent` derive from `SecurityEvent` |
| Virtual inheritance | `SecurityEvent : virtual public EventInfo` |
| Runtime polymorphism / overriding | `displayEvent()` through `SecurityEvent*` |
| Function overloading | Three `ThreatDetector::detectThreat()` signatures |
| Operator overloading / friends | `operator<<` and `operator>` on domain objects |
| Nested classes | `Threat::ThreatLevel`, `SecurityLog::LogEntry` |
| Static data/functions | Threat, alert, incident, and log counters |
| `this` pointer | `LoginEvent` construction and `Threat::updateStatus()` |
| Object pointers / derived pointers | Polymorphic event view and `dynamic_cast<LoginEvent*>` |
| Object slicing | Base copy compared with virtual `clone()` |
| `final` | `NetworkEvent final` |
| Basic-to-class conversion | `int -> NumericSeverity` |
| Class-to-basic conversion | `NumericSeverity -> int` |
| Class-to-class conversion | `SecurityEvent -> SecurityEventSummary` |
| Templates | `printMetric<T>()` |
| Exception handling | `try`, `throw`, derived/base `catch`, custom exceptions, RAII cleanup |
| Constructors/destructors | All classes; virtual event destructors and smart-pointer ownership |

## Project documents and diagrams

- [Problem statement](problemstatement.md)
- [Noun analysis](noun-analysis.md)
- [CRC cards](crc-cards.md)
- [Use cases](use-cases.md)
- [Class diagram source](class-diagram.puml)
- [Rendered class diagram](class-diagram.png)
- [Object diagram source](object-diagram.puml)
- [Rendered object diagram](object-diagram.png)
- [Sequence diagram source](sequence-diagram.puml)
- [Rendered sequence diagram](sequence-diagram.png)
- [Use-case diagram source](usercasediagram.mmd)

The Dockerfile builds the simulator and serves the frontend for deployment.
