#include "ThreatDetector.h"
#include "LoginEvent.h"
#include "NetworkEvent.h"
#include <iostream>

using namespace std;

ThreatDetector::ThreatDetector()
{
    threatCounter = 0;
    cout << "Threat Detector initialized." << endl;
}

void ThreatDetector::addRule(const DetectionRule& rule)
{
    rules.push_back(rule);
}

void ThreatDetector::listRules() const
{
    cout << "\nConfigured Detection Rules:" << endl;
    if (rules.empty())
    {
        cout << "  (none)" << endl;
        return;
    }
    for (size_t i = 0; i < rules.size(); i++)
    {
        cout << "  - " << rules[i].describe() << endl;
    }
}

// ------------------------------------------------------------
// Overload 1 : evaluate one event against every configured rule.
// The parameter is a const SecurityEvent& so it accepts both a
// LoginEvent and a NetworkEvent (polymorphism).
// ------------------------------------------------------------
Threat ThreatDetector::detectThreat(const SecurityEvent& event)
{
    cout << "\nAnalyzing security event " << event.getEventId()
         << " against " << rules.size() << " rule(s)..." << endl;

    // Try each rule until one matches.
    for (size_t i = 0; i < rules.size(); i++)
    {
        if (rules[i].matches(event))
        {
            cout << "  Rule triggered: " << rules[i].getRuleName() << endl;

            threatCounter++;

            string type = "Suspicious Activity";
            if (dynamic_cast<const LoginEvent*>(&event) != nullptr)
            {
                type = "Credential Access - Failed Login";
            }
            else if (dynamic_cast<const NetworkEvent*>(&event) != nullptr)
            {
                type = "Suspicious Network Activity";
            }

            return Threat(
                "THREAT-" + to_string(threatCounter),
                type,
                event.getSourceIp(),
                event.getSeverity(),
                "ACTIVE"
            );
        }
    }

    // No rule matched.
    cout << "  No rule triggered - activity treated as low risk." << endl;
    threatCounter++;
    return Threat(
        "THREAT-" + to_string(threatCounter),
        "No Significant Threat",
        event.getSourceIp(),
        event.getSeverity(),
        "NORMAL"
    );
}

// ------------------------------------------------------------
// Overload 2 : evaluate using raw values, without an event object.
// Kept from the original implementation so the overload demo is
// still visible in the viva.
// ------------------------------------------------------------
Threat ThreatDetector::detectThreat(
    string eventType,
    int severity,
    string sourceIp
)
{
    cout << "\nAnalyzing event using event type and severity..." << endl;

    threatCounter++;

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
        "THREAT-" + to_string(threatCounter),
        threatType,
        sourceIp,
        severity,
        status
    );
}

// ------------------------------------------------------------
// Overload 3 : brute-force pattern detection.
// This is the scenario shown in the object diagram.
// ------------------------------------------------------------
Threat ThreatDetector::detectThreat(
    const vector<SecurityEvent*>& events,
    string sourceIp,
    int threshold
)
{
    cout << "\nChecking for brute-force pattern from "
         << sourceIp << " (threshold " << threshold << ")..." << endl;

    int failures = countFailedLoginsFrom(events, sourceIp);

    threatCounter++;

    if (failures >= threshold)
    {
        cout << "  " << failures << " failed logins detected - "
             << "brute-force pattern confirmed." << endl;

        // Multiple failures escalate the severity to CRITICAL (5).
        int sev = 5;
        if (failures >= threshold * 2)
        {
            sev = 5;   // CRITICAL
        }
        else
        {
            sev = 4;   // HIGH
        }

        return Threat(
            "THREAT-" + to_string(threatCounter),
            "Credential Access - Brute Force",
            sourceIp,
            sev,
            "ACTIVE"
        );
    }

    cout << "  Only " << failures << " failed login(s) - below threshold."
         << endl;

    return Threat(
        "THREAT-" + to_string(threatCounter),
        "No Brute-Force Pattern",
        sourceIp,
        1,
        "NORMAL"
    );
}

int ThreatDetector::countFailedLoginsFrom(
    const vector<SecurityEvent*>& events,
    string sourceIp
) const
{
    int count = 0;
    for (size_t i = 0; i < events.size(); i++)
    {
        // Only events from this IP matter.
        if (events[i]->getSourceIp() != sourceIp)
        {
            continue;
        }

        // dynamic_cast confirms at runtime that this event really
        // is a LoginEvent before we use login-specific methods.
        const LoginEvent* login =
            dynamic_cast<const LoginEvent*>(events[i]);

        if (login != nullptr && login->isFailedLogin())
        {
            count++;
        }
    }
    return count;
}
