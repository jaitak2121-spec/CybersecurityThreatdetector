#ifndef EVENTINFO_H
#define EVENTINFO_H

#include <string>

using namespace std;

// ============================================================
// OOP CONCEPT: VIRTUAL BASE CLASS
// ------------------------------------------------------------
// EventInfo is the common base for every kind of security event.
// It stores the information that ALL events share (the source IP
// the event came from).
//
// SecurityEvent inherits from it using "virtual public" so that
// if a class ever inherits SecurityEvent through more than one
// path, it still receives only ONE copy of EventInfo. This
// avoids the classic "diamond problem" of duplicate base data.
// ============================================================

class EventInfo
{
protected:
    // Protected: visible to derived classes, hidden from the outside.
    string sourceIp;

public:
    EventInfo(string ip);

    // Virtual destructor: safe deletion through a base-class pointer.
    virtual ~EventInfo() = default;

    string getSourceIp() const;

    // Virtual so derived classes may extend how event info is shown.
    virtual void displayInfo() const;
};

#endif
