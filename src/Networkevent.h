#ifndef NETWORKEVENT_H
#define NETWORKEVENT_H

#include "SecurityEvent.h"

using namespace std;

<<<<<<< HEAD
=======
// ============================================================
// NetworkEvent
// ------------------------------------------------------------
// OOP CONCEPTS DEMONSTRATED HERE:
//
// 1. INHERITANCE + OVERRIDING : a second kind of SecurityEvent,
//    with its own displayEvent().
//
// 2. final KEYWORD : the class is marked "final". This means no
//    other class may inherit from NetworkEvent. It signals that
//    NetworkEvent is a complete, closed event type and prevents
//    accidental further extension (and the bugs that come with
//    it). The compiler would reject:
//        class X : public NetworkEvent { ... };   // ERROR
// ============================================================

>>>>>>> dd8f70d (Updated security events and combined all)
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
    SecurityEvent* clone() const override;

    int getDestinationPort() const;
    string getProtocol() const;
};

#endif
