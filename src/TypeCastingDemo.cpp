
#include "TypeCastingDemo.h"

namespace TypeCastingDemo {

void runTypeCastingDemo() {
    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << " TYPE CASTING AND TEMPLATE DEMONSTRATION\n";
    std::cout << "============================================\n";

    // --------------------------------------------------
    // 1. BASIC-TO-CLASS
    // --------------------------------------------------
    std::cout << "\n1. BASIC-TO-CLASS TYPE CONVERSION\n";

    int rawSeverity = 3;

    // The int is converted to a NumericSeverity object.
    NumericSeverity severity = rawSeverity;

    std::cout << "Original integer: " << rawSeverity << '\n';
    std::cout << "Object severity: " << severity.getLevel() << '\n';

    // --------------------------------------------------
    // 2. CLASS-TO-BASIC
    // --------------------------------------------------
    std::cout << "\n2. CLASS-TO-BASIC TYPE CONVERSION\n";

    // The NumericSeverity object is converted to an int.
    int numericValue = severity;

    std::cout << "Converted integer: " << numericValue << '\n';

    // --------------------------------------------------
    // 3. CLASS-TO-CLASS
    // --------------------------------------------------
    std::cout << "\n3. CLASS-TO-CLASS TYPE CONVERSION\n";

    LoginEventData loginEvent("192.168.1.10", 5);

    // A LoginEventData object is converted into a
    // SecurityEventSummary object using its constructor.
    SecurityEventSummary summary = loginEvent;

    summary.display();

    // --------------------------------------------------
    // 4. FUNCTION TEMPLATE
    // --------------------------------------------------
    std::cout << "\n4. FUNCTION TEMPLATE DEMONSTRATION\n";

    int threatCount = 9;
    double riskScore = 95.5;
    std::string simulationStatus = "Completed";

    printMetric("Threat count", threatCount);
    printMetric("Risk score", riskScore);
    printMetric("Simulation status", simulationStatus);

    std::cout << "\n============================================\n";
    std::cout << " END OF OOP LAB DEMONSTRATION\n";
    std::cout << "============================================\n";
}

} // namespace TypeCastingDemo
