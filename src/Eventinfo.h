#ifndef EVENTINFO_H
#define EVENTINFO_H

#include <string>
using namespace std;

class EventInfo
{
protected:
    string sourceIp;

public:
    EventInfo(string ip);
    virtual ~EventInfo() = default;

    string getSourceIp() const;
};

#endif
