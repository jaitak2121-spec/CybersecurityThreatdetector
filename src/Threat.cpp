#include "Threat.h"
#include <iostream>

using namespace std;

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
    cout << "Status      : " << status << endl;
}

bool operator>(const Threat& t1, const Threat& t2)
{
    return t1.severity > t2.severity;
}