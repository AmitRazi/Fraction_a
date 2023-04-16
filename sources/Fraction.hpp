//
// Created by 97250 on 14/04/2023.
//

#ifndef FRACTION_FRACTION_HPP
#define FRACTION_FRACTION_HPP

#include <stdexcept>

namespace ariel {
    class Fraction {
    private:
        int _numerator;
        int _denominator;

        int gcd(int a, int b);

        std::pair<int, int> abs_max_min(int a, int b);

        Fraction float_to_fraction(double floating_point);

        void reduce_fraction();

        void increment();

        void decrement();


    public:
         explicit Fraction(const int numerator = 1, const int denominator = 1) : _numerator(numerator),
                                                                       _denominator(denominator) {
            if (denominator == 0) {
                throw std::invalid_argument("The denominator can not be zero\n");
            }
            reduce_fraction();
        }

         Fraction(const Fraction &rhs) : _numerator(rhs._numerator), _denominator(rhs._denominator) {
            reduce_fraction();
        }

        explicit Fraction(const double floating_point) : Fraction(float_to_fraction(floating_point)){
        }


        Fraction &operator++();

        Fraction operator++(int);

        Fraction &operator--();

        Fraction operator--(int);

        friend Fraction operator+(const Fraction &lhs, const Fraction &rhs);

        friend Fraction operator+(const Fraction &lhs, double rhs);

        friend Fraction operator+(double lhs, const Fraction &rhs);

        friend Fraction operator-(const Fraction &lhs, const Fraction &rhs);

        friend Fraction operator-(const Fraction &lhs, double rhs);

        friend Fraction operator-(double lhs, const Fraction &rhs);

        friend Fraction operator*(const Fraction &lhs, const Fraction &rhs);

        friend Fraction operator*(const Fraction &lhs, double rhs);

        friend Fraction operator*(double lhs, const Fraction &rhs);

        friend Fraction operator/(const Fraction &lhs, const Fraction &rhs);

        friend Fraction operator/(const Fraction &lhs, double rhs);

        friend Fraction operator/(double lhs, const Fraction &rhs);

        friend bool operator==(const Fraction &lhs, const Fraction &rhs);

        friend bool operator==(const Fraction &lhs, double rhs);

        friend bool operator==(double lhs, const Fraction &rhs);

        friend bool operator<(const Fraction &lhs, const Fraction &rhs);

        friend bool operator<(const Fraction &lhs, double rhs);

        friend bool operator<(double lhs, const Fraction &rhs);

        friend bool operator>(const Fraction &lhs, const Fraction &rhs);

        friend bool operator>(const Fraction &lhs, double rhs);

        friend bool operator>(double lhs, const Fraction &rhs);

        friend bool operator<=(const Fraction &lhs, const Fraction &rhs);

        friend bool operator<=(const Fraction &lhs, double rhs);

        friend bool operator<=(double lhs, const Fraction &rhs);

        friend bool operator>=(const Fraction &lhs, const Fraction &rhs);

        friend bool operator>=(const Fraction &lhs, double rhs);

        friend bool operator>=(double lhs, const Fraction &rhs);

        friend std::ostream &operator<<(std::ostream &output_stream, const Fraction &fraction);

        friend std::istream &operator>>(std::istream &input_stream, Fraction &fraction);
    };
}

#endif //FRACTION_FRACTION_HPP
