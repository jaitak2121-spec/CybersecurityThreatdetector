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
    this->destinationPort = port;
    this->protocol = proto;
}

void NetworkEvent::displayEvent() const
{
    cout << "\n--- Network Event ---" << endl;

    cout << "Event ID    : " << getEventId() << endl;
    cout << "Event Type  : NETWORK_EVENT" << endl;
    cout << "Source IP   : " << getSourceIp() << endl;
    cout << "Severity    : " << getSeverity() << endl;
    cout << "Destination : Port " << this->destinationPort << endl;
    cout << "Protocol    : " << this->protocol << endl;
}
