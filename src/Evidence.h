#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <string>

using namespace std;

// ============================================================
// Evidence
// ------------------------------------------------------------
// Information collected while investigating an incident, e.g. a
// log extract, a list of failed logins, a suspicious connection.
//
// OOP CONCEPTS DEMONSTRATED HERE:
//  - ENCAPSULATION
//  - FRIEND FUNCTION + OPERATOR OVERLOADING : operator<< prints
//    an evidence record with cout << evidence;
// ============================================================

class Evidence
{
private:
    string evidenceId;
    string evidenceType;
    string source;
    string timestamp;
    string description;

public:
    Evidence(
        string id,
        string type,
        string src,
        string time,
        string desc
    );

    string getEvidenceId() const;
    string getEvidenceType() const;
    string getSource() const;
    string getDescription() const;

    void displayEvidence() const;

    // Friend stream operator (encapsulation kept, printing allowed).
    friend ostream& operator<<(ostream& out, const Evidence& evidence);
};

#endif
