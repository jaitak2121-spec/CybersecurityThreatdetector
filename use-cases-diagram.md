```mermaid
graph LR
    subgraph Cybersecurity Management & Threat Monitoring System
        %% Use Cases
        UC1[Manage Security Policies]
        UC2[Monitor Network / System Activity]
        UC3[Investigate Security Incident]
        UC4[View Threat Intelligence]
        UC5[Detect Security Threat]
        UC6[Generate Security Alert]
        UC7[Notify Security Administrator]
        UC8[Generate Security Report]
        UC9[Report Suspicious Activity]

        %% Relationships & Dependencies
        UC2 -->|include| UC5
        UC5 -.->|extend <br/> threat detected| UC6
        UC6 -.->|extend <br/> severity = CRITICAL| UC7
        UC3 -->|include| UC4
    end

    %% Actors
    SA((Security Administrator))
    AN((Security Analyst))
    SN((System / Network Administrator))
    US((Organization / User))
    TI((Threat Intelligence Service))

    %% Actor Connections
    SA --> UC1
    SA --> UC8
    
    AN --> UC2
    AN --> UC3
    
    SN --> UC2
    
    US --> UC9
    
    TI --> UC4
    ```
