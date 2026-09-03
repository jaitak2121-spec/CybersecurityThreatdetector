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
{
    eventId = id;
    eventType = type;
    timestamp = time;
    sourceIp = ip;
    severity = sev;
}

string SecurityEvent::getEventType() const
{
    return eventType;
}

int SecurityEvent::getSeverity() const
{
    return severity;
}

string SecurityEvent::getEventId() const
{
    return eventId;
}

string SecurityEvent::getSourceIp() const
{
    return sourceIp;
}

int SecurityEvent::getEventSeverity() const
{
    return severity;
}

void SecurityEvent::displayEvent() const
{
    cout << "\n--- Security Event ---" << endl;
    cout << "Event ID    : " << eventId << endl;
    cout << "Event Type  : " << eventType << endl;
    cout << "Timestamp   : " << timestamp << endl;
    cout << "Source IP   : " << sourceIp << endl;
    cout << "Severity    : " << severity << endl;
}