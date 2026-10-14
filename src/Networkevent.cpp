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
    // Virtual base EventInfo is listed first because it is always
    // constructed first; SecurityEvent then forwards the same ip.
    : EventInfo(ip),
      SecurityEvent(id, "NETWORK_EVENT", time, ip, sev)
{
    destinationPort = port;
    protocol = proto;

    rawData = "Network connection to port " + to_string(port)
              + " using " + proto;
}

void NetworkEvent::displayEvent() const
{
    cout << "\n--- Network Event ---" << endl;
    cout << "Event ID        : " << getEventId() << endl;
    cout << "Event Type      : " << getEventType() << endl;
    cout << "Timestamp       : " << getTimestamp() << endl;
    cout << "Source IP       : " << getSourceIp() << endl;
    cout << "Protocol        : " << protocol << endl;
    cout << "Destination Port: " << destinationPort << endl;
    cout << "Severity        : " << getSeverity() << endl;
}

SecurityEvent* NetworkEvent::clone() const
{
    return new NetworkEvent(*this);
}

int NetworkEvent::getDestinationPort() const
{
    return destinationPort;
}

string NetworkEvent::getProtocol() const
{
    return protocol;
}
