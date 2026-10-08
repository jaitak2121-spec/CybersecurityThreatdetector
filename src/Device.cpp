#include "Device.h"
#include <iostream>

using namespace std;

Device::Device(
    string id,
    string name,
    string ip,
    string os
)
{
    deviceId = id;
    deviceName = name;
    ipAddress = ip;
    osType = os;
    status = "ONLINE";
}

string Device::getDeviceId() const   { return deviceId; }
string Device::getDeviceName() const { return deviceName; }
string Device::getIpAddress() const  { return ipAddress; }
string Device::getOsType() const     { return osType; }
string Device::getStatus() const     { return status; }

void Device::updateStatus(string newStatus)
{
    status = newStatus;
}

void Device::isolate()
{
    // Simulation only - no real interface is touched.
    status = "ISOLATED";
    cout << "[SIMULATION] Device " << deviceId
         << " (" << deviceName << ") has been marked ISOLATED." << endl;
}

void Device::displayDevice() const
{
    cout << "\n--- Device ---" << endl;
    cout << "Device ID   : " << deviceId << endl;
    cout << "Device Name : " << deviceName << endl;
    cout << "IP Address  : " << ipAddress << endl;
    cout << "OS Type     : " << osType << endl;
    cout << "Status      : " << status << endl;
}
