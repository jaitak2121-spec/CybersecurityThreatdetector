# Concept Implementation Map

This document is the final viva/lab index showing where each concept appears
and how it is used in the running project.

## Object-oriented and C++ concepts

| Concept | Where | How it is demonstrated |
|---|---|---|
| Encapsulation | All domain headers | Data members are private/protected and accessed through public methods |
| Abstraction | `DetectionRule::matches`, `ResponseAction::execute`, `Device::isolate` | Complex checks/actions are hidden behind one operation |
| Inheritance | `LoginEvent`, `NetworkEvent` | Both inherit `SecurityEvent` |
| Virtual inheritance | `SecurityEvent` | Inherits `virtual public EventInfo` |
| Runtime polymorphism | `main.cpp` event collection | `SecurityEvent*` calls the correct overridden `displayEvent()` |
| Function overriding | `LoginEvent::displayEvent`, `NetworkEvent::displayEvent` | Derived implementations use `override` |
| Function overloading | `ThreatDetector` | Three `detectThreat()` parameter lists handle an event, raw values, or an event collection |
| Operator overloading | `Threat`, `Alert`, `Evidence`, `Incident`, `ResponseAction` | `operator<<` prints objects and `operator>` compares threat severity |
| Friend functions | The same printable domain classes | Friend stream operators read private state safely |
| Nested classes | `Threat::ThreatLevel`, `SecurityLog::LogEntry` | Helper types are scoped inside their owning classes |
| Static members | `Threat`, `Alert`, `Incident`, `SecurityLog` | Shared counters and static getter functions track created objects/entries |
| `this` pointer | `LoginEvent` constructor, `Threat::updateStatus` | Explicitly refers to the current object's member |
| Base/derived pointers | `main.cpp`, `DetectionRule`, `ThreatDetector` | Uses `SecurityEvent*` and checked `dynamic_cast` to derived event types |
| Object slicing | Section 5 of `main.cpp` | A base copy loses derived data; virtual `clone()` preserves it |
| `final` | `NetworkEvent` | Prevents further inheritance |
| Constructors/destructors | All classes; event and thread hierarchies | Objects initialize valid state; base destructors are virtual |
| Smart pointers | Section 1 of `main.cpp` | `unique_ptr<SecurityEvent>` owns polymorphic events automatically |
| Basic-to-class conversion | `NumericSeverity` | Converts an admitted event's integer severity to an object |
| Class-to-basic conversion | `NumericSeverity::operator int` | Converts the severity object back to an integer |
| Class-to-class conversion | `SecurityEventSummary` | Builds a summary directly from a real `SecurityEvent` |
| Function template | `TypeCasting::printMetric<T>` | Prints integer and string metrics through one generic function |
| Custom exceptions | `ExceptionHandling` hierarchy | Invalid event identity/severity throws specific derived exceptions |
| Derived/base catches | Section 1 of `main.cpp` | Shows specific catch ordering and a base handler catching a derived error |
| RAII cleanup | Validation guard in `ExceptionHandling.cpp` | Destructor runs on normal completion and during stack unwinding |

## Multithreading concepts

| Required topic | Where | How it is demonstrated |
|---|---|---|
| Creating threads | Section 2 of `main.cpp` | Creates two workers and calls `start()` on both |
| Extending `Thread` | `EventMonitoringThread` | Inherits `Thread` and overrides `run()` |
| Implementing `Runnable` | `EventMonitoringTask` | Implements `Runnable::run()` and is supplied to a `Thread` object |
| Thread lifecycle | `Thread::State` | Transitions through `NEW`, `RUNNABLE`, `RUNNING`, `TIMED_WAITING`, and `TERMINATED` |
| `start()` | `Thread::start()` | Creates the underlying `std::thread` and invokes the worker entry point |
| `run()` | Both monitoring worker classes | Processes each assigned event range |
| `sleep()` | Worker loops | Enters `TIMED_WAITING` and uses `std::this_thread::sleep_for()` |
| `join()` | Section 2 of `main.cpp` | Waits for both workers before metrics are read and detection begins |
| `yield()` | Worker loops | Temporarily returns execution opportunity to another runnable thread |
| Synchronization | `ThreadSafeEventMetrics::record()` | `std::mutex` and `std::lock_guard` protect shared counters from data races |

The frontend displays the lifecycle states, synchronized totals, audit entry,
and this same mapping in its expandable concept table.
