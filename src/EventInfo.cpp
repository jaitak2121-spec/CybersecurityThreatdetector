#include "EventInfo.h"
#include <iostream>

using namespace std;

EventInfo::EventInfo(string ip)
{
    sourceIp = ip;
}

string EventInfo::getSourceIp() const
{
    return sourceIp;
}

void EventInfo::displayInfo() const
{
    cout << "Source IP   : " << sourceIp << endl;
}
