#include "big_decimal.h"
#include <sstream>
#include <algorithm>

int LongNumber::precision = 8; // Значение по умолчанию

LongNumber::LongNumber() : value("0") {}

LongNumber::LongNumber(const std::string& binary) : value(binary) {}

LongNumber::LongNumber(const LongNumber& other) : value(other.value) {}

LongNumber::~LongNumber() {}

LongNumber& LongNumber::operator=(const LongNumber& other) {
    if (this != &other) {
        value = other.value;
    }
    return *this;
}

LongNumber LongNumber::operator+(const LongNumber& other) const {
    return LongNumber(addFixedPointBinary(value, other.value, precision));
}

LongNumber LongNumber::operator-(const LongNumber& other) const {
    return LongNumber(subtractBinary(value, other.value));
}

LongNumber LongNumber::operator*(const LongNumber& other) const {
    return LongNumber(multiplyBinary(value, other.value));
}

LongNumber LongNumber::operator/(const LongNumber& other) const {
    return LongNumber(divideBinary(value, other.value));
}

bool LongNumber::operator==(const LongNumber& other) const {
    return value == other.value;
}

bool LongNumber::operator!=(const LongNumber& other) const {
    return !(*this == other);
}

bool LongNumber::operator<(const LongNumber& other) const {
    return value < other.value;
}

bool LongNumber::operator>(const LongNumber& other) const {
    return value > other.value;
}

void LongNumber::setPrecision(int bits) {
    precision = bits;
}

LongNumber operator""_longnum(long double number) {
    std::ostringstream oss;
    oss.precision(LongNumber::precision);
    oss << number;
    return LongNumber(oss.str());
}

std::ostream& operator<<(std::ostream& os, const LongNumber& num) {
    os << num.value;
    return os;
}

// Вспомогательная функция сложения чисел с фиксированной точкой
std::string LongNumber::addFixedPointBinary(const std::string& a, const std::string& b, int precision) {
    int pointPosA = a.find('.');
    int pointPosB = b.find('.');

    int fracLenA = (pointPosA != std::string::npos) ? (a.length() - pointPosA - 1) : 0;
    int fracLenB = (pointPosB != std::string::npos) ? (b.length() - pointPosB - 1) : 0;
    int maxFracLen = std::max(fracLenA, fracLenB);

    std::string numA = a + std::string(maxFracLen - fracLenA, '0');
    std::string numB = b + std::string(maxFracLen - fracLenB, '0');

    numA.erase(pointPosA, 1);
    numB.erase(pointPosB, 1);

    std::string result = "";
    int carry = 0;
    int i = numA.length() - 1, j = numB.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += numA[i--] - '0';
        if (j >= 0) sum += numB[j--] - '0';
        result += (sum % 2) + '0';
        carry = sum / 2;
    }

    std::reverse(result.begin(), result.end());

    int pointPos = result.length() - maxFracLen;
    result.insert(pointPos, ".");

    return result;
}

std::string LongNumber::subtractBinary(const std::string& a, const std::string& b) {
    std::string result;
    int borrow = 0;
    int pointPosA = a.find('.');
    int pointPosB = b.find('.');
    int fracLenA = (pointPosA != std::string::npos) ? (a.length() - pointPosA - 1) : 0;
    int fracLenB = (pointPosB != std::string::npos) ? (b.length() - pointPosB - 1) : 0;
    int maxFracLen = std::max(fracLenA, fracLenB);

    std::string numA = a.substr(0, pointPosA) + a.substr(pointPosA + 1) + std::string(maxFracLen - fracLenA, '0');
    std::string numB = b.substr(0, pointPosB) + b.substr(pointPosB + 1) + std::string(maxFracLen - fracLenB, '0');

    while (numA.size() < numB.size()) numA.insert(numA.begin(), '0');
    while (numB.size() < numA.size()) numB.insert(numB.begin(), '0');

    for (int i = numA.size() - 1; i >= 0; --i) {
        int diff = (numA[i] - '0') - (numB[i] - '0') - borrow;
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.insert(result.begin(), diff + '0');
    }

    if (result.length() > maxFracLen) {
        result.insert(result.end() - maxFracLen, '.');
    }

    return result;
}

std::string LongNumber::multiplyBinary(const std::string& a, const std::string& b) {
    std::string numA = a, numB = b;
    size_t pointA = numA.find('.');
    size_t pointB = numB.find('.');

    numA.erase(pointA, 1);
    numB.erase(pointB, 1);

    int totalPrecision = precision * 2;
    std::string result(numA.size() + numB.size(), '0');

    for (int i = numA.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = numB.size() - 1; j >= 0; --j) {
            int sum = (numA[i] - '0') * (numB[j] - '0') + (result[i + j + 1] - '0') + carry;
            result[i + j + 1] = (sum % 2) + '0';
            carry = sum / 2;
        }
        result[i] += carry;
    }

    result.insert(result.end() - totalPrecision, '.');
    while (result.front() == '0' && result[1] != '.') {
        result.erase(result.begin());
    }
    return result;
}

std::string LongNumber::divideBinary(const std::string& a, const std::string& b) {
    return a; // Заглушка
}