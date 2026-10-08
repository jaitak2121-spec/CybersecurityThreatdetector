#ifndef SECURITYREPORT_H
#define SECURITYREPORT_H

#include "Incident.h"
#include "Alert.h"
#include "Threat.h"
#include "SecurityLog.h"
#include <string>
#include <vector>

using namespace std;

// ============================================================
// SecurityReport
// ------------------------------------------------------------
// Produces the end-of-run summary: how many threats, alerts,
// incidents and response actions occurred, what the highest risk
// level was, and what was written to the log.
//
// OOP CONCEPTS DEMONSTRATED HERE:
//  - ENCAPSULATION : it gathers its figures through the public
//    interfaces of the other classes, rather than reaching into
//    their data.
//  - ABSTRACTION   : generateSummary() presents one clear result.
// ============================================================

class SecurityReport
{
private:
    string reportId;
    string generatedAt;
    string periodCovered;

public:
    SecurityReport(
        string id,
        string time,
        string period
    );

    // Builds and prints the report from the live simulator data.
    void generateSummary(
        const vector<Threat>& threats,
        const vector<Alert*>& alerts,
        const vector<Incident*>& incidents,
        const SecurityLog& log
    ) const;

    void displayReportHeader() const;
};

#endif
