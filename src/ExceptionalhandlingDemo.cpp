#include "ExceptionHandlingDemo.h"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

namespace ExceptionHandlingDemo {

// 1. USER-DEFINED BASE EXCEPTION
class SecurityException : public runtime_error {
public:
    explicit SecurityException(const string& message)
        : runtime_error(message) {}
};

// 2. USER-DEFINED DERIVED EXCEPTIONS
class InvalidSeverityException : public SecurityException {
public:
    explicit InvalidSeverityException(const string& message)
        : SecurityException(message) {}
};

class InvalidEventException : public SecurityException {
public:
    explicit InvalidEventException(const string& message)
        : SecurityException(message) {}
};

// 3. RAII CLEANUP GUARD
class CleanupGuard {
public:
    CleanupGuard() {
        cout << "[START] Processing security event.\n";
    }

    ~CleanupGuard() noexcept {
        cout << "[CLEANUP] Event processing finished.\n";
    }

    CleanupGuard(const CleanupGuard&) = delete;
    CleanupGuard& operator=(const CleanupGuard&) = delete;
};

// 4. VALIDATE SEVERITY
void validateSeverity(int severity) {
    if (severity < 1 || severity > 5) {
        throw InvalidSeverityException(
            "Severity must be between 1 and 5."
        );
    }

    cout << "[OK] Valid severity: " << severity << '\n';
}

// 5. VALIDATE EVENT TYPE
void validateEventType(const string& eventType) {
    if (eventType.empty()) {
        throw InvalidEventException(
            "Security event type cannot be empty."
        );
    }

    cout << "[OK] Valid event type: "
         << eventType << '\n';
}

// 6. MAIN DEMONSTRATION
void runExceptionHandlingDemo() {
    cout << "\n";
    cout << "============================================\n";
    cout << " EXCEPTION HANDLING DEMONSTRATION\n";
    cout << "============================================\n";

    // A. TRY, THROW, CATCH AND CLEANUP
    cout << "\n1. TRY, THROW, CATCH AND CLEANUP\n";

    try {
        CleanupGuard cleanup;
        validateSeverity(8);
        cout << "Validation completed normally.\n";
    }
    catch (const InvalidSeverityException& ex) {
        cout << "[CAUGHT] " << ex.what() << '\n';
    }

    // B. VALID EVENT
    cout << "\n2. VALID EVENT\n";

    try {
        CleanupGuard cleanup;
        validateSeverity(3);
        validateEventType("Login Event");
    }
    catch (const SecurityException& ex) {
        cout << "[SECURITY ERROR] "
             << ex.what() << '\n';
    }

    // C. USER-DEFINED EXCEPTION
    cout << "\n3. USER-DEFINED EXCEPTION\n";

    try {
        validateEventType("");
    }
    catch (const InvalidEventException& ex) {
        cout << "[CUSTOM EXCEPTION] "
             << ex.what() << '\n';
    }

    // D. DERIVED-CLASS CATCH
    cout << "\n4. DERIVED-CLASS CATCH\n";

    try {
        throw InvalidSeverityException(
            "A severity-specific exception occurred."
        );
    }
    catch (const InvalidSeverityException& ex) {
        cout << "[DERIVED CATCH] "
             << ex.what() << '\n';
    }
    catch (const SecurityException& ex) {
        cout << "[BASE CATCH] "
             << ex.what() << '\n';
    }

    // E. BASE-CLASS CATCH
    cout << "\n5. BASE-CLASS CATCH\n";

    try {
        throw InvalidEventException(
            "An event-specific exception was caught by its base."
        );
    }
    catch (const SecurityException& ex) {
        cout << "[BASE HANDLED DERIVED EXCEPTION] "
             << ex.what() << '\n';
    }

    // F. C++ LANGUAGE NOTES
    cout << "\n6. C++ LANGUAGE NOTES\n";
    cout << "C++ uses throw to raise exceptions.\n";
    cout << "C++ uses catch to handle exceptions.\n";
    cout << "C++ has no Java-style throws declaration.\n";
    cout << "C++ has no built-in finally block; RAII provides cleanup.\n";
    cout << "noexcept specifies that a function is non-throwing.\n";

    cout << "\n============================================\n";
    cout << " END OF EXCEPTION HANDLING DEMO\n";
    cout << "============================================\n";
}

} // namespace ExceptionHandlingDemo
