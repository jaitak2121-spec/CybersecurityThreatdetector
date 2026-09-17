#include "Threat.h"
#include <iostream>

using namespace std;


int Threat::threatCount = 0;


Threat::Threat(
    string id,
    string type,
    string ip,
    int sev,
    string stat
)
{
    threatId = id;
    threatType = type;
    sourceIp = ip;
    severity = sev;
    status = stat;

    threatCount++;
}


string Threat::getThreatId() const
{
    return threatId;
}

string Threat::getThreatType() const
{
    return threatType;
}

int Threat::getSeverity() const
{
    return severity;
}


void Threat::displayThreat() const
{
    cout << "\n--- Threat Detected ---" << endl;
    cout << "Threat ID   : " << threatId << endl;
    cout << "Threat Type : " << threatType << endl;
    cout << "Source IP   : " << sourceIp << endl;
    cout << "Severity    : " << severity << endl;

    cout << "Risk Level  : "
         << ThreatLevel::getLevel(severity)
         << endl;

    cout << "Status      : " << status << endl;
}


int Threat::getThreatCount()
{
    return threatCount;
}


bool operator>(
    const Threat& t1,
    const Threat& t2
)
{
    return t1.severity > t2.severity;
}


ostream& operator<<(
    ostream& out,
    const Threat& threat
)
{
    out << "\n--- Threat Details ---" << endl;
    out << "Threat ID   : " << threat.threatId << endl;
    out << "Threat Type : " << threat.threatType << endl;
    out << "Source IP   : " << threat.sourceIp << endl;
    out << "Severity    : " << threat.severity << endl;

    out << "Risk Level  : "
        << Threat::ThreatLevel::getLevel(threat.severity)
        << endl;

    out << "Status      : " << threat.status << endl;

    return out;
}
