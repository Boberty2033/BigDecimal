#ifndef LONG_NUMBER_H
#define LONG_NUMBER_H

#include <string>
#include <iostream>

class LongNumber {
private:
    std::string value;  // Хранение числа в строковом виде
    static int precision; // Количество бит после запятой

    // Вспомогательные функции
    static std::string addFixedPointBinary(const std::string& a, const std::string& b, int precision);
    static std::string subtractBinary(const std::string& a, const std::string& b);
    static std::string multiplyBinary(const std::string& a, const std::string& b);
    static std::string divideBinary(const std::string& a, const std::string& b);

public:
    // Конструкторы
    LongNumber();
    LongNumber(const std::string& binary);
    LongNumber(const LongNumber& other);
    ~LongNumber();

    // Оператор присваивания
    LongNumber& operator=(const LongNumber& other);

    // Арифметические операции
    LongNumber operator+(const LongNumber& other) const;
    LongNumber operator-(const LongNumber& other) const;
    LongNumber operator*(const LongNumber& other) const;
    LongNumber operator/(const LongNumber& other) const;

    // Операции сравнения
    bool operator==(const LongNumber& other) const;
    bool operator!=(const LongNumber& other) const;
    bool operator<(const LongNumber& other) const;
    bool operator>(const LongNumber& other) const;

    // Функция установки точности
    static void setPrecision(int bits);

    // Перегрузка оператора для литерала
    friend LongNumber operator""_longnum(long double number);

    // Вывод в поток
    friend std::ostream& operator<<(std::ostream& os, const LongNumber& num);
};

#endif // LONG_NUMBER_HPP