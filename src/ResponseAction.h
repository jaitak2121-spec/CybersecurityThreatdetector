#ifndef RESPONSEACTION_H
#define RESPONSEACTION_H

#include "Device.h"
#include <string>

using namespace std;

// ============================================================
// ResponseAction
// ------------------------------------------------------------
// A SIMULATED response to an incident. Supported action types:
//
//   LOCK_ACCOUNT   - simulate locking a user account
//   BLOCK_SOURCE   - simulate blocking a source IP
//   ISOLATE_DEVICE - simulate isolating a device
//   RESET_PASSWORD - simulate forcing a password reset
//
// IMPORTANT: none of these do anything real. Each simply sets a
// status/outcome string to model what a real system would do.
//
// OOP CONCEPTS DEMONSTRATED HERE:
//  - ABSTRACTION   : execute() hides the details of each action.
//  - ENCAPSULATION : action data is private.
//  - FRIEND FUNCTION + OPERATOR OVERLOADING : operator<< prints
//    the action and its outcome.
// ============================================================

class ResponseAction
{
private:
    string actionId;
    string actionType;
    string target;            // username, IP, or device id
    string status;            // PENDING / COMPLETED / FAILED
    string outcome;

public:
    ResponseAction(
        string id,
        string type,
        string tgt
    );

    string getActionId() const;
    string getActionType() const;
    string getTarget() const;
    string getStatus() const;
    string getOutcome() const;

    // Performs the SIMULATED action on a target Device.
    // Returns true on success. All work is simulated.
    bool execute(Device& device);

    void displayAction() const;

    friend ostream& operator<<(ostream& out, const ResponseAction& action);
};

#endif
