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
