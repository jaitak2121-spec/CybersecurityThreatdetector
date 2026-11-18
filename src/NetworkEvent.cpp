#include "NetworkEvent.h"
#include "TypeCasting.h"
#include <iostream>

using namespace std;

NetworkEvent::NetworkEvent(
    string id,
    string time,
    string ip,
    int port,
    string proto,
    int attempts,
    bool unauthorized
)
    // Virtual base EventInfo is listed first because it is always
    // constructed first; SecurityEvent then forwards the same ip.
    : EventInfo(ip),
      SecurityEvent(
          id,
          "NETWORK_EVENT",
          time,
          ip,
          TypeCasting::NumericSeverity::forNetwork(port, attempts, unauthorized).getLevel()
      )
{
    destinationPort = port;
    protocol = proto;

    rawData = "Network connection to port " + to_string(port)
              + " using " + proto
              + "; attempts in simulated 5-minute window=" + to_string(attempts)
              + "; unauthorized=" + (unauthorized ? "yes" : "no");
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
    cout << "Severity Score  : " << getSeverity() << " (calculated)" << endl;
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
