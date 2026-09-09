#ifndef SECURITYEVENT_H
#define SECURITYEVENT_H
  
#include <string>

using namespace std;

class SecurityEvent
{
private:
    string eventId;
    string eventType;
    string timestamp;
    string sourceIp;
    int severity;

protected:
    string getEventType() const;
    int getSeverity() const;

public:
    SecurityEvent(
        string id,
        string type,
        string time,
        string ip,
        int sev
    );

    virtual ~SecurityEvent() = default;

    string getEventId() const;
    string getSourceIp() const;
    int getEventSeverity() const;

    virtual void displayEvent() const;
};

#endif