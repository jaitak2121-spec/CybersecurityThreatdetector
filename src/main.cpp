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
        "2026-09-17 10:30:00",
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
        "2026-09-17 10:32:00",
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
    cout << " Method Overloading" << endl;
    cout << "========================================" << endl;

    Threat threat1 = detector.detectThreat(loginEvent);

    Threat threat2 = detector.detectThreat(
        "NETWORK_EVENT",
        4,
        "203.0.113.20"
    );


    // -----------------------------------------
    // 5. Stream Operator Overloading
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Stream Operator Overloading" << endl;
    cout << "========================================" << endl;

    cout << threat1;
    cout << threat2;


    // -----------------------------------------
    // 6. Existing > Operator Overloading
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Operator > Overloading" << endl;
    cout << "========================================" << endl;

    if (threat1 > threat2)
    {
        cout << "Threat 1 has higher severity." << endl;
    }
    else if (threat2 > threat1)
    {
        cout << "Threat 2 has higher severity." << endl;
    }
    else
    {
        cout << "Both threats have equal severity." << endl;
    }


    // -----------------------------------------
    // 7. Static Variable + Static Function
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Static Variable / Static Function" << endl;
    cout << "========================================" << endl;

    cout << "Total Threat Objects Created: "
         << Threat::getThreatCount()
         << endl;


    // -----------------------------------------
    // 8. Object Slicing
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Object Slicing" << endl;
    cout << "========================================" << endl;

    LoginEvent originalLogin(
        "EVT-003",
        "2026-09-17 10:40:00",
        "203.0.113.50",
        5,
        "admin",
        false
    );

    // Derived object copied into base object
    SecurityEvent slicedEvent = originalLogin;

    cout << "\nOriginal LoginEvent:" << endl;
    originalLogin.displayEvent();

    cout << "\nSliced SecurityEvent:" << endl;
    slicedEvent.displayEvent();


    // -----------------------------------------
    // 9. Final
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " final Keyword" << endl;
    cout << "========================================" << endl;

    cout << "NetworkEvent is declared as final." << endl;
    cout << "Therefore, another class cannot inherit from NetworkEvent."
         << endl;


    cout << "\n========================================" << endl;
    cout << " Simulation Completed" << endl;
    cout << "========================================" << endl;

    return 0;
}
