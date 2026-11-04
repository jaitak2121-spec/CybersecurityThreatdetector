#ifndef EXCEPTION_HANDLING_H
#define EXCEPTION_HANDLING_H

#include <stdexcept>
#include <string>

namespace ExceptionHandling {

class SecurityException : public std::runtime_error {
public:
    explicit SecurityException(const std::string& message);
};

class InvalidSeverityException : public SecurityException {
public:
    explicit InvalidSeverityException(const std::string& message);
};

class InvalidEventException : public SecurityException {
public:
    explicit InvalidEventException(const std::string& message);
};

void validateEventInput(
    const std::string& eventId,
    const std::string& eventType,
    int severity
);

} // namespace ExceptionHandling

#endif
