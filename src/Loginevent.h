#ifndef LOGINEVENT_H
#define LOGINEVENT_H

#include "SecurityEvent.h"

using namespace std;

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

    // Virtual function overriding
    void displayEvent() const override;

    bool isFailedLogin() const;
};

#endif
