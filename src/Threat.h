#ifndef THREAT_H
#define THREAT_H

#include <string>
#include <iostream>

using namespace std;

class Threat
{
private:
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
    string threatId;
    string threatType;
    string sourceIp;
    int severity;
    string status;

public:
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

    // Existing operator overloading
    friend bool operator>(const Threat& t1, const Threat& t2);

    // NEW: stream operator overloading
    friend ostream& operator<<(ostream& out, const Threat& threat);
};

#endif
