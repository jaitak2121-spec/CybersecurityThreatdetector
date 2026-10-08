#ifndef DETECTIONRULE_H
#define DETECTIONRULE_H

#include "SecurityEvent.h"
#include <string>

using namespace std;

// ============================================================
// DetectionRule
// ------------------------------------------------------------
// Defines ONE condition that, when satisfied by a security event,
// means the event is suspicious. Examples used in the simulator:
//
//   - "FAILED_LOGIN"  : a failed login with severity >= 4
//   - "OPEN_PORT"     : a network event to a risky port (e.g. 22)
//   - "HIGH_SEVERITY" : any event with severity >= 4
//
// OOP CONCEPTS DEMONSTRATED HERE:
//  - ABSTRACTION   : matches() hides the comparison logic.
//  - ENCAPSULATION : rule fields are private.
// ============================================================

class DetectionRule
{
private:
    string ruleId;
    string ruleName;
    string conditionType;     // which check to perform
    int severityThreshold;    // minimum severity for the rule
    bool isEnabled;

public:
    DetectionRule(
        string id,
        string name,
        string condition,
        int threshold,
        bool enabled
    );

    string getRuleId() const;
    string getRuleName() const;
    bool getIsEnabled() const;

    void enable();
    void disable();

    // Evaluates one event against this rule.
    // Returns true when the rule is triggered.
    bool matches(const SecurityEvent& event) const;

    // A short human-readable description for logging.
    string describe() const;
};

#endif
