#ifndef THREATDETECTOR_H
#define THREATDETECTOR_H

#include "SecurityEvent.h"
#include "Threat.h"
#include <string>

using namespace std;

class ThreatDetector
{
public:
    ThreatDetector();

    Threat detectThreat(const SecurityEvent& event);

    Threat detectThreat(
        string eventType,
        int severity,
        string sourceIp
    );
};

#endif