
#ifndef TYPE_CASTING_DEMO_H
#define TYPE_CASTING_DEMO_H

#include <iostream>
#include <string>

namespace TypeCastingDemo {

// --------------------------------------------------
// 1. BASIC-TO-CLASS TYPE CONVERSION
// An int is converted into a NumericSeverity object.
// --------------------------------------------------
class NumericSeverity {
private:
    int level;

public:
    // Conversion constructor: int -> NumericSeverity
    NumericSeverity(int value) : level(value) {}

    int getLevel() const {
        return level;
    }

    // --------------------------------------------------
    // 2. CLASS-TO-BASIC TYPE CONVERSION
    // A NumericSeverity object can convert to int.
    // --------------------------------------------------
    operator int() const {
        return level;
    }
};

// Source class for the class-to-class demonstration.
class LoginEventData {
private:
    std::string sourceIp;
    int failedAttempts;

public:
    LoginEventData(const std::string& ip, int attempts)
        : sourceIp(ip), failedAttempts(attempts) {}

    const std::string& getSourceIp() const {
        return sourceIp;
    }

    int getFailedAttempts() const {
        return failedAttempts;
    }
};

// Destination class for the class-to-class demonstration.
class SecurityEventSummary {
private:
    std::string eventType;
    std::string sourceIp;
    int failedAttempts;

public:
    // --------------------------------------------------
    // 3. CLASS-TO-CLASS TYPE CONVERSION
    // LoginEventData -> SecurityEventSummary
    // --------------------------------------------------
    SecurityEventSummary(const LoginEventData& event)
        : eventType("Login Event"),
          sourceIp(event.getSourceIp()),
          failedAttempts(event.getFailedAttempts()) {}

    void display() const {
        std::cout << "Event type: " << eventType << '\n';
        std::cout << "Source IP: " << sourceIp << '\n';
        std::cout << "Failed attempts: " << failedAttempts << '\n';
    }
};

// --------------------------------------------------
// 4. FUNCTION TEMPLATE
// One function works with different data types.
// --------------------------------------------------
template <typename T>
void printMetric(const std::string& name, const T& value) {
    std::cout << name << ": " << value << '\n';
}

// Function implemented in TypeCastingDemo.cpp.
void runTypeCastingDemo();

} // namespace TypeCastingDemo

#endif
