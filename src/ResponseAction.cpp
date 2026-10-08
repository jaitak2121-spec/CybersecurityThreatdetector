#include "ResponseAction.h"
#include <iostream>

using namespace std;

ResponseAction::ResponseAction(
    string id,
    string type,
    string tgt
)
{
    actionId = id;
    actionType = type;
    target = tgt;
    status = "PENDING";
    outcome = "Not executed yet";
}

string ResponseAction::getActionId() const   { return actionId; }
string ResponseAction::getActionType() const { return actionType; }
string ResponseAction::getTarget() const     { return target; }
string ResponseAction::getStatus() const     { return status; }
string ResponseAction::getOutcome() const    { return outcome; }

bool ResponseAction::execute(Device& device)
{
    cout << "[SIMULATION] Executing response action "
         << actionType << " on target '" << target << "'" << endl;

    // Each branch only sets strings - nothing real is performed.
    if (actionType == "ISOLATE_DEVICE")
    {
        device.isolate();                 // simulated isolation
        status = "COMPLETED";
        outcome = "Device " + device.getDeviceId()
                  + " isolated (simulated)";
    }
    else if (actionType == "BLOCK_SOURCE")
    {
        status = "COMPLETED";
        outcome = "Source " + target
                  + " added to simulated block list";
    }
    else if (actionType == "LOCK_ACCOUNT")
    {
        status = "COMPLETED";
        outcome = "Account '" + target
                  + "' locked (simulated)";
    }
    else if (actionType == "RESET_PASSWORD")
    {
        status = "COMPLETED";
        outcome = "Password reset forced for '" + target
                  + "' (simulated)";
    }
    else
    {
        // Alternate Flow 2 of UC-03: the action fails and is recorded.
        status = "FAILED";
        outcome = "Unknown action type: " + actionType;
        cout << "[SIMULATION] Action failed." << endl;
        return false;
    }

    cout << "[SIMULATION] Result: " << outcome << endl;
    return true;
}

void ResponseAction::displayAction() const
{
    cout << "\n--- Response Action ---" << endl;
    cout << "Action ID   : " << actionId << endl;
    cout << "Action Type : " << actionType << endl;
    cout << "Target      : " << target << endl;
    cout << "Status      : " << status << endl;
    cout << "Outcome     : " << outcome << endl;
}

ostream& operator<<(ostream& out, const ResponseAction& action)
{
    out << "[" << action.actionId << "] "
        << action.actionType
        << " on " << action.target
        << " -> " << action.status
        << " (" << action.outcome << ")";
    return out;
}
