//
// Created by 97250 on 14/04/2023.
//

#include "Fraction.hpp"
#include <cmath>
#include <iostream>
#include <limits>


namespace ariel {

    int safe_multiply(int a, int b) {
        if (a != 0 && b != 0) {
            if (a > 0 && b > 0 && a > (std::numeric_limits<int>::max() / b)) {
                throw std::overflow_error("Integer overflow on multiplication");
            }

            if (a < 0 && b < 0 && a < (std::numeric_limits<int>::max() / b)) {
                throw std::overflow_error("Integer overflow on multiplication");
            }

            if (a > 0 && b < 0 && b < (std::numeric_limits<int>::min() / a)) {
                throw std::overflow_error("Integer overflow on multiplication");
            }

            if (a < 0 && b > 0 && a < (std::numeric_limits<int>::min() / b)) {
                throw std::overflow_error("Integer overflow on multiplication");
            }
        }

        return a * b;
    }

    int safe_add(int a, int b) {
        if ((b > 0) && a > std::numeric_limits<int>::max() - b) {
            throw std::overflow_error("Operation caused an overflow");
        }

        if ((b < 0) && a < std::numeric_limits<int>::min() - b) {
            throw std::overflow_error("Operation caused an overflow");
        }

        return a + b;
    }

    int safe_substract(int a, int b) {
        if ((b > 0) && a < std::numeric_limits<int>::min() + b) {
            throw std::overflow_error("Operation caused an overflow");
        }

        if ((b < 0) && a > std::numeric_limits<int>::min() + b) {
            throw std::overflow_error("Operation caused an overflow");
        }

        return a - b;
    }

    int Fraction::gcd(int a, int b) {
        auto min_max = abs_max_min(a, b);
        int bigger_integer = std::abs(min_max.first);
        int smaller_integer = std::abs(min_max.second);

        while (smaller_integer != 0) {
            int temp = smaller_integer;
            smaller_integer = bigger_integer % smaller_integer;
            bigger_integer = temp;
        }

        return bigger_integer;
    }

    std::pair<int, int> Fraction::abs_max_min(int a, int b) {
        if (abs(a) > abs(b)) {
            return std::make_pair(a, b);
        }

        return std::make_pair(b, a);
    }

    Fraction Fraction::float_to_fraction(const double floating_point) {
        int precision = 1000;
        int numerator = static_cast<int>(precision * floating_point);

        auto gcd = Fraction::gcd(std::abs(numerator), precision);

        return Fraction(numerator / gcd, precision / gcd);
    }

    void Fraction::reduce_fraction() {
        auto gcd = Fraction::gcd(_numerator, _denominator);

        _numerator = _numerator / gcd;
        _denominator = _denominator / gcd;

        if (_denominator < 0) {
            _denominator = -_denominator;
            _numerator = -_numerator;
        }
    }

    int Fraction::getNumerator(){
        return _numerator;
    }

    int Fraction::getDenominator(){
        return _denominator;
    }

    void Fraction::increment() {
        _numerator += _denominator;
        reduce_fraction();
    }

    void Fraction::decrement() {
        _numerator -= _denominator;
        reduce_fraction();
    }

    Fraction &Fraction::operator++() {
        increment();
        return *this;
    }

    Fraction Fraction::operator++(int) {
        Fraction before_increment{Fraction(*this)};
        increment();
        return before_increment;
    }

    Fraction &Fraction::operator--() {
        decrement();
        return *this;
    }

    Fraction Fraction::operator--(int) {
        Fraction before_decrement{Fraction(*this)};
        decrement();
        return before_decrement;
    }

    Fraction operator+(const Fraction &lhs, const Fraction &rhs) {
        int common_denominator = safe_multiply(lhs._denominator, rhs._denominator);
        int sum_numerator = safe_add(safe_multiply(lhs._numerator, rhs._denominator), safe_multiply(rhs._numerator, lhs._denominator));
        return Fraction(sum_numerator, common_denominator);
    }

    Fraction operator+(const Fraction &lhs, double rhs) {
        Fraction rhs_fraction(rhs);
        return lhs + rhs_fraction;
    }

    Fraction operator+(double lhs, const Fraction &rhs) {
        Fraction lhs_fraction(lhs);
        return lhs_fraction + rhs;
    }

    Fraction operator-(const Fraction &lhs, const Fraction &rhs) {
        int common_denominator = safe_multiply(lhs._denominator, rhs._denominator);
        int sub_numerator = safe_substract(safe_multiply(lhs._numerator, rhs._denominator), safe_multiply(rhs._numerator, lhs._denominator));
        return Fraction(sub_numerator, common_denominator);
    }

    Fraction operator-(const Fraction &lhs, double rhs) {
        Fraction rhs_fraction(rhs);
        return lhs - rhs_fraction;
    }

    Fraction operator-(double lhs, const Fraction &rhs) {
        Fraction lhs_fraction(lhs);
        return lhs_fraction - rhs;
    }

    Fraction operator*(const Fraction &lhs, const Fraction &rhs) {
        int multiplied_numerator = safe_multiply(lhs._numerator , rhs._numerator);
        int multiplies_denominator = safe_multiply(lhs._denominator, rhs._denominator);
        return Fraction(multiplied_numerator, multiplies_denominator);
    }

    Fraction operator*(const Fraction &lhs, double rhs) {
        Fraction rhs_fraction(rhs);
        return lhs * rhs_fraction;
    }

    Fraction operator*(double lhs, const Fraction &rhs) {
        Fraction lhs_fraction(lhs);
        return lhs_fraction * rhs;
    }

    Fraction operator/(const Fraction &lhs, const Fraction &rhs) {
        if (rhs == 0.0) {
            throw std::runtime_error("Dividing by zero\n");
        }
        return lhs * Fraction(rhs._denominator, rhs._numerator);
    }

    Fraction operator/(const Fraction &lhs, double rhs) {
        if (rhs == 0.0) {
            throw std::runtime_error("Dividing by zero\n");
        }
        Fraction rhs_fraction(rhs);
        return lhs * Fraction(rhs_fraction._denominator, rhs_fraction._numerator);
    }

    Fraction operator/(double lhs, const Fraction &rhs) {
        if (rhs == 0.0) {
            throw std::runtime_error("Dividing by zero\n");
        }

        if (lhs == 0) return Fraction{0, 1};
        Fraction lhs_fraction(lhs);
        return lhs_fraction * Fraction(rhs._denominator, rhs._numerator);
    }

    bool operator==(const Fraction &lhs, const Fraction &rhs) {
        double fraction1 = static_cast<double>(lhs._numerator) / lhs._denominator;
        double fraction2 = static_cast<double>(rhs._numerator) / rhs._denominator;
        double tol = 0.001;
        return (std::abs(fraction1 - fraction2) <= tol);
    }

    bool operator==(const Fraction &lhs, double rhs) {
        Fraction rhs_fraction(rhs);
        return lhs == rhs_fraction;
    }

    bool operator==(double lhs, const Fraction &rhs) {
        Fraction lhs_fraction(lhs);
        return lhs_fraction == rhs;
    }

    bool operator<(const Fraction &lhs, const Fraction &rhs) {
        return (lhs._numerator * rhs._denominator - rhs._numerator * lhs._denominator) < 0;
    }

    bool operator<(const Fraction &lhs, double rhs) {
        Fraction rhs_fraction(rhs);
        return lhs < rhs_fraction;
    }

    bool operator<(double lhs, const Fraction &rhs) {
        Fraction lhs_fraction(lhs);
        return lhs_fraction < rhs;
    }

    bool operator>(const Fraction &lhs, const Fraction &rhs) {
        return (lhs._numerator * rhs._denominator - rhs._numerator * lhs._denominator) > 0;
    }

    bool operator>(const Fraction &lhs, double rhs) {
        Fraction rhs_fraction(rhs);
        return lhs > rhs_fraction;
    }

    bool operator>(double lhs, const Fraction &rhs) {
        Fraction lhs_fraction(lhs);
        return lhs_fraction > rhs;
    }

    bool operator<=(const Fraction &lhs, const Fraction &rhs) {
        return ((lhs < rhs) || (lhs == rhs));
    }

    bool operator<=(const Fraction &lhs, double rhs) {
        return ((lhs < rhs) || (lhs == rhs));
    }

    bool operator<=(double lhs, const Fraction &rhs) {
        return (lhs < rhs) || (lhs == rhs);
    }

    bool operator>=(const Fraction &lhs, const Fraction &rhs) {
        return (lhs > rhs) || (lhs == rhs);
    }

    bool operator>=(const Fraction &lhs, double rhs) {
        return (lhs > rhs) || (lhs == rhs);
    }

    bool operator>=(double lhs, const Fraction &rhs) {
        return (lhs > rhs) || (lhs == rhs);
    }

    std::ostream &operator<<(std::ostream &output_stream, const Fraction &fraction) {
        std::string str_dec = std::to_string(fraction._numerator) + "/" + std::to_string(fraction._denominator);
        return output_stream << str_dec;
    }

    std::istream &operator>>(std::istream &input_stream, Fraction &fraction) {
        int numerator, denominator;
        input_stream >> numerator >> denominator;


        if (input_stream.fail()) {
            throw std::runtime_error("Invalid input. Enter only integers as input.\n");
        }
        if (denominator == 0) {
            throw std::runtime_error("Invalid input. The denominator can not be zero\n");
        }
        fraction._numerator = numerator;
        fraction._denominator = denominator;
        fraction.reduce_fraction();


        return input_stream;
    }
}

