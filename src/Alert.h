#ifndef ALERT_H
#define ALERT_H

#include <string>

using namespace std;

// ============================================================
// Alert
// ------------------------------------------------------------
// A warning raised when a DetectionRule is triggered.
//
// OOP CONCEPTS DEMONSTRATED HERE:
//  - STATIC VARIABLE + STATIC FUNCTION : alertCount tracks how
//    many alerts exist, shared by all Alert objects.
//  - ENCAPSULATION / ABSTRACTION.
//  - FRIEND FUNCTION + OPERATOR OVERLOADING : operator<< prints
//    an alert with cout << alert;
// ============================================================

class Alert
{
private:
    string alertId;
    string timestamp;
    int severity;
    string status;            // OPEN / INVESTIGATING / ESCALATED / CLOSED
    string description;

    static int alertCount;    // shared counter

public:
    Alert(
        string id,
        string time,
        int sev,
        string desc
    );

    string getAlertId() const;
    int getSeverity() const;
    string getStatus() const;
    string getDescription() const;

    void updateStatus(string newStatus);
    void markFalsePositive(string reason);

    // A serious alert can be escalated into an incident.
    bool isEscalatable() const;

    void displayAlert() const;

    static int getAlertCount();

    friend ostream& operator<<(ostream& out, const Alert& alert);
};

#endif
