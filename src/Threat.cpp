#include "Threat.h"
#include <iostream>

using namespace std;

// ============================================================
// OOP CONCEPT: STATIC VARIABLE DEFINITION
// ------------------------------------------------------------
// The static member is *declared* inside the class but must be
// *defined* exactly once, outside the class, like this. All
// Threat objects share this single variable.
// ============================================================
int Threat::threatCount = 0;


// ---------- Nested class: ThreatLevel ----------

Threat::ThreatLevel::ThreatLevel(int lvl)
{
    level = lvl;
}

int Threat::ThreatLevel::value() const
{
    return level;
}

string Threat::ThreatLevel::describe() const
{
    if (level >= 5) return "CRITICAL";
    if (level == 4) return "HIGH";
    if (level == 3) return "MEDIUM";
    if (level == 2) return "LOW";
    return "INFO";
}

ostream& operator<<(ostream& out, const Threat::ThreatLevel& tl)
{
    out << tl.describe() << " (" << tl.level << ")";
    return out;
}


// ---------- Threat ----------

Threat::Threat(
    string id,
    string type,
    string ip,
    int sev,
    string stat
)
{
    threatId = id;
    threatType = type;
    sourceIp = ip;
    severity = sev;
    status = stat;

    // Every time a new Threat is detected (created through this
    // constructor), the shared counter grows by one. Copies made
    // when a Threat is placed in a vector use the compiler's copy
    // constructor and deliberately do NOT count as new detections,
    // so the counter stays equal to the number of threats detected.
    threatCount++;
}

string Threat::getThreatId() const    { return threatId; }
string Threat::getThreatType() const  { return threatType; }
string Threat::getSourceIp() const    { return sourceIp; }
int    Threat::getSeverity() const    { return severity; }
string Threat::getStatus() const      { return status; }

Threat::ThreatLevel Threat::getLevel() const
{
    return ThreatLevel(severity);
}

void Threat::updateStatus(string newStatus)
{
    // OOP CONCEPT: this POINTER - "this->status" is the member,
    // "newStatus" is the parameter. this-> removes any ambiguity.
    this->status = newStatus;
}

void Threat::displayThreat() const
{
    cout << "\n--- Threat Detected ---" << endl;
    cout << "Threat ID   : " << threatId << endl;
    cout << "Threat Type : " << threatType << endl;
    cout << "Source IP   : " << sourceIp << endl;
    cout << "Risk Level  : " << getLevel() << endl;   // uses operator<<
    cout << "Status      : " << status << endl;
}

int Threat::getThreatCount()
{
    return threatCount;
}


// ============================================================
// OOP CONCEPT: FRIEND FUNCTION + OPERATOR OVERLOADING
// ------------------------------------------------------------
// These are NOT members of Threat, but because Threat declared
// them "friend", they may read threat's private fields directly.
// ============================================================

ostream& operator<<(ostream& out, const Threat& threat)
{
    out << "[" << threat.threatId << "] "
        << threat.threatType
        << " | Risk: " << threat.getLevel()
        << " | Source: " << threat.sourceIp
        << " | Status: " << threat.status;
    return out;
}

// Compares two threats by severity (enables threat1 > threat2).
bool operator>(const Threat& t1, const Threat& t2)
{
    return t1.severity > t2.severity;
}
