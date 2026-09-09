#include "NetworkEvent.h"
#include <iostream>

using namespace std;

NetworkEvent::NetworkEvent(
    string id,
    string time,
    string ip,
    int sev,
    int port,
    string proto
)
    : SecurityEvent(id, "NETWORK_EVENT", time, ip, sev)
{
    destinationPort = port;
    protocol = proto;
}

void NetworkEvent::displayEvent() const
{
    cout << "\n--- Network Event ---" << endl;
    cout << "Event ID        : " << getEventId() << endl;
    cout << "Event Type      : " << getEventType() << endl;
    cout << "Source IP       : " << getSourceIp() << endl;
    cout << "Protocol        : " << protocol << endl;
    cout << "Destination Port: " << destinationPort << endl;
    cout << "Severity        : " << getSeverity() << endl;
}