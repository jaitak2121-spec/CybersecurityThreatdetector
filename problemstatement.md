### Problem Statement

Modern computer systems continuously generate security-related events such as login attempts, file-access requests, network connections, and other system activities. Security analysts need to monitor these events, identify suspicious patterns, assess their severity, and take appropriate actions.

However, understanding the complete process of threat detection and incident response can be difficult without a controlled environment for experimentation and learning.

The *Cybersecurity Threat Detection & Incident Response Simulator* is a software system that simulates a security monitoring environment. It generates or accepts simulated security events, analyzes them using predefined detection rules, identifies possible threats, evaluates their risk level, and recommends or performs simulated incident-response actions.

For example, multiple failed login attempts from the same source can be detected as a possible brute-force attack. The system can classify the threat as High or Critical risk, simulate actions such as locking the account or blocking the source IP, and record the complete incident in the security log.

The system will support different types of security events such as login events, file-access events, and network events. Different threat detectors will analyze these events, while a risk-assessment module will assign an appropriate severity level. An incident-response module will execute simulated responses, and a logging/reporting module will maintain a history of detected incidents.

The system is intended as a *safe simulation*. It will not perform real hacking, exploitation, malware execution, or real network blocking. Its purpose is to demonstrate the software design and object-oriented modeling of a cybersecurity monitoring and incident-response system.
