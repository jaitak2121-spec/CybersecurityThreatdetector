#include "TypeCasting.h"

#include "ExceptionHandling.h"
#include "SecurityEvent.h"


namespace TypeCasting {

NumericSeverity::NumericSeverity(int value) : level(value) {
    if (value < 1 || value > 5) {
        throw ExceptionHandling::InvalidSeverityException(
            "NumericSeverity must be between 1 and 5."
        );
    }
}

NumericSeverity NumericSeverity::forLogin(
    bool loginSuccessful,
    int recentFailures,
    bool afterLock
) {
    if (loginSuccessful) {
        return NumericSeverity(1);
    }

    return NumericSeverity(1 + 1 + (recentFailures >= 3)
                           + (recentFailures >= 5) + afterLock);
}

NumericSeverity NumericSeverity::forNetwork(
    int destinationPort,
    int attempts,
    bool unauthorized
) {
    const bool restricted = destinationPort == 22 || destinationPort == 3389;
    return NumericSeverity(1 + 2 * restricted + (attempts >= 3) + unauthorized);
}

int NumericSeverity::getLevel() const {
    return level;
}

NumericSeverity::operator int() const {
    return level;
}

SecurityEventSummary::SecurityEventSummary(const SecurityEvent& event)
    : eventType(event.getEventType()),
      sourceIp(event.getSourceIp()),
      severity(event.getSeverity()) {}

void SecurityEventSummary::display() const {
    std::cout << "Event summary: " << eventType
              << " from " << sourceIp
              << " (severity " << severity << ")\n";
}

} // namespace TypeCasting
