## Use Case Specifications: Cybersecurity Management & Threat Monitoring System

# Use Case 1: Monitor Network / System Activity (UC2)
* **Description:** System analysts and network administrators monitor real-time system logs and network streams.
* **Primary Actor:** Security Analyst, System / Network Administrator
* **Preconditions:** User must be authenticated and logged into the monitoring dashboard.
* **Main Success Scenario:**
  1. Actor navigates to the live monitoring module.
  2. System retrieves real-time packet data and system health metrics.
  3. System updates the visualization graphs continuously.
  4. Actor reviews network flows for anomalies.
* **Postconditions:** Active logs are displayed on the dashboard for review.

---

# Use Case 2: Detect Security Threat (UC5)
* **Description:** The system automatically analyzes active network/system traffic to catch malicious patterns.
* **Primary Actor:** System (Triggered by Monitor Network / System Activity)
* **Preconditions:** Live activity monitoring is running.
* **Main Success Scenario:**
  1. System compares incoming activity logs against known threat signatures or baseline behavioral parameters.
  2. System identifies an irregular pattern or malicious signature.
  3. System flags the event as an active security threat.
* **Postconditions:** Threat is logged internally and triggers downstream alerts.

---

# Use Case 3: Investigate Security Incident (UC3)
* **Description:** Security analysts deep-dive into a flagged security event using integrated threat data.
* **Primary Actor:** Security Analyst
* **Preconditions:** A security threat or alert has been generated.
* **Main Success Scenario:**
  1. Analyst selects a specific alert or incident from the dashboard queue.
  2. System pulls detailed forensic logs and related threat intelligence data.
  3. Analyst reviews the threat context, origin, and affected assets.
  4. Analyst updates the incident status (e.g., investigating, resolved).
* **Postconditions:** Incident investigation notes are updated and saved to the audit log.
*
