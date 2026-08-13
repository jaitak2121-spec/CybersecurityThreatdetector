# Use Case Specifications

This document contains the detailed specifications for three major use cases of the Cybersecurity Threat Detection and Incident Response Simulator.

## UC-01: Investigate Alert

### Primary Actor

Security Analyst

### Stakeholders

- Security Analyst
- System Administrator
- Security Team

### Preconditions

- A security alert has been generated.
- The Security Analyst is logged into the simulator.
- The alert is available for investigation.

### Postconditions

- The alert has been investigated.
- The investigation result is recorded.
- The alert status is updated.

### Trigger

The Security Analyst selects an alert that requires investigation.

### Main Flow

1. Security Analyst selects an alert.
2. System displays the alert details.
3. System displays available evidence related to the alert.
4. Security Analyst reviews the evidence.
5. Security Analyst determines the threat severity.
6. Security Analyst records the investigation result.
7. System updates the alert status.
8. System saves the investigation record.

### Alternate Flow 1 — Evidence Unavailable

1. System determines that no evidence is available.
2. System informs the Security Analyst.
3. Security Analyst marks the investigation as pending.
4. System saves the investigation as pending.

### Alternate Flow 2 — False Positive

1. Security Analyst determines that the alert is a false positive.
2. Security Analyst marks the alert as false positive.
3. System changes the alert status to "Closed".
4. System records the reason for closing the alert.
## UC-02: Create Incident

### Primary Actor

Security Analyst

### Stakeholders

- Security Analyst
- Incident Response Team
- System Administrator
- Security Team

### Preconditions

- A suspicious or confirmed threat has been detected.
- The Security Analyst is logged into the simulator.
- Relevant alert information is available.

### Postconditions

- A new incident is created.
- The incident receives a unique ID.
- The alert is associated with the incident.
- The incident status is set to "Open".

### Trigger

The Security Analyst determines that an alert represents a security incident.

### Main Flow

1. Security Analyst selects a confirmed security alert.
2. System displays the alert information.
3. Security Analyst selects "Create Incident".
4. System creates a new incident.
5. System generates a unique incident ID.
6. Security Analyst enters the incident details.
7. System associates the alert with the incident.
8. System sets the incident status to "Open".
9. System saves the incident.
10. System displays a confirmation message.

### Alternate Flow 1 — Alert Already Linked

1. System detects that the selected alert already belongs to an existing incident.
2. System displays the existing incident.
3. Security Analyst chooses whether to use the existing incident.
4. System updates the existing incident if the Security Analyst confirms.

### Alternate Flow 2 — Missing Information

1. System detects that required incident information is missing.
2. System identifies the missing information.
3. Security Analyst enters the required information.
4. System creates the incident.

## UC-03: Respond to Incident

### Primary Actor

Security Analyst

### Stakeholders

- Security Analyst
- Incident Response Team
- System Administrator
- Security Team

### Preconditions

- An active security incident exists.
- The incident has been investigated.
- The Security Analyst has permission to perform response actions.

### Postconditions

- A response action has been performed.
- The response action is recorded.
- The incident status is updated.

### Trigger

The Security Analyst decides that a response action is required for an active security incident.

### Main Flow

1. Security Analyst selects an active incident.
2. System displays the incident details.
3. Security Analyst reviews the affected device and threat information.
4. Security Analyst selects an appropriate response action.
5. System displays the selected response action.
6. Security Analyst confirms the action.
7. System performs the simulated response action.
8. System records the response action.
9. System updates the incident status.
10. System displays the response result.

### Alternate Flow 1 — Compromised Device

1. System identifies that the affected device is compromised.
2. Security Analyst selects "Isolate Device".
3. System asks the Security Analyst for confirmation.
4. Security Analyst confirms the action.
5. System simulates device isolation.
6. System records the isolation action.

### Alternate Flow 2 — Response Failure

1. The selected response action fails.
2. System informs the Security Analyst.
3. System records the failed response action.
4. Security Analyst selects another response action.
5. System performs the new response action.
