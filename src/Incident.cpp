#include "Incident.h"
#include <iostream>

using namespace std;

int Incident::incidentCount = 0;

Incident::Incident(
    string id,
    string ttl,
    int sev,
    string time,
    string desc
)
{
    incidentId = id;
    title = ttl;
    severity = sev;
    createdAt = time;
    description = desc;
    status = "OPEN";
    incidentCount++;
}

string Incident::getIncidentId() const { return incidentId; }
string Incident::getTitle() const      { return title; }
int    Incident::getSeverity() const   { return severity; }
string Incident::getStatus() const     { return status; }

void Incident::updateStatus(string newStatus)
{
    status = newStatus;
}

void Incident::addAlert(Alert* alert)
{
    // UC-02 step 7: associate the alert with the incident.
    alerts.push_back(alert);
}

void Incident::addEvidence(Evidence* evidence)
{
    // UC-01: store the evidence gathered during investigation.
    evidenceList.push_back(evidence);
}

bool Incident::executeResponse(ResponseAction* action, Device& device)
{
    // UC-03: perform the simulated response, then record it.
    bool ok = action->execute(device);
    actions.push_back(action);

    // Update the incident status based on the outcome.
    if (ok)
    {
        status = "CONTAINED";
    }
    return ok;
}

void Incident::displayIncident() const
{
    cout << "\n--- Incident ---" << endl;
    cout << "Incident ID : " << incidentId << endl;
    cout << "Title       : " << title << endl;
    cout << "Severity    : " << severity << endl;
    cout << "Status      : " << status << endl;
    cout << "Created At  : " << createdAt << endl;
    cout << "Description : " << description << endl;
    cout << "Alerts      : " << alerts.size() << endl;
    cout << "Evidence    : " << evidenceList.size() << endl;
    cout << "Actions     : " << actions.size() << endl;
}

void Incident::displayFullReport() const
{
    displayIncident();

    if (!alerts.empty())
    {
        cout << "\n  Related Alerts:" << endl;
        for (size_t i = 0; i < alerts.size(); i++)
        {
            cout << "   * " << *alerts[i] << endl;   // uses operator<<
        }
    }

    if (!evidenceList.empty())
    {
        cout << "\n  Evidence:" << endl;
        for (size_t i = 0; i < evidenceList.size(); i++)
        {
            cout << "   * " << *evidenceList[i] << endl;   // uses operator<<
        }
    }

    if (!actions.empty())
    {
        cout << "\n  Response Actions:" << endl;
        for (size_t i = 0; i < actions.size(); i++)
        {
            cout << "   * " << *actions[i] << endl;   // uses operator<<
        }
    }
}

int Incident::getIncidentCount()
{
    return incidentCount;
}

int Incident::getEvidenceCount() const
{
    return (int)evidenceList.size();
}

ostream& operator<<(ostream& out, const Incident& incident)
{
    out << "[" << incident.incidentId << "] "
        << incident.title
        << " | sev=" << incident.severity
        << " | status=" << incident.status
        << " | alerts=" << incident.alerts.size()
        << " evidence=" << incident.evidenceList.size()
        << " actions=" << incident.actions.size();
    return out;
}
