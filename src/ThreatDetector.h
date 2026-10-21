#ifndef THREATDETECTOR_H
#define THREATDETECTOR_H

#include "SecurityEvent.h"
#include "Threat.h"
#include "DetectionRule.h"
#include <string>
#include <vector>

using namespace std;

// ============================================================
// ThreatDetector
// ------------------------------------------------------------
// Turns security events into threats.
//
// OOP CONCEPTS DEMONSTRATED HERE:
//  - FUNCTION OVERLOADING : three different detectThreat()
//    functions, chosen by their parameter list.
//  - POLYMORPHISM / POINTERS TO DERIVED CLASSES : the rule-based
//    detector receives a SecurityEvent* that may point at a
//    LoginEvent or a NetworkEvent, and relies on virtual
//    functions and dynamic_cast to inspect it.
//  - ENCAPSULATION : the list of rules is private.
//
// It also detects the brute-force pattern from the object
// diagram: several failed logins from the same source IP.
// ============================================================

class ThreatDetector
{
private:
    vector<DetectionRule> rules;   // the configured rules
    int threatCounter;             // used to give threats unique ids

public:
    ThreatDetector();

    // --- Rule configuration ---
    void addRule(const DetectionRule& rule);
    void listRules() const;

    // --- Overload 1: evaluate an event against the configured rules ---
    Threat detectThreat(const SecurityEvent& event);

    // --- Overload 2: evaluate using raw values (kept from before) ---
    Threat detectThreat(
        string eventType,
        int severity,
        string sourceIp
    );

    // --- Overload 3: brute-force pattern over a set of events ---
    // Counts failed logins from one source IP; if the number
    // reaches "threshold", the activity is treated as a possible
    // brute-force attack.
    Threat detectThreat(
        const vector<SecurityEvent*>& events,
        string sourceIp,
        int threshold
    );

    // Counts failed logins from a given IP (used by overload 3).
    int countFailedLoginsFrom(
        const vector<SecurityEvent*>& events,
        string sourceIp
    ) const;
};

#endif
