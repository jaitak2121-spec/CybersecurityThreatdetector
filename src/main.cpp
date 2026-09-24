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
    // 1. Login Event
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
    // 2. Network Event
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
    // 3. Threat Detector
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
    // 9. final Keyword
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " final Keyword" << endl;
    cout << "========================================" << endl;

    cout << "NetworkEvent is declared as final." << endl;
    cout << "Therefore, another class cannot inherit from NetworkEvent."
         << endl;


    // -----------------------------------------
    // 10. this Pointer
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " this Pointer" << endl;
    cout << "========================================" << endl;

    cout << "The this pointer refers to the current object." << endl;
    cout << "It is used inside Threat and event constructors."
         << endl;


    // -----------------------------------------
    // 11. Virtual Function
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Virtual Function" << endl;
    cout << "========================================" << endl;

    SecurityEvent* eventPtr = &loginEvent;

    cout << "\nCalling displayEvent() using base pointer:"
         << endl;

    eventPtr->displayEvent();


    // -----------------------------------------
    // 12. Pointer to Object
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Pointer to Object" << endl;
    cout << "========================================" << endl;

    SecurityEvent* securityEventPtr = &networkEvent;

    cout << "Calling NetworkEvent through SecurityEvent pointer:"
         << endl;

    securityEventPtr->displayEvent();


    // -----------------------------------------
    // 13. Pointer to Derived Class
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Pointer to Derived Class" << endl;
    cout << "========================================" << endl;

    LoginEvent* loginPtr = &loginEvent;

    cout << "Calling LoginEvent using derived-class pointer:"
         << endl;

    loginPtr->displayEvent();


    // -----------------------------------------
    // 14. Virtual Base Class
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Virtual Base Class" << endl;
    cout << "========================================" << endl;

    cout << "EventInfo is used as a virtual base class"
         << endl;

    cout << "SecurityEvent inherits virtually from EventInfo."
         << endl;

    cout << "Source IP obtained through the virtual base:"
         << endl;

    cout << eventPtr->getSourceIp() << endl;


    // -----------------------------------------
    // 15. Simulation Completed
    // -----------------------------------------

    cout << "\n========================================" << endl;
    cout << " Simulation Completed" << endl;
    cout << "========================================" << endl;

    return 0;
}
