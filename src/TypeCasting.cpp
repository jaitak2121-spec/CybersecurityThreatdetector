#include "TypeCasting.h"

#include "ExceptionHandling.h"
#include "SecurityEvent.h"

#include <algorithm>

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
    int recentFailures
) {
    if (loginSuccessful) {
        return NumericSeverity(1);
    }

    // Failed login: base 2 + repetition (1..2), capped at HIGH.
    // The collection-level brute-force detector may later escalate to CRITICAL.
    return NumericSeverity(std::min(4, 2 + std::max(1, recentFailures)));
}

NumericSeverity NumericSeverity::forNetwork(
    int destinationPort,
    const std::string& protocol
) {
    int score = 1;
    if (protocol == "TCP") score += 1;
    if (destinationPort == 22 || destinationPort == 3389) score += 2;
    return NumericSeverity(std::min(5, score));
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
