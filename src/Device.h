#ifndef DEVICE_H
#define DEVICE_H

#include <string>

using namespace std;

// ============================================================
// Device
// ------------------------------------------------------------
// Represents a device (server, workstation, firewall...) that
// generates security events and can be affected by an incident.
//
// OOP CONCEPTS DEMONSTRATED HERE:
//  - ENCAPSULATION : all data is private, reached via getters.
//  - ABSTRACTION   : isolate() hides the details of "isolation"
//                    behind one simple call. Nothing real happens;
//                    it only changes the simulated status string.
// ============================================================

class Device
{
private:
    string deviceId;
    string deviceName;
    string ipAddress;
    string osType;
    string status;        // ONLINE / ISOLATED / COMPROMISED

public:
    Device(
        string id,
        string name,
        string ip,
        string os
    );

    // --- accessors ---
    string getDeviceId() const;
    string getDeviceName() const;
    string getIpAddress() const;
    string getOsType() const;
    string getStatus() const;

    void updateStatus(string newStatus);

    // SIMULATED isolation: marks the device as isolated.
    // It performs no real network action whatsoever.
    void isolate();

    void displayDevice() const;
};

#endif
