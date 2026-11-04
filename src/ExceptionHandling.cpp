#include "ExceptionHandling.h"

#include <iostream>

namespace ExceptionHandling {

SecurityException::SecurityException(const std::string& message)
    : std::runtime_error(message) {}

InvalidSeverityException::InvalidSeverityException(const std::string& message)
    : SecurityException(message) {}

InvalidEventException::InvalidEventException(const std::string& message)
    : SecurityException(message) {}

namespace {

class ValidationGuard {
private:
    std::string eventId;

public:
    explicit ValidationGuard(const std::string& id) : eventId(id) {}

    ~ValidationGuard() noexcept {
        std::cout << "  Validation finished for " << eventId << ".\n";
    }

    ValidationGuard(const ValidationGuard&) = delete;
    ValidationGuard& operator=(const ValidationGuard&) = delete;
};

} // namespace

void validateEventInput(
    const std::string& eventId,
    const std::string& eventType,
    int severity
) {
    ValidationGuard cleanup(eventId.empty() ? "<missing-id>" : eventId);

    if (eventId.empty() || eventType.empty()) {
        throw InvalidEventException(
            "Event id and event type must not be empty."
        );
    }
    if (severity < 1 || severity > 5) {
        throw InvalidSeverityException(
            "Severity must be between 1 and 5."
        );
    }
}

} // namespace ExceptionHandling
