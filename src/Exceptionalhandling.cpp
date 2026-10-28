
#include "ExceptionHandlingDemo.h"

#include <iostream>
#include <stdexcept>
#include <string>

namespace ExceptionHandlingDemo {

// ================================================
// 1. USER-DEFINED BASE EXCEPTION
// ================================================
class SecurityException : public std::runtime_error {
public:
    explicit SecurityException(const std::string& message)
        : std::runtime_error(message) {}
};

// ================================================
// 2. USER-DEFINED DERIVED EXCEPTIONS
// ================================================
class InvalidSeverityException : public SecurityException {
public:
    explicit InvalidSeverityException(const std::string& message)
        : SecurityException(message) {}
};

class InvalidEventException : public SecurityException {
public:
    explicit InvalidEventException(const std::string& message)
        : SecurityException(message) {}
};

// ================================================
// 3. RAII CLEANUP GUARD
// C++ has no built-in finally block.
// The destructor runs automatically when this
// object leaves scope, including during exceptions.
// ================================================
class CleanupGuard {
public:
    CleanupGuard() {
        std::cout << "[START] Processing security event.\n";
    }

    ~CleanupGuard() noexcept {
        std::cout << "[CLEANUP] Event processing finished.\n";
    }

    CleanupGuard(const CleanupGuard&) = delete;
    CleanupGuard& operator=(const CleanupGuard&) = delete;
};

// ================================================
// 4. VALIDATE SEVERITY
// throw raises a user-defined exception.
// ================================================
void validateSeverity(int severity) {
    if (severity < 1 || severity > 5) {
        throw InvalidSeverityException(
            "Severity must be between 1 and 5."
        );
    }

    std::cout << "[OK] Valid severity: " << severity << '\n';
}

// ================================================
// 5. VALIDATE EVENT TYPE
// ================================================
void validateEventType(const std::string& eventType) {
    if (eventType.empty()) {
        throw InvalidEventException(
            "Security event type cannot be empty."
        );
    }

    std::cout << "[OK] Valid event type: "
              << eventType << '\n';
}

// ================================================
// 6. MAIN EXCEPTION-HANDLING DEMONSTRATION
// ================================================
void runExceptionHandlingDemo() {
    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << " EXCEPTION HANDLING DEMONSTRATION\n";
    std::cout << "============================================\n";

    // A. TRY, THROW, CATCH AND RAII CLEANUP
    std::cout << "\n1. TRY, THROW, CATCH AND CLEANUP\n";

    try {
        CleanupGuard cleanup;

        validateSeverity(8); // Invalid: throws an exception.

        // This line is skipped if validation throws.
        std::cout << "Validation completed normally.\n";
    }
    catch (const InvalidSeverityException& ex) {
        std::cout << "[CAUGHT] " << ex.what() << '\n';
    }

    // B. VALID EVENT: NO EXCEPTION
    std::cout << "\n2. VALID EVENT\n";

    try {
        CleanupGuard cleanup;

        validateSeverity(3);
        validateEventType("Login Event");
    }
    catch (const SecurityException& ex) {
        std::cout << "[SECURITY ERROR] "
                  << ex.what() << '\n';
    }

    // C. USER-DEFINED EXCEPTION
    std::cout << "\n3. USER-DEFINED EXCEPTION\n";

    try {
        validateEventType("");
    }
    catch (const InvalidEventException& ex) {
        std::cout << "[CUSTOM EXCEPTION] "
                  << ex.what() << '\n';
    }

    // D. CATCH DERIVED EXCEPTION FIRST
    std::cout << "\n4. DERIVED-CLASS CATCH\n";

    try {
        throw InvalidSeverityException(
            "A severity-specific exception occurred."
        );
    }
    catch (const InvalidSeverityException& ex) {
        std::cout << "[DERIVED CATCH] "
                  << ex.what() << '\n';
    }
    catch (const SecurityException& ex) {
        // Fallback for other security exceptions.
        std::cout << "[BASE CATCH] "
                  << ex.what() << '\n';
    }

    // E. BASE CLASS CATCHES A DERIVED EXCEPTION
    std::cout << "\n5. BASE-CLASS CATCH\n";

    try {
        throw InvalidEventException(
            "An event-specific exception was caught by its base."
        );
    }
    catch (const SecurityException& ex) {
        std::cout << "[BASE HANDLED DERIVED EXCEPTION] "
                  << ex.what() << '\n';
    }

    // F. C++ EQUIVALENT TOPICS FOR THROWS / FINALLY
    std::cout << "\n6. C++ LANGUAGE NOTES\n";
    std::cout
        << "C++ uses throw to raise exceptions.\n";
    std::cout
        << "C++ uses catch to handle exceptions.\n";
    std::cout
        << "C++ has no Java-style throws declaration.\n";
    std::cout
        << "C++ has no built-in finally block; RAII provides cleanup.\n";
    std::cout
        << "noexcept specifies that a function is non-throwing.\n";

    std::cout << "\n============================================\n";
    std::cout << " END OF EXCEPTION HANDLING DEMO\n";
    std::cout << "============================================\n";
}

} // namespace ExceptionHandlingDemo
