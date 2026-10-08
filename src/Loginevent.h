#ifndef LOGINEVENT_H
#define LOGINEVENT_H

#include "SecurityEvent.h"

using namespace std;

// ============================================================
// LoginEvent
// ------------------------------------------------------------
// OOP CONCEPTS DEMONSTRATED HERE:
//
// 1. INHERITANCE  : LoginEvent is a SecurityEvent (and therefore
//    also an EventInfo, through the virtual base).
//
// 2. FUNCTION OVERRIDING (polymorphism) : displayEvent() replaces
//    the base version. The keyword "override" lets the compiler
//    confirm we really are overriding a virtual function.
//
// 3. this POINTER : the constructor uses this->username = user to
//    show the difference between the member variable (username)
//    and the parameter (user).
// ============================================================

class LoginEvent : public SecurityEvent
{
private:
    string username;
    bool loginSuccessful;

public:
    LoginEvent(
        string id,
        string time,
        string ip,
        int sev,
        string user,
        bool success
    );

<<<<<<< HEAD
    // Virtual function overriding
=======
    // Overrides SecurityEvent::displayEvent()
>>>>>>> dd8f70d (Updated security events and combined all)
    void displayEvent() const override;

    // Returns a full copy of the real object (no slicing).
    SecurityEvent* clone() const override;

    // Login-specific behaviour used by the detection rules.
    bool isFailedLogin() const;
    string getUsername() const;
};

#endif
