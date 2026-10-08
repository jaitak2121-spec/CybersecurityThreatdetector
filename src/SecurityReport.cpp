#include "SecurityReport.h"
#include <iostream>

using namespace std;

SecurityReport::SecurityReport(
    string id,
    string time,
    string period
)
{
    reportId = id;
    generatedAt = time;
    periodCovered = period;
}

void SecurityReport::displayReportHeader() const
{
    cout << "\n==============================================" << endl;
    cout << " SECURITY REPORT" << endl;
    cout << "==============================================" << endl;
    cout << "Report ID      : " << reportId << endl;
    cout << "Generated At   : " << generatedAt << endl;
    cout << "Period Covered : " << periodCovered << endl;
}

void SecurityReport::generateSummary(
    const vector<Threat>& threats,
    const vector<Alert*>& alerts,
    const vector<Incident*>& incidents,
    const SecurityLog& log
) const
{
    displayReportHeader();

    // ---- Count threats by risk level using the nested class ----
    int critical = 0, high = 0, medium = 0, low = 0;
    for (size_t i = 0; i < threats.size(); i++)
    {
        string level = threats[i].getLevel().describe();
        if (level == "CRITICAL")     critical++;
        else if (level == "HIGH")    high++;
        else if (level == "MEDIUM")  medium++;
        else                         low++;
    }

    cout << "\n--- Threat Summary ---" << endl;
    cout << "Threats detected        : " << threats.size() << endl;
    cout << "  CRITICAL              : " << critical << endl;
    cout << "  HIGH                  : " << high << endl;
    cout << "  MEDIUM                : " << medium << endl;
    cout << "  LOW / INFO            : " << low << endl;

    cout << "\n--- Alert Summary ---" << endl;
    cout << "Alerts raised           : " << alerts.size() << endl;
    int escalated = 0;
    for (size_t i = 0; i < alerts.size(); i++)
    {
        if (alerts[i]->getStatus() == "ESCALATED")
        {
            escalated++;
        }
    }
    cout << "  Escalated to incident : " << escalated << endl;

    cout << "\n--- Incident Summary ---" << endl;
    cout << "Incidents created       : " << incidents.size() << endl;
    int totalEvidence = 0;
    for (size_t i = 0; i < incidents.size(); i++)
    {
        totalEvidence += incidents[i]->getEvidenceCount();
    }
    cout << "Evidence items collected: " << totalEvidence << endl;

    cout << "\n--- Log Summary ---" << endl;
    cout << "Log entries recorded    : " << log.getEntryCount() << endl;
    cout << "  EVENTS                : "
         << log.countByType("EVENT") << endl;
    cout << "  DETECTION             : "
         << log.countByType("DETECTION") << endl;
    cout << "  ALERT                 : "
         << log.countByType("ALERT") << endl;
    cout << "  INCIDENT              : "
         << log.countByType("INCIDENT") << endl;
    cout << "  RESPONSE              : "
         << log.countByType("RESPONSE") << endl;

    cout << "\n--- Overall Assessment ---" << endl;
    if (critical > 0)
    {
        cout << "System status: CRITICAL activity detected and contained." << endl;
    }
    else if (high > 0)
    {
        cout << "System status: HIGH-risk activity detected." << endl;
    }
    else
    {
        cout << "System status: No significant threats detected." << endl;
    }

    cout << "\n(All values above are from a SAFE simulation.)" << endl;
    cout << "==============================================" << endl;
}
