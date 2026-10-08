#include "Evidence.h"
#include <iostream>

using namespace std;

Evidence::Evidence(
    string id,
    string type,
    string src,
    string time,
    string desc
)
{
    evidenceId = id;
    evidenceType = type;
    source = src;
    timestamp = time;
    description = desc;
}

string Evidence::getEvidenceId() const    { return evidenceId; }
string Evidence::getEvidenceType() const  { return evidenceType; }
string Evidence::getSource() const        { return source; }
string Evidence::getDescription() const   { return description; }

void Evidence::displayEvidence() const
{
    cout << "\n--- Evidence ---" << endl;
    cout << "Evidence ID   : " << evidenceId << endl;
    cout << "Type          : " << evidenceType << endl;
    cout << "Source        : " << source << endl;
    cout << "Timestamp     : " << timestamp << endl;
    cout << "Description   : " << description << endl;
}

// OOP CONCEPT: FRIEND FUNCTION + OPERATOR OVERLOADING
// Reads private fields directly because Evidence declared it friend.
ostream& operator<<(ostream& out, const Evidence& evidence)
{
    out << "[" << evidence.evidenceId << "] "
        << evidence.evidenceType
        << " from " << evidence.source
        << " -> " << evidence.description;
    return out;
}
