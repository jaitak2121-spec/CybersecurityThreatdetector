#ifndef NETWORKEVENT_H
#define NETWORKEVENT_H

#include "SecurityEvent.h"

using namespace std;

class NetworkEvent final : public SecurityEvent
{
private:
    int destinationPort;
    string protocol;

public:
    NetworkEvent(
        string id,
        string time,
        string ip,
        int sev,
        int port,
        string proto
    );

    // Virtual function overriding
    void displayEvent() const override;
};

#endif
