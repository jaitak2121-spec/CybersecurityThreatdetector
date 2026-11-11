# Cybersecurity Threat Detection & Incident Response Simulator

A safe C++17 simulation of a small security-monitoring pipeline. It validates
events, applies detection rules, creates threats and alerts, investigates an
incident, performs simulated responses, writes an audit log, and prints a
report. No real account, device, or network operation is performed.

## Build and run

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -pthread -o simulator src/*.cpp
./simulator
```

For the presentation frontend:

```bash
python3 frontend/server.py
```

Open <http://localhost:10000> and select **Run Simulation**. The frontend
compiles and runs the same C++ program; it does not reimplement the model.
Do not open `frontend/index.html` directly with a `file://` URL: that only
previews the layout and has no simulator API behind it.

The web UI offers five safe, allow-listed runs: a full demonstration, attack
data without deliberate errors, validation errors, a failed response action,
and a higher-volume attack dataset.
After every successful run, the dashboard keeps the previous summary in the
browser session and shows metric-by-metric changes for events, threats,
critical threats, validation errors, failed actions, and log entries.

## Public deployment

The repository includes both a production Docker image and `render.yaml`.

1. Push the repository to GitHub or GitLab.
2. In Render, create a **Blueprint** and select the repository.
3. Render reads `render.yaml`, builds the Dockerfile, checks `/healthz`, and
   provides a public `onrender.com` URL.

The service binds to Render's `$PORT`, runs as a non-root container user,
accepts only predefined scenario names, limits concurrent simulator runs, and
does not pass request content to a shell. Free Render services may sleep after
an idle period, so the first visit can take longer to start.

Run the deployment smoke check with:

```bash
python3 tests/smoke_test.py
```

## Simplified workflow

```text
Device
  -> validated LoginEvent / NetworkEvent objects
  -> two synchronized monitoring workers
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
| Multithreading | `Runnable`, `Thread`, `EventMonitoringThread`, `EventMonitoringTask`, `ThreadSafeEventMetrics` | Process event ranges concurrently and safely combine metrics |

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
| Multithreading | Two event-monitoring workers execute concurrently before detection |
| Thread synchronization | `ThreadSafeEventMetrics::record()` protects shared counters with `std::mutex` and `std::lock_guard` |

## Multithreading lab concept map

| Required topic | Where and how it is implemented |
|---|---|
| Creating threads | Section 2 of `main.cpp` creates `inheritedWorker` and `runnableWorker` |
| Extending `Thread` | `EventMonitoringThread : public Thread` overrides `run()` |
| Implementing `Runnable` | `EventMonitoringTask : public Runnable` overrides `run()` and is passed to a `Thread` |
| Thread life cycle | `Thread::State` moves through `NEW`, `RUNNABLE`, `RUNNING`, `TIMED_WAITING`, and `TERMINATED`; states are printed before `start()` and after `join()` |
| `start()` | Creates the underlying `std::thread` and begins `threadEntry()` |
| `run()` | Contains each worker's event-processing work |
| `sleep()` | Pauses each worker briefly using `std::this_thread::sleep_for()` |
| `join()` | Makes the main flow wait for both workers before using their metrics |
| `yield()` | Gives another runnable worker an execution opportunity |
| Synchronization | Both workers update one `ThreadSafeEventMetrics`; a mutex prevents data races |

## Project documents and diagrams

- [Problem statement](problemstatement.md)
- [Noun analysis](noun-analysis.md)
- [CRC cards](crc-cards.md)
- [Use cases](use-cases.md)
- [Complete concept implementation map](concept-implementation-map.md)
- [Class diagram source](class-diagram.puml)
- [Rendered class diagram](class-diagram.png)
- [Object diagram source](object-diagram.puml)
- [Rendered object diagram](object-diagram.png)
- [Sequence diagram source](sequence-diagram.puml)
- [Rendered sequence diagram](sequence-diagram.png)
- [Use-case diagram source](usercasediagram.mmd)

The Dockerfile builds the simulator and serves the frontend for deployment.
