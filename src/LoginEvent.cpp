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
    // Virtual base EventInfo is listed first because it is always
    // constructed first; SecurityEvent then forwards the same ip.
    : EventInfo(ip),
      SecurityEvent(id, "LOGIN_EVENT", time, ip, sev)
{
    // --------------------------------------------------------
    // OOP CONCEPT: this POINTER
    // "this" points to the current object. Using this-> makes it
    // explicit that we assign the member variable "username" the
    // value of the parameter "user".
    // --------------------------------------------------------
    this->username = user;
    this->loginSuccessful = success;

    // Build a short simulated raw description for the report/log.
    rawData = "Login attempt for user '" + user + "' from " + sourceIp
              + (success ? " (SUCCESS)" : " (FAILED)");
}

void LoginEvent::displayEvent() const
{
    cout << "\n--- Login Event ---" << endl;
    cout << "Event ID        : " << getEventId() << endl;
    cout << "Event Type      : " << getEventType() << endl;
    cout << "Timestamp       : " << getTimestamp() << endl;
    cout << "Source IP       : " << getSourceIp() << endl;
    cout << "Username        : " << username << endl;
    cout << "Login Status    : "
         << (loginSuccessful ? "Successful" : "Failed")
         << endl;
    cout << "Severity        : " << getSeverity() << endl;
}

// Copies the *derived* object, so username/loginSuccessful survive.
SecurityEvent* LoginEvent::clone() const
{
    return new LoginEvent(*this);
}

bool LoginEvent::isFailedLogin() const
{
    return !loginSuccessful;
}

string LoginEvent::getUsername() const
{
    return username;
}
