#ifndef SECURITYEVENT_H
#define SECURITYEVENT_H

#include <string>
#include "EventInfo.h"

using namespace std;

class SecurityEvent : virtual public EventInfo
{
private:
    string eventId;
    string eventType;
    string timestamp;
    int severity;

protected:
    string getEventType() const;
    int getSeverity() const;

public:
    SecurityEvent(
        string id,
        string type,
        string time,
        string ip,
        int sev
    );

    virtual ~SecurityEvent() = default;

    string getEventId() const;

    // Virtual function
    virtual void displayEvent() const;
};

#endif
