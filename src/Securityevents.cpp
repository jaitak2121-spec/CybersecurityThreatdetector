#include "SecurityEvent.h"
#include <iostream>

using namespace std;

SecurityEvent::SecurityEvent(
    string id,
    string type,
    string time,
    string ip,
    int sev
)
    : EventInfo(ip)
{
    this->eventId = id;
    this->eventType = type;
    this->timestamp = time;
    this->severity = sev;
}

string SecurityEvent::getEventId() const
{
    return this->eventId;
}

string SecurityEvent::getSourceIp() const
{
    return EventInfo::getSourceIp();
}

string SecurityEvent::getEventType() const
{
    return this->eventType;
}

int SecurityEvent::getSeverity() const
{
    return this->severity;
}

void SecurityEvent::displayEvent() const
{
    cout << "\n--- Security Event ---" << endl;
    cout << "Event ID    : " << this->eventId << endl;
    cout << "Event Type  : " << this->eventType << endl;
    cout << "Timestamp   : " << this->timestamp << endl;
    cout << "Source IP   : " << this->sourceIp << endl;
    cout << "Severity    : " << this->severity << endl;
}
