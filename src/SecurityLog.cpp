#include "SecurityLog.h"
#include <iostream>

using namespace std;

// Static member definition.
int SecurityLog::logCount = 0;


// ---------- Nested class: LogEntry ----------

SecurityLog::LogEntry::LogEntry(
    string time,
    string type,
    string msg,
    string source
)
{
    timestamp = time;
    eventType = type;
    message = msg;
    sourceComponent = source;
}

string SecurityLog::LogEntry::getEventType() const
{
    return eventType;
}

string SecurityLog::LogEntry::getMessage() const
{
    return message;
}

string SecurityLog::LogEntry::getSourceComponent() const
{
    return sourceComponent;
}

void SecurityLog::LogEntry::display() const
{
    cout << "[" << timestamp << "] "
         << "(" << eventType << ") "
         << message
         << "  <" << sourceComponent << ">" << endl;
}


// ---------- SecurityLog ----------

SecurityLog::SecurityLog()
{
    // nothing to initialize; the vector starts empty
}

void SecurityLog::writeLogEntry(
    string timestamp,
    string eventType,
    string message,
    string sourceComponent
)
{
    entries.push_back(
        LogEntry(timestamp, eventType, message, sourceComponent)
    );
    logCount++;
}

void SecurityLog::printAll() const
{
    cout << "\n===== SECURITY LOG =====" << endl;
    if (entries.empty())
    {
        cout << "No log entries recorded." << endl;
        return;
    }
    for (size_t i = 0; i < entries.size(); i++)
    {
        cout << (i + 1) << ". ";
        entries[i].display();
    }
}

int SecurityLog::getEntryCount() const
{
    return (int)entries.size();
}

int SecurityLog::getLogCount()
{
    return logCount;
}

int SecurityLog::countByType(string eventType) const
{
    int total = 0;
    for (size_t i = 0; i < entries.size(); i++)
    {
        if (entries[i].getEventType() == eventType)
        {
            total++;
        }
    }
    return total;
}
