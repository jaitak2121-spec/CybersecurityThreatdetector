#include "ThreatDetector.h"
#include <iostream>

using namespace std;

ThreatDetector::ThreatDetector()
{
    cout << "Threat Detector initialized." << endl;
}

Threat ThreatDetector::detectThreat(const SecurityEvent& event)
{
    cout << "\nAnalyzing security event..." << endl;

    if (event.getSeverity() >= 4)
    {
        cout << "High severity event detected." << endl;

        return Threat(
            "THREAT-001",
            "Suspicious Security Activity",
            event.getSourceIp(),
            event.getSeverity(),
            "ACTIVE"
        );
    }

    cout << "No significant threat detected." << endl;

    return Threat(
        "THREAT-000",
        "No Significant Threat",
        event.getSourceIp(),
        event.getSeverity(),
        "NORMAL"
    );
}

Threat ThreatDetector::detectThreat(
    string eventType,
    int severity,
    string sourceIp
)
{
    cout << "\nAnalyzing event using event type and severity..." << endl;

    string threatType;

    if (eventType == "LOGIN_EVENT" && severity >= 4)
    {
        threatType = "Possible Brute Force Attack";
    }
    else if (eventType == "NETWORK_EVENT" && severity >= 4)
    {
        threatType = "Suspicious Network Activity";
    }
    else
    {
        threatType = "Low Risk Activity";
    }

    string status = (severity >= 4) ? "ACTIVE" : "NORMAL";

    return Threat(
        "THREAT-002",
        threatType,
        sourceIp,
        severity,
        status
    );
}