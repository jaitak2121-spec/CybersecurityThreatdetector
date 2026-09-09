#include <iostream>

#include "SecurityEvent.h"
#include "LoginEvent.h"
#include "NetworkEvent.h"
#include "Threat.h"
#include "ThreatDetector.h"

using namespace std;

int main()
{
    cout << "========================================" << endl;
    cout << " Cybersecurity Threat Detection Simulator" << endl;
    cout << "========================================" << endl;


    // -----------------------------------------
    // 1. Create Login Event
    // -----------------------------------------

    LoginEvent loginEvent(
        "EVT-001",
        "2026-08-25 10:30:00",
        "203.0.113.19",
        5,
        "admin",
        false
    );

    loginEvent.displayEvent();


    // -----------------------------------------
    // 2. Create Network Event
    // -----------------------------------------

    NetworkEvent networkEvent(
        "EVT-002",
        "2026-08-25 10:32:00",
        "203.0.113.20",
        3,
        22,
        "TCP"
    );

    networkEvent.displayEvent();


    // -----------------------------------------
    // 3. Create Threat Detector
    // -----------------------------------------

    ThreatDetector detector;


    // -----------------------------------------
    // 4. Method Overloading
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Method Overloading Demonstration" << endl;
    cout << "========================================" << endl;

    Threat threat1 = detector.detectThreat(loginEvent);

    threat1.displayThreat();


    Threat threat2 = detector.detectThreat(
        "NETWORK_EVENT",
        4,
        "203.0.113.20"
    );

    threat2.displayThreat();


    // -----------------------------------------
    // 5. Operator Overloading
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Operator Overloading Demonstration" << endl;
    cout << "========================================" << endl;

    if (threat1 > threat2)
    {
        cout << "Threat 1 has higher severity than Threat 2."
             << endl;
    }
    else if (threat2 > threat1)
    {
        cout << "Threat 2 has higher severity than Threat 1."
             << endl;
    }
    else
    {
        cout << "Both threats have equal severity."
             << endl;
    }


    // -----------------------------------------
    // 6. Access Specifiers
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Access Specifier Demonstration" << endl;
    cout << "========================================" << endl;

    cout << "Event ID accessed through public method: "
         << loginEvent.getEventId()
         << endl;

    cout << "Direct access to private data is not allowed."
         << endl;


    cout << "\n========================================" << endl;
    cout << " Simulation Completed" << endl;
    cout << "========================================" << endl;

    return 0;
}