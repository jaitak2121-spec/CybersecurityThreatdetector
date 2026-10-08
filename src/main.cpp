#include <iostream>
#include <vector>
#include <string>

#include "EventInfo.h"
#include "SecurityEvent.h"
#include "LoginEvent.h"
#include "NetworkEvent.h"
#include "Threat.h"
#include "ThreatDetector.h"
#include "Device.h"
#include "DetectionRule.h"
#include "Alert.h"
#include "Evidence.h"
#include "ResponseAction.h"
#include "Incident.h"
#include "SecurityLog.h"
#include "SecurityReport.h"

using namespace std;

// Small helper so the console is easier to read.
static void printSection(string title)
{
    cout << "\n========================================" << endl;
    cout << " " << title << endl;
    cout << "========================================" << endl;
}

int main()
{
    cout << "==============================================" << endl;
    cout << " Cybersecurity Threat Detection & " << endl;
    cout << " Incident Response Simulator" << endl;
    cout << " (SAFE SIMULATION - no real actions performed)" << endl;
    cout << "==============================================" << endl;

    // A single shared log receives every activity in the run.
    SecurityLog securityLog;

<<<<<<< HEAD
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
=======
    // ========================================================
    // STEP 1 - DEVICE
    // The device that generates the security events.
    // ========================================================
    printSection("STEP 1: Device");

    Device authServer(
        "DEV-SRV-04",
        "Auth-Portal-Server",
        "192.168.10.45",
        "Ubuntu 22.04 LTS"
>>>>>>> dd8f70d (Updated security events and combined all)
    );

    authServer.displayDevice();

<<<<<<< HEAD

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
=======
    securityLog.writeLogEntry(
        "2026-08-25 10:29:00",
        "EVENT",
        "Device " + authServer.getDeviceId() + " online",
        "EventGenerator"
>>>>>>> dd8f70d (Updated security events and combined all)
    );

    // ========================================================
    // STEP 2 - GENERATE SECURITY EVENTS
    // Stored as pointers to the base class SecurityEvent*, so
    // the vector can hold LoginEvent and NetworkEvent objects,
    // and virtual functions run the correct version later.
    // ========================================================
    printSection("STEP 2: Generate Security Events");

    vector<SecurityEvent*> events;

<<<<<<< HEAD
    // -----------------------------------------
    // 3. Threat Detector
    // -----------------------------------------
=======
    // Five failed logins from one source IP (the brute-force case).
    events.push_back(new LoginEvent(
        "EVT-8801", "2026-08-25 10:14:02", "203.0.113.19", 4,
        "admin", false));
    events.push_back(new LoginEvent(
        "EVT-8802", "2026-08-25 10:14:20", "203.0.113.19", 4,
        "admin", false));
    events.push_back(new LoginEvent(
        "EVT-8803", "2026-08-25 10:14:39", "203.0.113.19", 4,
        "admin", false));
    events.push_back(new LoginEvent(
        "EVT-8804", "2026-08-25 10:15:01", "203.0.113.19", 4,
        "admin", false));
    events.push_back(new LoginEvent(
        "EVT-8805", "2026-08-25 10:15:22", "203.0.113.19", 4,
        "admin", false));
    // One successful login from a normal user.
    events.push_back(new LoginEvent(
        "EVT-8806", "2026-08-25 10:16:00", "198.51.100.7", 1,
        "jsmith", true));
    // A risky network connection to port 22 (SSH).
    events.push_back(new NetworkEvent(
        "EVT-8807", "2026-08-25 10:15:40", "203.0.113.19", 4,
        22, "TCP"));

    // Display every event through the base-class pointer.
    // OOP CONCEPT: POLYMORPHISM - each object prints its own version
    // of displayEvent() even though the pointer type is SecurityEvent*.
    for (size_t i = 0; i < events.size(); i++)
    {
        events[i]->displayEvent();

        securityLog.writeLogEntry(
            "2026-08-25 10:16:05",
            "EVENT",
            events[i]->getRawData(),
            "EventGenerator"
        );
    }

    // ========================================================
    // STEP 3 - CONFIGURE DETECTION RULES
    // ========================================================
    printSection("STEP 3: Configure Detection Rules");
>>>>>>> dd8f70d (Updated security events and combined all)

    ThreatDetector detector;

    detector.addRule(DetectionRule(
        "RULE-AUTH-005",
        "Failed Login (severity >= 4)",
        "FAILED_LOGIN",
        4,
        true
    ));
    detector.addRule(DetectionRule(
        "RULE-NET-002",
        "Connection to risky port (severity >= 4)",
        "OPEN_PORT",
        4,
        true
    ));
    detector.addRule(DetectionRule(
        "RULE-GEN-001",
        "Any high severity event",
        "HIGH_SEVERITY",
        4,
        true
    ));

    detector.listRules();

<<<<<<< HEAD
    cout << "\n========================================" << endl;
    cout << " Method Overloading" << endl;
    cout << "========================================" << endl;
=======
    securityLog.writeLogEntry(
        "2026-08-25 10:16:10",
        "DETECTION",
        "Detection rules configured",
        "DetectionModule"
    );
>>>>>>> dd8f70d (Updated security events and combined all)

    // ========================================================
    // STEP 4 - DETECT THREATS
    // Overload 1 evaluates each event against the rules.
    // ========================================================
    printSection("STEP 4: Detect Threats");

<<<<<<< HEAD
    Threat threat2 = detector.detectThreat(
=======
    // Keep the detected threats so we can report on them later.
    vector<Threat> threats;

    for (size_t i = 0; i < events.size(); i++)
    {
        Threat t = detector.detectThreat(*events[i]);
        threats.push_back(t);

        // Only log threats that are actually suspicious.
        if (t.getStatus() == "ACTIVE")
        {
            securityLog.writeLogEntry(
                "2026-08-25 10:16:30",
                "DETECTION",
                "Threat detected: " + t.getThreatType()
                    + " from " + t.getSourceIp(),
                "DetectionModule"
            );
        }
    }

    // Also run the brute-force pattern detector over the whole set
    // of events (Overload 3).
    Threat bruteForce = detector.detectThreat(
        events,
        "203.0.113.19",
        5
    );
    bruteForce.displayThreat();
    threats.push_back(bruteForce);

    securityLog.writeLogEntry(
        "2026-08-25 10:16:35",
        "DETECTION",
        "Brute-force pattern analysis: " + bruteForce.getThreatType(),
        "DetectionModule"
    );

    // ========================================================
    // STEP 5 - FUNCTION OVERLOADING DEMONSTRATION
    // The same function name, different parameter lists.
    // ========================================================
    printSection("STEP 5: Function Overloading");

    Threat overloadDemo = detector.detectThreat(
>>>>>>> dd8f70d (Updated security events and combined all)
        "NETWORK_EVENT",
        4,
        "203.0.113.20"
    );
    overloadDemo.displayThreat();
    threats.push_back(overloadDemo);

<<<<<<< HEAD

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
=======
    // ========================================================
    // STEP 6 - OPERATOR OVERLOADING + FRIEND FUNCTION
    // ========================================================
    printSection("STEP 6: Operator Overloading");

    cout << "Threat printed with the friend operator<< :" << endl;
    cout << "  " << bruteForce << endl;

    if (bruteForce > overloadDemo)
    {
        cout << "\nbruteForce has a higher severity than overloadDemo. (operator>)" << endl;
    }
    else
    {
        cout << "\noverloadDemo has a higher or equal severity. (operator>)" << endl;
>>>>>>> dd8f70d (Updated security events and combined all)
    }

    cout << "\nTotal threats created      : "
         << Threat::getThreatCount() << " (static function)" << endl;

<<<<<<< HEAD
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
=======
    // ========================================================
    // STEP 7 - GENERATE ALERT
    // Only the serious (ACTIVE) threat becomes an alert.
    // ========================================================
    printSection("STEP 7: Generate Alert");

    Alert* bruteForceAlert = new Alert(
        "ALT-9042",
        "2026-08-25 10:16:40",
        bruteForce.getSeverity(),
        "Excessive failed logins on Auth-Portal-Server from "
            + bruteForce.getSourceIp()
    );

    bruteForceAlert->displayAlert();

    securityLog.writeLogEntry(
        "2026-08-25 10:16:40",
        "ALERT",
        "Alert raised: " + bruteForceAlert->getDescription(),
        "AlertModule"
    );

    // ========================================================
    // STEP 8 - CREATE INCIDENT (UC-02)
    // ========================================================
    printSection("STEP 8: Create Incident");

    Incident* incident = new Incident(
        "INC-2026-0044",
        "Brute Force Attack on Internal Auth Portal",
        bruteForce.getSeverity(),
        "2026-08-25 10:17:00",
        "Repeated failed login attempts from a single external IP."
    );

    // Associate the alert with the incident, then escalate it.
    incident->addAlert(bruteForceAlert);
    bruteForceAlert->updateStatus("ESCALATED");
    incident->displayIncident();

    securityLog.writeLogEntry(
        "2026-08-25 10:17:00",
        "INCIDENT",
        "Incident created: " + incident->getIncidentId()
            + " - " + incident->getTitle(),
        "IncidentModule"
    );

    // ========================================================
    // STEP 9 - INVESTIGATE: COLLECT EVIDENCE (UC-01)
    // ========================================================
    printSection("STEP 9: Investigate - Collect Evidence");

    Evidence* evidence1 = new Evidence(
        "EVD-3301",
        "AUTH_LOG_EXTRACT",
        "/var/log/auth.log",
        "2026-08-25 10:18:00",
        "45 failed authentication attempts within 30 seconds"
    );
    Evidence* evidence2 = new Evidence(
        "EVD-3302",
        "NETWORK_CONNECTION_LOG",
        "Simulated firewall log",
        "2026-08-25 10:18:10",
        "Inbound SSH connection attempts from 203.0.113.19"
    );

    incident->addEvidence(evidence1);
    incident->addEvidence(evidence2);

    evidence1->displayEvidence();
    evidence2->displayEvidence();

    securityLog.writeLogEntry(
        "2026-08-25 10:18:10",
        "INCIDENT",
        "2 evidence items attached to " + incident->getIncidentId(),
        "InvestigationModule"
    );

    // ========================================================
    // STEP 10 - RESPOND (UC-03) - ALL SIMULATED
    // ========================================================
    printSection("STEP 10: Respond to Incident (SIMULATED)");

    // Action 1: block the attacking source IP (simulated).
    ResponseAction* blockAction = new ResponseAction(
        "ACT-1090",
        "BLOCK_SOURCE",
        bruteForce.getSourceIp()
    );
    incident->executeResponse(blockAction, authServer);

    // Action 2: lock the targeted account (simulated).
    ResponseAction* lockAction = new ResponseAction(
        "ACT-1091",
        "LOCK_ACCOUNT",
        "admin"
    );
    incident->executeResponse(lockAction, authServer);

    // Action 3: isolate the affected device (simulated).
    ResponseAction* isolateAction = new ResponseAction(
        "ACT-1092",
        "ISOLATE_DEVICE",
        authServer.getDeviceId()
    );
    incident->executeResponse(isolateAction, authServer);

    // Action 4: an unknown action, to show the failure path
    // (Alternate Flow 2 of UC-03).
    ResponseAction* badAction = new ResponseAction(
        "ACT-1093",
        "UNKNOWN_ACTION",
        "some-target"
    );
    incident->executeResponse(badAction, authServer);

    // Log each response action and its outcome.
    securityLog.writeLogEntry(
        "2026-08-25 10:18:13",
        "RESPONSE",
        "ACT-1090 BLOCK_SOURCE on " + blockAction->getTarget()
            + " -> " + blockAction->getStatus(),
        "IncidentResponseModule"
    );
    securityLog.writeLogEntry(
        "2026-08-25 10:18:14",
        "RESPONSE",
        "ACT-1091 LOCK_ACCOUNT on " + lockAction->getTarget()
            + " -> " + lockAction->getStatus(),
        "IncidentResponseModule"
    );
    securityLog.writeLogEntry(
        "2026-08-25 10:18:15",
        "RESPONSE",
        "ACT-1092 ISOLATE_DEVICE on " + isolateAction->getTarget()
            + " -> " + isolateAction->getStatus(),
        "IncidentResponseModule"
    );
    securityLog.writeLogEntry(
        "2026-08-25 10:18:16",
        "RESPONSE",
        "ACT-1093 UNKNOWN_ACTION failed -> " + badAction->getStatus(),
        "IncidentResponseModule"
    );

    // Show the device state after the simulated isolation.
    authServer.displayDevice();

    // ========================================================
    // STEP 11 - OOP CONCEPT DEMONSTRATIONS
    // Kept separate so they are easy to point at during the viva.
    // ========================================================
    printSection("STEP 11: OOP Concept Demonstrations");

    // ---- 11a. Pointers to objects and to derived classes ----
    cout << "\n[11a] Pointers to objects / derived classes" << endl;
    LoginEvent loginExample(
        "EVT-9901", "2026-08-25 11:00:00", "203.0.113.50", 3,
        "testuser", false
    );
    NetworkEvent networkExample(
        "EVT-9902", "2026-08-25 11:01:00", "203.0.113.51", 2,
        443, "HTTPS"
    );

    // Base-class pointer pointing at a derived object.
    SecurityEvent* securityEventPtr = &loginExample;
    cout << "Calling displayEvent() through SecurityEvent* :" << endl;
    securityEventPtr->displayEvent();          // runs LoginEvent version

    SecurityEvent* networkPtr = &networkExample;
    cout << "Calling displayEvent() through SecurityEvent* :" << endl;
    networkPtr->displayEvent();                // runs NetworkEvent version

    // Derived-class pointer (more specific).
    LoginEvent* loginPtr = &loginExample;
    cout << "Failed login via LoginEvent*: "
         << (loginPtr->isFailedLogin() ? "yes" : "no") << endl;

    // ---- 11b. Virtual function through the base pointer ----
    cout << "\n[11b] Virtual function (runtime polymorphism)" << endl;
    cout << "The same call '->displayEvent()' ran two different"
         << " implementations depending on the real object type." << endl;

    // ---- 11c. Object slicing ----
    cout << "\n[11c] Object slicing" << endl;
    // Copying a LoginEvent into a SecurityEvent variable SLICES it:
    // the LoginEvent-only data (username, loginSuccessful) is lost,
    // and displayEvent() now runs the BASE version.
    SecurityEvent slicedEvent = loginExample;
    cout << "Sliced copy (type SecurityEvent) prints only base fields:"
         << endl;
    slicedEvent.displayEvent();
    cout << "Notice the username and login status are gone - that is"
         << " object slicing." << endl;

    // clone() avoids slicing because it copies through a pointer.
    SecurityEvent* realCopy = loginExample.clone();
    cout << "\nThe same object copied with clone() keeps its full type:"
         << endl;
    realCopy->displayEvent();   // still prints the LoginEvent version
    delete realCopy;

    // ---- 11d. Static variable / static function ----
    cout << "\n[11d] Static members" << endl;
    cout << "Threat::getThreatCount() = "
         << Threat::getThreatCount()
         << "   (shared by all Threat objects)" << endl;
    cout << "Alert::getAlertCount()   = "
         << Alert::getAlertCount() << endl;
    cout << "SecurityLog::getLogCount() = "
         << SecurityLog::getLogCount() << endl;

    // ---- 11e. Nested class ----
    cout << "\n[11e] Nested class Threat::ThreatLevel" << endl;
    Threat::ThreatLevel level5(5);
    Threat::ThreatLevel level3(3);
    cout << "Level 5 -> " << level5 << endl;   // uses operator<<
    cout << "Level 3 -> " << level3 << endl;

    // ---- 11f. this pointer ----
    cout << "\n[11f] this pointer" << endl;
    cout << "LoginEvent's constructor used this->username = user;"
         << " and Threat::updateStatus() uses this->status = newStatus;"
         << endl;
    bruteForce.updateStatus("CONTAINED");
    cout << "bruteForce status after updateStatus(): "
         << bruteForce.getStatus() << endl;

    // ---- 11g. final keyword ----
    cout << "\n[11g] final keyword" << endl;
    cout << "NetworkEvent is declared 'final', so no class may inherit"
         << " from it. The compiler would reject any attempt."
         << endl;

    // ---- 11h. Friend stream operator for other classes ----
    cout << "\n[11h] Friend operator<< on other classes" << endl;
    cout << "Alert    : " << *bruteForceAlert << endl;
    cout << "Incident : " << *incident << endl;
    cout << "Evidence : " << *evidence1 << endl;
>>>>>>> dd8f70d (Updated security events and combined all)

    // ========================================================
    // STEP 12 - SECURITY LOG
    // ========================================================
    printSection("STEP 12: Security Log");

<<<<<<< HEAD
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
=======
    securityLog.printAll();

    // ========================================================
    // STEP 13 - SECURITY REPORT
    // ========================================================
    printSection("STEP 13: Security Report");

    SecurityReport report(
        "REP-2026-08-25",
        "2026-08-25 23:00:00",
        "2026-08-25"
    );

    vector<Alert*> allAlerts;
    allAlerts.push_back(bruteForceAlert);

    vector<Incident*> allIncidents;
    allIncidents.push_back(incident);

    report.generateSummary(threats, allAlerts, allIncidents, securityLog);

    // ========================================================
    // STEP 14 - INCIDENT FULL REPORT
    // ========================================================
    printSection("STEP 14: Incident Full Report");

    incident->displayFullReport();

    // ========================================================
    // CLEAN UP
    // Objects created with new are deleted here.
    // ========================================================
    for (size_t i = 0; i < events.size(); i++)
    {
        delete events[i];
    }

    delete bruteForceAlert;
    delete evidence1;
    delete evidence2;
    delete blockAction;
    delete lockAction;
    delete isolateAction;
    delete badAction;
    delete incident;

    cout << "\n==============================================" << endl;
>>>>>>> dd8f70d (Updated security events and combined all)
    cout << " Simulation Completed" << endl;
    cout << " All actions were simulated - no real security" << endl;
    cout << " operations were performed." << endl;
    cout << "==============================================" << endl;

    return 0;
}
