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
<<<<<<< HEAD
    this->username = user;
    this->loginSuccessful = success;
=======
    // --------------------------------------------------------
    // OOP CONCEPT: this POINTER
    // "this" points to the current object. Using this-> makes it
    // explicit that we assign the member variable "username" the
    // value of the parameter "user". Without the clear naming,
    // this->username = username is how the compiler tells the
    // two apart (the member is implied by "this->").
    // --------------------------------------------------------
    this->username = user;
    this->loginSuccessful = success;

    // Build a short simulated raw description for the report/log.
    rawData = "Login attempt for user '" + user + "' from " + sourceIp
              + (success ? " (SUCCESS)" : " (FAILED)");
>>>>>>> dd8f70d (Updated security events and combined all)
}

void LoginEvent::displayEvent() const
{
    cout << "\n--- Login Event ---" << endl;
<<<<<<< HEAD

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
=======
    cout << "Event ID        : " << getEventId() << endl;
    cout << "Event Type      : " << getEventType() << endl;
    cout << "Timestamp       : " << getTimestamp() << endl;
    cout << "Source IP       : " << getSourceIp() << endl;
    cout << "Username        : " << username << endl;
    cout << "Login Status    : "
         << (loginSuccessful ? "Successful" : "Failed")
         << endl;
    cout << "Severity        : " << getSeverity() << endl;
>>>>>>> dd8f70d (Updated security events and combined all)
}

// Copies the *derived* object, so username/loginSuccessful survive.
SecurityEvent* LoginEvent::clone() const
{
    return new LoginEvent(*this);
}

bool LoginEvent::isFailedLogin() const
{
<<<<<<< HEAD
    return !this->loginSuccessful;
=======
    return !loginSuccessful;
}

string LoginEvent::getUsername() const
{
    return username;
>>>>>>> dd8f70d (Updated security events and combined all)
}
