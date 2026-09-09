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
    username = user;
    loginSuccessful = success;
}

void LoginEvent::displayEvent() const
{
    cout << "\n--- Login Event ---" << endl;
    cout << "Event ID        : " << getEventId() << endl;
    cout << "Event Type      : " << getEventType() << endl;
    cout << "Source IP       : " << getSourceIp() << endl;
    cout << "Username        : " << username << endl;
    cout << "Login Status    : "
         << (loginSuccessful ? "Successful" : "Failed")
         << endl;
    cout << "Severity        : " << getSeverity() << endl;
}

bool LoginEvent::isFailedLogin() const
{
    return !loginSuccessful;
}