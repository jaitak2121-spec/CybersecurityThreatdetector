#ifndef THREAT_H
#define THREAT_H

#include <string>
#include <iostream>

using namespace std;

class Threat
{
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
    int severity;
    string status;

public:

    // Constructor
    Threat(
        string id,
        string type,
        string ip,
        int sev,
        string stat
    );

    string getThreatId() const;
    string getThreatType() const;
    int getSeverity() const;

    void displayThreat() const;

    // Static function
    static int getThreatCount();

    // Existing operator overloading using friend function
    friend bool operator>(
        const Threat& t1,
        const Threat& t2
    );

    // NEW: Stream operator overloading using friend function
    friend ostream& operator<<(
        ostream& out,
        const Threat& threat
    );
};

#endif
