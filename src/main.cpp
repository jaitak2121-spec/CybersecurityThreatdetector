#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Alert.h"
#include "DetectionRule.h"
#include "Device.h"
#include "Evidence.h"
#include "ExceptionHandling.h"
#include "Incident.h"
#include "LoginEvent.h"
#include "NetworkEvent.h"
#include "ResponseAction.h"
#include "SecurityLog.h"
#include "SecurityReport.h"
#include "ThreatDetector.h"
#include "Threading.h"
#include "TypeCasting.h"

using namespace std;

static void printSection(const string& title)
{
    cout << "\n========================================\n"
         << " " << title << "\n"
         << "========================================\n";
}

int main()
{
    cout << "==============================================\n"
         << " Cybersecurity Threat Detection & Response\n"
         << " (SAFE SIMULATION - no real actions performed)\n"
         << "==============================================\n";

    SecurityLog securityLog;
    Device authServer(
        "DEV-SRV-04", "Auth-Portal-Server",
        "192.168.10.45", "Ubuntu 22.04 LTS"
    );

    printSection("1. Collect and validate events");
    authServer.displayDevice();

    // unique_ptr owns each object; raw base pointers provide a simple
    // polymorphic view for rules and detectors.
    vector<unique_ptr<SecurityEvent>> ownedEvents;
    vector<SecurityEvent*> events;

    auto addEvent = [&](unique_ptr<SecurityEvent> event) {
        event->displayEvent();
        securityLog.writeLogEntry(
            event->getTimestamp(), "EVENT", event->getRawData(),
            "EventCollector"
        );
        events.push_back(event.get());
        ownedEvents.push_back(std::move(event));
    };

    addEvent(make_unique<LoginEvent>(
        "EVT-8801", "2026-08-25 10:14:02", "203.0.113.19", 4,
        "admin", false));
    addEvent(make_unique<LoginEvent>(
        "EVT-8802", "2026-08-25 10:14:20", "203.0.113.19", 4,
        "admin", false));
    addEvent(make_unique<LoginEvent>(
        "EVT-8803", "2026-08-25 10:14:39", "203.0.113.19", 4,
        "admin", false));
    addEvent(make_unique<LoginEvent>(
        "EVT-8804", "2026-08-25 10:16:00", "198.51.100.7", 1,
        "jsmith", true));
    addEvent(make_unique<NetworkEvent>(
        "EVT-8805", "2026-08-25 10:15:40", "203.0.113.19", 4,
        22, "TCP"));

    // Exception handling is part of event admission, not a detached demo.
    try
    {
        addEvent(make_unique<LoginEvent>(
            "EVT-BAD", "2026-08-25 10:16:05", "203.0.113.20", 9,
            "invalid", false));
    }
    catch (const ExceptionHandling::InvalidSeverityException& error)
    {
        cout << "Rejected invalid event: " << error.what() << '\n';
        securityLog.writeLogEntry(
            "2026-08-25 10:16:05", "VALIDATION", error.what(),
            "EventCollector"
        );
    }
    catch (const ExceptionHandling::SecurityException& error)
    {
        // Base fallback must follow the more-specific derived catch.
        cout << "Rejected security event: " << error.what() << '\n';
    }

    try
    {
        addEvent(make_unique<SecurityEvent>(
            "", "", "2026-08-25 10:16:06", "203.0.113.21", 3));
    }
    catch (const ExceptionHandling::SecurityException& error)
    {
        // A base-class handler catches the derived InvalidEventException.
        cout << "Rejected invalid event: " << error.what() << '\n';
        securityLog.writeLogEntry(
            "2026-08-25 10:16:06", "VALIDATION", error.what(),
            "EventCollector"
        );
    }

    // These conversions use an admitted SecurityEvent's real data.
    TypeCasting::NumericSeverity severity = events.front()->getSeverity();
    int severityValue = severity;
    TypeCasting::SecurityEventSummary summary = *events.front();
    cout << "Converted severity value: " << severityValue << '\n';
    summary.display();

    printSection("2. Multithreaded event monitoring");

    ThreadSafeEventMetrics threadMetrics;
    const size_t splitIndex = events.size() / 2;

    // Style 1: create a worker by extending Thread.
    EventMonitoringThread inheritedWorker(
        events, 0, splitIndex, threadMetrics);

    // Style 2: implement Runnable, then give that task to Thread.
    EventMonitoringTask monitoringTask(
        events, splitIndex, events.size(), threadMetrics);
    Thread runnableWorker(monitoringTask);

    cout << "Inherited worker state before start(): "
         << Thread::stateName(inheritedWorker.getState()) << '\n';
    cout << "Runnable worker state before start(): "
         << Thread::stateName(runnableWorker.getState()) << '\n';

    inheritedWorker.start();
    runnableWorker.start();
    cout << "Both workers started; run() is executing concurrently.\n";
    Thread::sleep(1); // allow the workers to enter RUNNING/TIMED_WAITING
    cout << "Inherited worker active state: "
         << Thread::stateName(inheritedWorker.getState()) << '\n';
    cout << "Runnable worker active state: "
         << Thread::stateName(runnableWorker.getState()) << '\n';

    inheritedWorker.join();
    runnableWorker.join();
    cout << "Inherited worker state after join(): "
         << Thread::stateName(inheritedWorker.getState()) << '\n';
    cout << "Runnable worker state after join(): "
         << Thread::stateName(runnableWorker.getState()) << '\n';

    TypeCasting::printMetric(
        "Synchronized events processed",
        threadMetrics.getProcessedEvents());
    TypeCasting::printMetric(
        "Synchronized high-severity events",
        threadMetrics.getHighSeverityEvents());
    TypeCasting::printMetric(
        "Login events", threadMetrics.getLoginEvents());
    TypeCasting::printMetric(
        "Network events", threadMetrics.getNetworkEvents());

    securityLog.writeLogEntry(
        "2026-08-25 10:16:08", "THREADING",
        "Two workers processed "
            + to_string(threadMetrics.getProcessedEvents())
            + " events using synchronized metrics",
        "EventMonitor"
    );

    printSection("3. Configure rules and detect threats");
    ThreatDetector detector;
    detector.addRule(DetectionRule(
        "RULE-AUTH-005", "Failed login", "FAILED_LOGIN", 4, true));
    detector.addRule(DetectionRule(
        "RULE-NET-002", "Risky network port", "OPEN_PORT", 4, true));
    detector.addRule(DetectionRule(
        "RULE-GEN-001", "High severity activity", "HIGH_SEVERITY", 4, true));
    detector.listRules();

    vector<Threat> threats;
    for (SecurityEvent* event : events)
    {
        Threat threat = detector.detectThreat(*event); // overload 1
        threats.push_back(threat);
        if (threat.getStatus() == "ACTIVE")
        {
            securityLog.writeLogEntry(
                event->getTimestamp(), "DETECTION",
                "Threat detected: " + threat.getThreatType(),
                "ThreatDetector"
            );
        }
    }

    Threat bruteForce = detector.detectThreat(
        events, "203.0.113.19", 3); // overload 2: event collection
    threats.push_back(bruteForce);
    bruteForce.displayThreat();

    Threat directDetection = detector.detectThreat(
        "NETWORK_EVENT", 4, "203.0.113.20"); // overload 3: raw fields
    threats.push_back(directDetection);

    printSection("4. Alert, investigate, and respond");
    Alert alert(
        "ALT-9042", "2026-08-25 10:16:40", bruteForce.getSeverity(),
        "Repeated failed logins from " + bruteForce.getSourceIp()
    );
    Incident incident(
        "INC-2026-0044", "Brute Force Attack on Auth Portal",
        bruteForce.getSeverity(), "2026-08-25 10:17:00",
        "Three failed logins from one external source."
    );
    alert.updateStatus("ESCALATED");
    incident.addAlert(&alert);
    securityLog.writeLogEntry(
        "2026-08-25 10:16:40", "ALERT",
        "Raised " + alert.getAlertId(), "AlertManager"
    );

    Evidence authEvidence(
        "EVD-3301", "AUTH_LOG_EXTRACT", "/var/log/auth.log",
        "2026-08-25 10:18:00",
        "Three failed authentication attempts in under one minute"
    );
    Evidence networkEvidence(
        "EVD-3302", "NETWORK_LOG", "Simulated firewall log",
        "2026-08-25 10:18:10",
        "Inbound SSH attempts from 203.0.113.19"
    );
    incident.addEvidence(&authEvidence);
    incident.addEvidence(&networkEvidence);

    ResponseAction blockAction(
        "ACT-1090", "BLOCK_SOURCE", bruteForce.getSourceIp());
    ResponseAction lockAction("ACT-1091", "LOCK_ACCOUNT", "admin");
    ResponseAction isolateAction(
        "ACT-1092", "ISOLATE_DEVICE", authServer.getDeviceId());
    ResponseAction failedAction(
        "ACT-1093", "UNKNOWN_ACTION", "simulation-target");

    vector<ResponseAction*> actions = {
        &blockAction, &lockAction, &isolateAction, &failedAction
    };
    for (ResponseAction* action : actions)
    {
        incident.executeResponse(action, authServer);
        securityLog.writeLogEntry(
            "2026-08-25 10:18:20", "RESPONSE",
            action->getActionId() + " -> " + action->getStatus(),
            "IncidentResponse"
        );
    }
    securityLog.writeLogEntry(
        "2026-08-25 10:17:00", "INCIDENT",
        "Created " + incident.getIncidentId(), "IncidentManager"
    );

    printSection("5. Compact OOP concept check");

    // Runtime polymorphism and pointer to a derived object.
    SecurityEvent* basePointer = events.front();
    basePointer->displayEvent();
    LoginEvent* derivedPointer = dynamic_cast<LoginEvent*>(basePointer);
    cout << "dynamic_cast found LoginEvent: "
         << (derivedPointer != nullptr ? "yes" : "no") << '\n';

    // Object slicing versus a virtual clone.
    SecurityEvent sliced = *derivedPointer;
    unique_ptr<SecurityEvent> cloned(derivedPointer->clone());
    cout << "Sliced object uses base display; clone keeps derived display:\n";
    sliced.displayEvent();
    cloned->displayEvent();

    // Friend/operator overloads, nested class, static functions, template.
    cout << "Threat: " << bruteForce << '\n';
    cout << "Alert: " << alert << '\n';
    cout << "Higher than direct detection: "
         << (bruteForce > directDetection ? "yes" : "no") << '\n';
    Threat::ThreatLevel risk = bruteForce.getLevel();
    cout << "Nested ThreatLevel: " << risk << '\n';
    TypeCasting::printMetric("Threat objects", Threat::getThreatCount());
    TypeCasting::printMetric("Alert objects", Alert::getAlertCount());
    TypeCasting::printMetric("Device status", authServer.getStatus());

    // The hierarchy also demonstrates virtual inheritance, overriding,
    // virtual destructors and NetworkEvent's final specifier in the headers.
    bruteForce.updateStatus("CONTAINED"); // uses this->status

    printSection("6. Log, incident, and report");
    securityLog.printAll();
    incident.displayFullReport();

    vector<Alert*> alerts = {&alert};
    vector<Incident*> incidents = {&incident};
    SecurityReport report(
        "REP-2026-08-25", "2026-08-25 23:00:00", "2026-08-25");
    report.generateSummary(threats, alerts, incidents, securityLog);

    cout << "\nSimulation completed safely.\n";
    return 0;
}
