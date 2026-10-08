#include "Threat.h"
#include <iostream>

using namespace std;

<<<<<<< HEAD
// Definition of static variable
int Threat::threatCount = 0;


// Constructor
=======
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

>>>>>>> dd8f70d (Updated security events and combined all)
Threat::Threat(
    string id,
    string type,
    string ip,
    int sev,
    string stat
)
{
<<<<<<< HEAD
    // Demonstration of this pointer
    this->threatId = id;
    this->threatType = type;
    this->sourceIp = ip;
    this->severity = sev;
    this->status = stat;

    threatCount++;
}


// Getter functions
string Threat::getThreatId() const
{
    return this->threatId;
=======
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
>>>>>>> dd8f70d (Updated security events and combined all)
}

void Threat::updateStatus(string newStatus)
{
<<<<<<< HEAD
    return this->threatType;
}

int Threat::getSeverity() const
{
    return this->severity;
=======
    // OOP CONCEPT: this POINTER - "this->status" is the member,
    // "newStatus" is the parameter. this-> removes any ambiguity.
    this->status = newStatus;
>>>>>>> dd8f70d (Updated security events and combined all)
}


// Display threat
void Threat::displayThreat() const
{
    cout << "\n--- Threat Detected ---" << endl;
<<<<<<< HEAD

    cout << "Threat ID   : " << this->threatId << endl;
    cout << "Threat Type : " << this->threatType << endl;
    cout << "Source IP   : " << this->sourceIp << endl;
    cout << "Severity    : " << this->severity << endl;

    cout << "Risk Level  : "
         << ThreatLevel::getLevel(this->severity)
         << endl;

    cout << "Status      : " << this->status << endl;
}


// Static function
=======
    cout << "Threat ID   : " << threatId << endl;
    cout << "Threat Type : " << threatType << endl;
    cout << "Source IP   : " << sourceIp << endl;
    cout << "Risk Level  : " << getLevel() << endl;   // uses operator<<
    cout << "Status      : " << status << endl;
}

>>>>>>> dd8f70d (Updated security events and combined all)
int Threat::getThreatCount()
{
    return threatCount;
}


<<<<<<< HEAD
// Friend operator > overloading
bool operator>(
    const Threat& t1,
    const Threat& t2
)
{
    return t1.severity > t2.severity;
}


// Friend stream operator << overloading
ostream& operator<<(
    ostream& out,
    const Threat& threat
)
{
    out << "\n--- Threat Details ---" << endl;

    out << "Threat ID   : "
        << threat.threatId << endl;

    out << "Threat Type : "
        << threat.threatType << endl;

    out << "Source IP   : "
        << threat.sourceIp << endl;

    out << "Severity    : "
        << threat.severity << endl;

    out << "Risk Level  : "
        << Threat::ThreatLevel::getLevel(threat.severity)
        << endl;

    out << "Status      : "
        << threat.status << endl;

    return out;
}
=======
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
>>>>>>> dd8f70d (Updated security events and combined all)
