#include "EventInfo.h"

using namespace std;

EventInfo::EventInfo(string ip)
{
    this->sourceIp = ip;
}

string EventInfo::getSourceIp() const
{
    return this->sourceIp;
}
