#ifndef THREAT_H
#define THREAT_H

#include <string>
#include <iostream>

using namespace std;

// ============================================================
// Threat
// ------------------------------------------------------------
// OOP CONCEPTS DEMONSTRATED HERE:
//
// 1. NESTED CLASS        : ThreatLevel is declared *inside* Threat.
//    Because it belongs only to Threat, it is scoped as
//    Threat::ThreatLevel and does not clutter the global namespace.
//
// 2. STATIC VARIABLE     : threatCount is shared by ALL Threat
//    objects (one copy for the whole class, not one per object).
//
// 3. STATIC FUNCTION     : getThreatCount() reads that shared
//    counter and is called as Threat::getThreatCount(), without
//    needing any particular Threat object.
//
// 4. FRIEND FUNCTION     : operator<< and operator> are declared
//    "friend" so they may read Threat's private data directly.
//
// 5. OPERATOR OVERLOADING: operator<< lets a Threat be printed
//    with cout << threat; operator> compares two threats.
//
// 6. this POINTER        : updateStatus() uses this->status.
// ============================================================

class Threat
{
public:
    // --------------------------------------------------------
    // OOP CONCEPT: NESTED CLASS
    // A small helper class that wraps the numeric severity and
    // turns it into a human-readable risk label. It lives inside
    // Threat, so it is written as Threat::ThreatLevel.
    // --------------------------------------------------------
    class ThreatLevel
    {
    private:
        int level;   // 1..5

    public:
        ThreatLevel(int lvl);

        string describe() const;   // e.g. "CRITICAL"
        int value() const;

        // Friend operator for ThreatLevel as well.
        friend ostream& operator<<(ostream& out, const ThreatLevel& tl);
    };

private:

    // Nested class
    class ThreatLevel
    {
    public:
        static string getLevel(int severity)
        {
            if (severity >= 5)
                return "CRITICAL";
            else if (severity >= 4)
                return "HIGH";
            else if (severity >= 2)
                return "MEDIUM";
            else
                return "LOW";
        }
    };

    // Static variable
    static int threatCount;

    string threatId;
    string threatType;
    string sourceIp;
    int severity;                 // 1..5
    string status;                // ACTIVE / CONTAINED / NORMAL

    // OOP CONCEPT: STATIC VARIABLE (shared counter, defined in .cpp)
    // Counts how many Threat objects have been created (i.e. detected)
    // during the whole run. One copy exists for the entire class, not
    // one per object.
    static int threatCount;

public:

    Threat(
        string id,
        string type,
        string ip,
        int sev,
        string stat
    );

    // --- accessors (encapsulation) ---
    string getThreatId() const;
    string getThreatType() const;
    string getSourceIp() const;
    int getSeverity() const;
    string getStatus() const;

    // Returns the nested-class view of the severity.
    ThreatLevel getLevel() const;

    // Uses the this pointer to update the status.
    void updateStatus(string newStatus);

    void displayThreat() const;

<<<<<<< HEAD
    // Static function
    static int getThreatCount();

    // Friend operator overloading
    friend bool operator>(
        const Threat& t1,
        const Threat& t2
    );

    // Stream operator overloading using friend function
    friend ostream& operator<<(
        ostream& out,
        const Threat& threat
    );
=======
    // --- OOP CONCEPT: STATIC FUNCTION ---
    // Called as Threat::getThreatCount(); no object required.
    static int getThreatCount();

    // --- OOP CONCEPT: FRIEND FUNCTIONS / OPERATOR OVERLOADING ---
    friend ostream& operator<<(ostream& out, const Threat& threat);
    friend bool operator>(const Threat& t1, const Threat& t2);
>>>>>>> dd8f70d (Updated security events and combined all)
};

#endif
