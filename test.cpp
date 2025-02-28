#include "big_decimal.h"

#include <iostream>


void runTest(const std::string& testName, const LongNumber& result, const LongNumber& expected) {
    if (result == expected) {
        std::cout << testName << " OK" << std::endl;
    } else {
        std::cout << testName << " FAIL (Expected: " << expected << ", Got: " << result << ")" << std::endl;
    }
}

void testAddition() {
    LongNumber num1("01.1000");  // 1.5
    LongNumber num2("00.1000");  // 0.5
    LongNumber expected("10.0000"); // 2.0
    runTest("Addition Test", num1 + num2, expected);
}

void testSubtraction() {
    LongNumber num1("10.0000");  // 2.0
    LongNumber num2("00.1000");  // 0.5
    LongNumber expected("01.1000"); // 1.5
    runTest("Subtraction Test", num1 - num2, expected);
}

void testMultiplication() {
    LongNumber num1("01.1000");  // 1.5
    LongNumber num2("00.1000");  // 0.5
    LongNumber expected("00.1100"); // 0.75
    runTest("Multiplication Test", num1 * num2, expected);
}

void testDivision() {
    LongNumber num1("10.0000");  // 2.0
    LongNumber num2("01.0000");  // 1.0
    LongNumber expected("10.0000"); // 2.0
    runTest("Division Test", num1 / num2, expected);
}

void testComparison() {
    LongNumber num1("01.1000");  // 1.5
    LongNumber num2("01.1000");  // 1.5
    runTest("Comparison Test", num1, num2);
}


int main() {

    std::cout << "Running tests...\n";
    testAddition();
    testSubtraction();
    testMultiplication();
    testDivision();
    testComparison();

    return 0;
}
