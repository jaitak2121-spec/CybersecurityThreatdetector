#ifndef TYPE_CASTING_H
#define TYPE_CASTING_H

#include <iostream>
#include <string>

class SecurityEvent;

namespace TypeCasting {

class NumericSeverity {
private:
    int level;

public:
    NumericSeverity(int value);
    int getLevel() const;
    operator int() const;
};

class SecurityEventSummary {
private:
    std::string eventType;
    std::string sourceIp;
    int severity;

public:
    SecurityEventSummary(const SecurityEvent& event);
    void display() const;
};

template <typename T>
void printMetric(const std::string& name, const T& value) {
    std::cout << name << ": " << value << '\n';
}

} // namespace TypeCasting

#endif
