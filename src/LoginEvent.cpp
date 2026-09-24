#include "LoginEvent.h"
#include <iostream>

using namespace std;

LoginEvent::LoginEvent(
    string id,
    string time,
    string ip,
    int sev,
    string user,
    bool success
)
    : SecurityEvent(id, "LOGIN_EVENT", time, ip, sev)
{
    this->username = user;
    this->loginSuccessful = success;
}

void LoginEvent::displayEvent() const
{
    cout << "\n--- Login Event ---" << endl;

    cout << "Event ID    : " << getEventId() << endl;
    cout << "Event Type  : LOGIN_EVENT" << endl;
    cout << "Source IP   : " << getSourceIp() << endl;
    cout << "Severity    : " << getSeverity() << endl;
    cout << "Username    : " << this->username << endl;

    cout << "Login Status: ";

    if (this->loginSuccessful)
        cout << "Successful" << endl;
    else
        cout << "Failed" << endl;
}

bool LoginEvent::isFailedLogin() const
{
    return !this->loginSuccessful;
}
