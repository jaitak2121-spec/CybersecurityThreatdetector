#ifndef INCIDENT_H
#define INCIDENT_H

#include "Alert.h"
#include "Evidence.h"
#include "ResponseAction.h"
#include "Device.h"
#include "Threat.h"
#include <string>
#include <vector>

using namespace std;

// ============================================================
// Incident
// ------------------------------------------------------------
// A confirmed security issue that needs investigation and/or a
// response. It groups together the alert(s), the threat, the
// evidence collected, and the response actions taken.
//
// OOP CONCEPTS DEMONSTRATED HERE:
//  - ENCAPSULATION : related objects are stored in private
//    vectors and reached through small public methods.
//  - STATIC VARIABLE + STATIC FUNCTION : incidentCount tracks how
//    many incidents exist.
//  - FRIEND FUNCTION + OPERATOR OVERLOADING : operator<< prints
//    an incident summary.
//
// NOTE: the Incident stores POINTERS to the related objects
// (Alert*, Evidence*, ResponseAction*). This avoids copying large
// objects and demonstrates pointers-to-objects in a real context.
// ============================================================

class Incident
{
private:
    string incidentId;
    string title;
    int severity;
    string status;                 // OPEN / INVESTIGATING / CONTAINED / CLOSED
    string createdAt;
    string description;

    vector<Alert*> alerts;             // associated alerts
    vector<Evidence*> evidenceList;    // collected evidence
    vector<ResponseAction*> actions;   // actions taken

    static int incidentCount;

public:
    Incident(
        string id,
        string ttl,
        int sev,
        string time,
        string desc
    );

    string getIncidentId() const;
    string getTitle() const;
    int getSeverity() const;
    string getStatus() const;

    void updateStatus(string newStatus);

    // UC-02: associate an alert with this incident.
    void addAlert(Alert* alert);

    // UC-01: attach evidence gathered during investigation.
    void addEvidence(Evidence* evidence);

    // UC-03: run a response action and store it.
    bool executeResponse(ResponseAction* action, Device& device);

    void displayIncident() const;

    // Prints everything grouped under this incident.
    void displayFullReport() const;

    static int getIncidentCount();
    int getEvidenceCount() const;

    friend ostream& operator<<(ostream& out, const Incident& incident);
};

#endif
