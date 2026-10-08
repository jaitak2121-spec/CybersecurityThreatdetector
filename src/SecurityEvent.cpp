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
<<<<<<< HEAD:src/Securityevents.cpp
    : EventInfo(ip)
{
    this->eventId = id;
    this->eventType = type;
    this->timestamp = time;
    this->severity = sev;
=======
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
>>>>>>> dd8f70d (Updated security events and combined all):src/SecurityEvent.cpp
}

string SecurityEvent::getTimestamp() const
{
<<<<<<< HEAD:src/Securityevents.cpp
    return this->eventId;
=======
    return timestamp;
>>>>>>> dd8f70d (Updated security events and combined all):src/SecurityEvent.cpp
}

string SecurityEvent::getRawData() const
{
<<<<<<< HEAD:src/Securityevents.cpp
    return EventInfo::getSourceIp();
}

string SecurityEvent::getEventType() const
{
    return this->eventType;
}

int SecurityEvent::getSeverity() const
{
    return this->severity;
=======
    return rawData;
>>>>>>> dd8f70d (Updated security events and combined all):src/SecurityEvent.cpp
}

void SecurityEvent::displayEvent() const
{
<<<<<<< HEAD:src/Securityevents.cpp
    cout << "\n--- Security Event ---" << endl;
    cout << "Event ID    : " << this->eventId << endl;
    cout << "Event Type  : " << this->eventType << endl;
    cout << "Timestamp   : " << this->timestamp << endl;
    cout << "Source IP   : " << this->sourceIp << endl;
    cout << "Severity    : " << this->severity << endl;
=======
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
>>>>>>> dd8f70d (Updated security events and combined all):src/SecurityEvent.cpp
}
