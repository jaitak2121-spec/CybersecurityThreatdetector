#include "Alert.h"
#include <iostream>

using namespace std;

// Static member must be defined once, outside the class.
int Alert::alertCount = 0;

Alert::Alert(
    string id,
    string time,
    int sev,
    string desc
)
{
    alertId = id;
    timestamp = time;
    severity = sev;
    description = desc;
    status = "OPEN";
    alertCount++;
}

string Alert::getAlertId() const      { return alertId; }
int    Alert::getSeverity() const     { return severity; }
string Alert::getStatus() const       { return status; }
string Alert::getDescription() const  { return description; }

void Alert::updateStatus(string newStatus)
{
    status = newStatus;
}

void Alert::markFalsePositive(string reason)
{
    // Alternate Flow 2 of UC-01: a false positive is closed.
    status = "CLOSED";
    description += " | Marked false positive: " + reason;
}

bool Alert::isEscalatable() const
{
    // Severity >= 4 (HIGH/CRITICAL) is worth an incident.
    return severity >= 4;
}

void Alert::displayAlert() const
{
    cout << "\n--- Alert ---" << endl;
    cout << "Alert ID    : " << alertId << endl;
    cout << "Timestamp   : " << timestamp << endl;
    cout << "Severity    : " << severity << endl;
    cout << "Status      : " << status << endl;
    cout << "Description : " << description << endl;
}

int Alert::getAlertCount()
{
    return alertCount;
}

ostream& operator<<(ostream& out, const Alert& alert)
{
    out << "[" << alert.alertId << "] sev=" << alert.severity
        << " status=" << alert.status
        << " :: " << alert.description;
    return out;
}
