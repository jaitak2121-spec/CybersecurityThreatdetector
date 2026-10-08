# Cybersecurity Threat Detection & Incident Response Simulator

A **safe, simulated** cybersecurity monitoring system written in C++ for an
object-oriented programming course. It models the full incident-response
pipeline — from raw security events through detection, alerting, incident
creation, investigation, simulated response, logging, and reporting.

> ⚠️ **This is a simulation only.** It performs **no** real hacking,
> exploitation, network blocking, account locking, or any other live security
> action. Every "response" simply updates a status string to model what a real
> system would do.

---

## Build

Requires a C++17 compiler (g++ or clang++).

```bash
g++ -std=c++17 -Wall -Wextra -o simulator src/*.cpp
```

## Run

```bash
./simulator
```

The program runs one complete scenario end to end and prints each stage to the
console.

---

## What the simulator does (the workflow)

It reproduces the brute-force scenario from the project's object diagram:

```
Device generates Security Events  (5 failed logins + 1 network event)
        │
        ▼
Detection Rules evaluate each event      (DetectionRule)
        │
        ▼
Threats are detected & risk-classified   (ThreatDetector, Threat::ThreatLevel)
        │
        ▼
An Alert is raised for the serious threat (Alert)
        │
        ▼
An Incident is created and the alert escalated (Incident, UC-02)
        │
        ▼
Evidence is attached during investigation (Evidence, UC-01)
        │
        ▼
Simulated Response Actions are executed   (ResponseAction, UC-03)
   block source · lock account · isolate device · (one failing action)
        │
        ▼
Every step is written to the Security Log (SecurityLog)
        │
        ▼
A Security Report summarises the run      (SecurityReport)
```

---

## Source files

| File | Class | Role |
|------|-------|------|
| `EventInfo.{h,cpp}` | `EventInfo` | Virtual base class; common event data (source IP) |
| `SecurityEvent.{h,cpp}` | `SecurityEvent` | Base event; virtual `displayEvent()` |
| `LoginEvent.{h,cpp}` | `LoginEvent` | Login event (derived) |
| `NetworkEvent.{h,cpp}` | `NetworkEvent` | Network event (derived, `final`) |
| `Threat.{h,cpp}` | `Threat` + nested `ThreatLevel` | A detected threat and its risk level |
| `ThreatDetector.{h,cpp}` | `ThreatDetector` | Rule-based detection, overloaded `detectThreat()` |
| `DetectionRule.{h,cpp}` | `DetectionRule` | A single detection condition |
| `Alert.{h,cpp}` | `Alert` | Warning raised by a triggered rule |
| `Incident.{h,cpp}` | `Incident` | Groups alerts, evidence, actions |
| `Evidence.{h,cpp}` | `Evidence` | Investigation artifact |
| `ResponseAction.{h,cpp}` | `ResponseAction` | Simulated response |
| `Device.{h,cpp}` | `Device` | Affected device; simulated `isolate()` |
| `SecurityLog.{h,cpp}` | `SecurityLog` + nested `LogEntry` | Audit trail |
| `SecurityReport.{h,cpp}` | `SecurityReport` | End-of-run summary |
| `main.cpp` | — | Drives the full scenario + OOP demos |

---

## OOP concept crib sheet (for the viva)

Every required concept, with exactly where to point:

| OOP concept | Where it lives | What to show |
|-------------|----------------|--------------|
| **Encapsulation** | every class | private data + public getters |
| **Abstraction** | `Device::isolate()`, `ResponseAction::execute()` | one call hides the detail |
| **Inheritance** | `SecurityEvent` → `LoginEvent`, `NetworkEvent` | `: public SecurityEvent` |
| **Virtual base / virtual inheritance** | `SecurityEvent : virtual public EventInfo` | `SecurityEvent.h` line with `virtual` |
| **Virtual function (polymorphism)** | `SecurityEvent::displayEvent()` overridden | STEP 11b — same `->displayEvent()` call, two outputs |
| **Function overriding** | `LoginEvent`/`NetworkEvent` `displayEvent() ... override` | the `override` keyword |
| **Function overloading** | `ThreatDetector::detectThreat()` ×3 | STEP 5 — three different parameter lists |
| **Operator overloading** | `operator<<` and `operator>` for `Threat` | STEP 6 — `cout << threat`, `threat1 > threat2` |
| **Friend function** | `operator<<` on `Threat`, `Alert`, `Evidence`, `Incident`, `ResponseAction` | STEP 11h |
| **Nested class** | `Threat::ThreatLevel`, `SecurityLog::LogEntry` | STEP 11e |
| **Static variable** | `Threat::threatCount`, `Alert::alertCount`, `SecurityLog::logCount`, `Incident::incidentCount` | STEP 11d |
| **Static function** | `Threat::getThreatCount()` etc. | STEP 11d — called without an object |
| **`this` pointer** | `LoginEvent` ctor (`this->username`), `Threat::updateStatus()` | STEP 11f |
| **Pointer to objects** | `SecurityEvent* securityEventPtr = &loginExample;` | STEP 11a |
| **Pointer to derived class** | `LoginEvent* loginPtr = &loginExample;` + `dynamic_cast` in `DetectionRule`/`ThreatDetector` | STEP 11a |
| **Object slicing** | `SecurityEvent slicedEvent = loginExample;` | STEP 11c — derived data lost; `clone()` avoids it |
| **`final` keyword** | `class NetworkEvent final : public SecurityEvent` | STEP 11g |
| **Constructors / destructors** | all classes; virtual `~EventInfo`/`~SecurityEvent` | base pointers delete safely |

---

## Implementation notes

- **Simplified types vs the UML.** The design documents (`class-diagram.puml`,
  CRC cards) use conceptual types such as `String`, `DateTime`, and
  `Map<String,Integer>`. The C++ implementation uses standard
  `std::string`, `int`, `bool`, and `std::vector` so the code stays readable
  for a first-year OOP student. Timestamps are plain strings.
- **Terminology preserved.** All class names and the pipeline terminology match
  the original noun analysis, CRC cards, and class/object diagrams
  (SecurityEvent, Threat, DetectionRule, Alert, Incident, Evidence,
  ResponseAction, Device, SecurityLog, SecurityReport).
- **Use cases covered.** UC-01 (investigate / attach evidence / false-positive
  path), UC-02 (create incident, associate alert), and UC-03 (respond, with a
  deliberate failing action to show the response-failure flow).
- **Safety.** `Device::isolate()` and every `ResponseAction` type only change
  status/outcome strings and print a `[SIMULATION]` line. No real system call,
  network, or account operation is performed anywhere.

---

## Example output (abridged)

```
STEP 4: Detect Threats
  Rule triggered: Failed Login (severity >= 4)   (×5)
  Rule triggered: Connection to risky port (severity >= 4)
Checking for brute-force pattern from 203.0.113.19 (threshold 5)...
  5 failed logins detected - brute-force pattern confirmed.

STEP 10: Respond to Incident (SIMULATED)
  [SIMULATION] Executing BLOCK_SOURCE on '203.0.113.19'
  [SIMULATION] Device DEV-SRV-04 has been marked ISOLATED.

STEP 13: Security Report
  Threats detected: 9   HIGH: 8   Incidents: 1   Log entries: 23
  System status: HIGH-risk activity detected.
```
