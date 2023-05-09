#pragma once
#include <iostream>

namespace ariel {
    class Fraction {
    private:
        int numerator;
        int denominator;

        // Static method to calculate Greatest Common Divisor (GCD)
        /* 'static' is used since this method does not depend on any object instance */
        static int gcd(int left, int right);

    public:
        // Constructors
        Fraction(): numerator(1), denominator(1){}
        Fraction(int num, int denom);  
        Fraction(double value);  // Constructor with double value

        // Getters
        int getNumerator() const{ return numerator; }
        int getDenominator() const{ return denominator; }

        // arithmetic operators
        Fraction operator+(const Fraction &other) const;
        Fraction operator-(const Fraction &other) const;
        Fraction operator*(const Fraction &other) const;
        Fraction operator/(const Fraction &other) const;

        // comparison operators
        bool operator==(const Fraction &other) const;
        bool operator!=(const Fraction &other) const;
        bool operator<(const Fraction &other) const;
        bool operator>(const Fraction &other) const;
        bool operator<=(const Fraction &other) const;
        bool operator>=(const Fraction &other) const;

        /* '&' is used to return a reference, allowing for chained operations */
        // Pre-increment (prefix)
        Fraction& operator++();  
        Fraction& operator--(); 
        // Post-increment (postfix)
        Fraction operator++(int);  
        Fraction operator--(int);  

        // Friend stream operators
        /* The 'friend' keyword is used because these operators need access to private member variables */
        friend std::ostream& operator<<(std::ostream &out, const Fraction &fraction);
        friend std::istream& operator>>(std::istream &input, Fraction &fraction);

        // Comparison operators for double and Fraction
        bool operator==(double floating);
        bool operator!=(double floating);
        bool operator<(double floating);
        bool operator>(double floating);
        bool operator<=(double floating);
        bool operator>=(double floating);

        friend bool operator==(double floating, const Fraction& fraction);
        friend bool operator!=(double floating, const Fraction &fraction);
        friend bool operator<(double floating, const Fraction& fraction);
        friend bool operator>(double floating, const Fraction& fraction);
        friend bool operator<=(double floating, const Fraction& fraction);
        friend bool operator>=(double floating, const Fraction& fraction);

        // Operator overloads for double and Fraction
        Fraction operator+(double floating);
        Fraction operator-(double floating);
        Fraction operator*(double floating);
        Fraction operator/(double floating);

        friend Fraction operator+(double floating, const Fraction& fraction);
        friend Fraction operator-(double floating, const Fraction& fraction);
        friend Fraction operator*(double floating, const Fraction& fraction);
        friend Fraction operator/(double floating, const Fraction& fraction);


    };
}




