#ifndef SECURITYEVENT_H
#define SECURITYEVENT_H

#include "EventInfo.h"
#include <string>

using namespace std;

// ============================================================
// SecurityEvent
// ------------------------------------------------------------
// OOP CONCEPTS DEMONSTRATED HERE:
//
// 1. INHERITANCE (virtual)  : "virtual public EventInfo" makes
//    EventInfo a virtual base class. SecurityEvent receives the
//    shared sourceIp from EventInfo exactly once, even if a
//    derived class later inherits SecurityEvent via several paths.
//
// 2. ABSTRACTION           : the outside world uses getEventId(),
//    getSeverity(), etc. It never touches the raw data fields.
//
// 3. ENCAPSULATION         : data is private; access is only
//    through public member functions.
//
// 4. POLYMORPHISM          : displayEvent() is virtual. LoginEvent
//    and NetworkEvent both override it, and calling it through a
//    SecurityEvent* runs the correct version at runtime.
// ============================================================

class SecurityEvent : virtual public EventInfo
{
private:
    string eventId;
    string eventType;
    string timestamp;
    int severity;          // 1 = low ... 5 = critical

protected:
    // rawData holds a short simulated description for the report.
    string rawData;

public:
    SecurityEvent(
        string id,
        string type,
        string time,
        string ip,
        int sev
    );

    // Virtual destructor of the hierarchy.
    virtual ~SecurityEvent() = default;

    // --- Public accessors (encapsulation) ---
    string getEventId() const;
    string getEventType() const;
    int getSeverity() const;
    string getTimestamp() const;
    string getRawData() const;

    // --- Virtual function (polymorphism) ---
    // Each derived event type prints its own details.
    virtual void displayEvent() const;

    // OOP NOTE: clone() returns a real copy of the *actual* object.
    // Unlike assigning a derived object into a base variable (which
    // slices it), clone() copies through a pointer and therefore
    // keeps the full derived data . See object slicing in main.cpp.
    virtual SecurityEvent* clone() const;
};

#endif
