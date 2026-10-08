#include "DetectionRule.h"
#include "LoginEvent.h"
#include "NetworkEvent.h"
#include <iostream>

using namespace std;

DetectionRule::DetectionRule(
    string id,
    string name,
    string condition,
    int threshold,
    bool enabled
)
{
    ruleId = id;
    ruleName = name;
    conditionType = condition;
    severityThreshold = threshold;
    isEnabled = enabled;
}

string DetectionRule::getRuleId() const   { return ruleId; }
string DetectionRule::getRuleName() const { return ruleName; }
bool DetectionRule::getIsEnabled() const  { return isEnabled; }

void DetectionRule::enable()  { isEnabled = true; }
void DetectionRule::disable() { isEnabled = false; }

bool DetectionRule::matches(const SecurityEvent& event) const
{
    // A disabled rule never matches anything.
    if (!isEnabled)
    {
        return false;
    }

    if (conditionType == "FAILED_LOGIN")
    {
        // Only LoginEvent objects can satisfy this rule.
        // dynamic_cast tells us at runtime whether the event really
        // is a LoginEvent, without assuming it.
        const LoginEvent* login = dynamic_cast<const LoginEvent*>(&event);
        if (login == nullptr)
        {
            return false;
        }
        return login->isFailedLogin()
               && event.getSeverity() >= severityThreshold;
    }

    if (conditionType == "OPEN_PORT")
    {
        const NetworkEvent* net = dynamic_cast<const NetworkEvent*>(&event);
        if (net == nullptr)
        {
            return false;
        }
        // Ports 22 (SSH) and 3389 (RDP) are treated as risky here.
        return (net->getDestinationPort() == 22
                || net->getDestinationPort() == 3389)
               && event.getSeverity() >= severityThreshold;
    }

    if (conditionType == "HIGH_SEVERITY")
    {
        return event.getSeverity() >= severityThreshold;
    }

    return false;
}

string DetectionRule::describe() const
{
    return ruleId + " (" + ruleName + ")"
           + (isEnabled ? " [ENABLED]" : " [DISABLED]");
}
