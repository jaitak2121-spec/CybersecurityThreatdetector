#ifndef SECURITYLOG_H
#define SECURITYLOG_H

#include <string>
#include <vector>

using namespace std;

// ============================================================
// SecurityLog
// ------------------------------------------------------------
// Records everything the simulator does: events received, rules
// triggered, alerts raised, incidents created, evidence added,
// and response actions taken. This gives the system an audit
// trail and feeds the final SecurityReport.
//
// OOP CONCEPTS DEMONSTRATED HERE:
//  - ENCAPSULATION : the internal vector of entries is private.
//  - STATIC VARIABLE + STATIC FUNCTION : logCount tracks how many
//    log entries exist across the whole class.
//  - NESTED CLASS : a LogEntry struct-like class describes one
//    record, scoped as SecurityLog::LogEntry.
// ============================================================

class SecurityLog
{
public:
    // --------------------------------------------------------
    // OOP CONCEPT: NESTED CLASS
    // One record in the log. It belongs to SecurityLog only.
    // --------------------------------------------------------
    class LogEntry
    {
    private:
        string timestamp;
        string eventType;
        string message;
        string sourceComponent;

    public:
        LogEntry(
            string time,
            string type,
            string msg,
            string source
        );

        string getEventType() const;
        string getMessage() const;
        string getSourceComponent() const;

        void display() const;
    };

private:
    vector<LogEntry> entries;      // the audit trail
    static int logCount;           // shared counter

public:
    SecurityLog();

    // Appends one record to the audit trail.
    void writeLogEntry(
        string timestamp,
        string eventType,
        string message,
        string sourceComponent
    );

    // Prints every record in order.
    void printAll() const;

    int getEntryCount() const;

    static int getLogCount();

    // Simple query used by the report: count entries of a type.
    int countByType(string eventType) const;
};

#endif
