#include "Threat.h"
#include <iostream>

using namespace std;

// Definition of static variable
int Threat::threatCount = 0;


// Constructor
Threat::Threat(
    string id,
    string type,
    string ip,
    int sev,
    string stat
)
{
    // Demonstration of this pointer
    this->threatId = id;
    this->threatType = type;
    this->sourceIp = ip;
    this->severity = sev;
    this->status = stat;

    threatCount++;
}


// Getter functions
string Threat::getThreatId() const
{
    return this->threatId;
}

string Threat::getThreatType() const
{
    return this->threatType;
}

int Threat::getSeverity() const
{
    return this->severity;
}


// Display threat
void Threat::displayThreat() const
{
    cout << "\n--- Threat Detected ---" << endl;

    cout << "Threat ID   : " << this->threatId << endl;
    cout << "Threat Type : " << this->threatType << endl;
    cout << "Source IP   : " << this->sourceIp << endl;
    cout << "Severity    : " << this->severity << endl;

    cout << "Risk Level  : "
         << ThreatLevel::getLevel(this->severity)
         << endl;

    cout << "Status      : " << this->status << endl;
}


// Static function
int Threat::getThreatCount()
{
    return threatCount;
}


// Friend operator > overloading
bool operator>(
    const Threat& t1,
    const Threat& t2
)
{
    return t1.severity > t2.severity;
}


// Friend stream operator << overloading
ostream& operator<<(
    ostream& out,
    const Threat& threat
)
{
    out << "\n--- Threat Details ---" << endl;

    out << "Threat ID   : "
        << threat.threatId << endl;

    out << "Threat Type : "
        << threat.threatType << endl;

    out << "Source IP   : "
        << threat.sourceIp << endl;

    out << "Severity    : "
        << threat.severity << endl;

    out << "Risk Level  : "
        << Threat::ThreatLevel::getLevel(threat.severity)
        << endl;

    out << "Status      : "
        << threat.status << endl;

    return out;
}
