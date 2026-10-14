#include "SecurityEvent.h"
#include <iostream>

using namespace std;

// The initializer list forwards the IP up to the virtual base EventInfo.
SecurityEvent::SecurityEvent(
    string id,
    string type,
    string time,
    string ip,
    int sev
)
    : EventInfo(ip)          // <-- virtual base is constructed here
{
    eventId = id;
    eventType = type;
    timestamp = time;
    severity = sev;
    rawData = "Security event recorded";
}

string SecurityEvent::getEventId() const
{
    return eventId;
}

string SecurityEvent::getEventType() const
{
    return eventType;
}

int SecurityEvent::getSeverity() const
{
    return severity;
}

string SecurityEvent::getTimestamp() const
{
    return timestamp;
}

string SecurityEvent::getRawData() const
{
    return rawData;
}

void SecurityEvent::displayEvent() const
{
    cout << "\n--- Security Event (base) ---" << endl;
    cout << "Event ID    : " << eventId << endl;
    cout << "Event Type  : " << eventType << endl;
    cout << "Timestamp   : " << timestamp << endl;
    displayInfo();                 // prints the source IP from EventInfo
    cout << "Severity    : " << severity << endl;
}

SecurityEvent* SecurityEvent::clone() const
{
    return new SecurityEvent(*this);
}
