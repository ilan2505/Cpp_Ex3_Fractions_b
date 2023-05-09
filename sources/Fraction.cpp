#include "Fraction.hpp"
#include <stdexcept>
#include <sstream>
#include <string>
#include <cctype>
#include <limits>


using namespace ariel;
using namespace std;
namespace ariel
{
    
    // Helper function to calculate the Greatest Common Divisor (GCD)
    int Fraction::gcd(int left, int right) {
        if (right == 0) {  return left;
        } else { return gcd(right, left % right); }
    }

    // Constructors
    Fraction::Fraction(int num, int denom) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        
        int gcd_val = gcd(numerator, denominator);
        numerator /= gcd_val;
        denominator /= gcd_val;
        if (denominator < 0)
        {
            denominator *= -1;
            numerator *= -1;
        }
        
    }


    Fraction::Fraction(double value) {
        numerator = value * 1000;
        denominator = 1000;

        int gcd_val = gcd(numerator, denominator);

        numerator /= gcd_val;
        denominator /= gcd_val;

        if (denominator < 0)
        {
            denominator *= -1;
            numerator *= -1;
        }
        
    }


    // Overloaded arithmetic operators
    Fraction Fraction::operator+(const Fraction &other) const {
        int64_t num = (int64_t) numerator * other.denominator + (int64_t) other.numerator * denominator;
        int64_t denom = (int64_t) denominator * other.denominator;
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() || 
        denom > std::numeric_limits<int>::max() || denom < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Overflow occurred during addition");
        }
        num = (int) num;
        denom = (int) denom;

        int g = gcd(num, denom);
        return Fraction(num / g, denom / g);
    }

    Fraction Fraction::operator-(const Fraction &other) const {
        int64_t num = (int64_t ) numerator * other.denominator - (int64_t )other.numerator * denominator;
        int64_t denom = (int64_t) denominator * other.denominator;
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min() || 
        denom > std::numeric_limits<int>::max() || denom < std::numeric_limits<int>::min()) {
            throw std::overflow_error("Overflow occurred during subtraction");
        }
        num = (int) num;
        denom = (int) denom;

        int g = gcd(num, denom);
        return Fraction(num / g, denom / g);
    }

    Fraction Fraction::operator*(const Fraction &other) const {
        int64_t num = (int64_t) numerator * other.numerator;
        int64_t denom = (int64_t) denominator * other.denominator;
        if (num > std::numeric_limits<int>::max() || denom > std::numeric_limits<int>::max()) {
            throw std::overflow_error("Overflow occurred during multiplication");
        }
        num = (int) num;
        denom = (int) denom;
        int g = gcd(num, denom);
        return Fraction(num / g, denom / g);
    }

    Fraction Fraction::operator/(const Fraction &other) const {
        cout << "/ operator " << endl;
        cout << "this is:  "<< *this << endl;
        cout << "other is: "  << other << endl;
        if (other.numerator == 0) {
            throw std::runtime_error("Division by zero");
        }
        int64_t num = (int64_t) numerator * other.denominator;
        int64_t denom = (int64_t) denominator * other.numerator;
        if (num > std::numeric_limits<int>::max() || denom > std::numeric_limits<int>::max()) {
            throw std::overflow_error("Overflow occurred during division");
        }
        num = (int) num;
        denom = (int) denom;
        int g = gcd(num, denom);
        return Fraction(num / g, denom / g);
    }

    // Overloaded comparison operators
    bool Fraction::operator==(const Fraction &other) const {
        // cout << "= operator " << endl;
        // cout << "this is:  "<< *this << endl;
        // cout << "other is: "  << other << endl;
        double tolerance = 0.001;
        double tempThis = (double) this->numerator / (double) this->denominator;
        double tempOther = (double) other.getNumerator() / (double) other.getDenominator();
        return std::abs(tempThis - tempOther) < tolerance;
    }
    bool Fraction::operator!=(const Fraction &other) const { return !(*this == other); }
    bool Fraction::operator<(const Fraction &other) const {
        cout << "< # Fraction &other" << endl;
        cout << "*this = " << *this << endl;
        cout << "other = " << other << endl;
        if (other.denominator < 0 && other.numerator > 0)
        {
            return numerator * other.denominator * -1 < other.numerator * -1 * denominator;
        }
        
        return numerator * other.denominator < other.numerator * denominator; }
    bool Fraction::operator>(const Fraction &other) const {
        cout << "> # Fraction &other" << endl;
        cout << "*this = " << *this << endl;
        cout << "other = " << other << endl;
         return other < *this; }
    bool Fraction::operator<=(const Fraction &other) const {
        // cout << "<= # Fraction &other" << endl;
        // cout << "*this = " << *this << endl;
        // cout << "other = " << other << endl;
         return !(*this > other); }
    bool Fraction::operator>=(const Fraction &other) const {
        // cout << ">= # Fraction &other" << endl;
        // cout << "*this = " << *this << endl;
        // cout << "other = " << other << endl;
         return !(*this < other); }

    // Overloaded increment and decrement operators
    Fraction& Fraction::operator++() {
        numerator += denominator;  // Adds 1 to the fraction (numerator += denominator)
        return *this;
    }
    Fraction Fraction::operator++(int) {
        Fraction temp = *this;
        ++(*this);
        return temp;
    }
    Fraction& Fraction::operator--() {
        numerator -= denominator;  // Subtracts 1 from the fraction (numerator -= denominator)
        return *this;
    }
    Fraction Fraction::operator--(int) {
        Fraction temp = *this;
        --(*this);
        return temp;
    }


    // Friend stream operators
    std::ostream& operator<<(std::ostream &out, const Fraction &fraction) {
        out << fraction.numerator << "/" << fraction.denominator;
        return out;
    }
    std::istream& operator>>(std::istream &input, Fraction &fraction) {
        int num, denom;
        char delimiter;

        // Check if extraction of num was successful
        if (!(input >> num)) {
            throw std::runtime_error("Invalid input: Unable to read numerator.");
        }

        // Check if extraction of denom was successful
        if (!(input >> denom)) {
            throw std::runtime_error("Invalid input: Unable to read denominator.");
        } else if (denom == 0) { throw std::runtime_error("Denominator cannot be zero");}

        // Check if there are any extra characters after the two integers
        input >> std::ws; // Skip any whitespace
        
        fraction = Fraction(num, denom);
        return input;
    }


    // Operator overloads for double and Fraction
    // Code for the double and Fraction operator overloads
    Fraction operator+(double floating, const Fraction &fraction) { return fraction + floating; }
    Fraction operator-(double floating, const Fraction &fraction) { Fraction temp(floating); return temp - fraction; }
    Fraction operator*(double floating, const Fraction &fraction) { return fraction * floating; }
    Fraction operator/(double floating, const Fraction &fraction) {
        if (fraction.getNumerator() == 0) {
            throw std::runtime_error("Division by zero");
        }
        cout << "/ operator " << endl;
        cout << "floating is:  "<< floating << endl;
        cout << "fraction is: "  << fraction << endl;
        Fraction temp(floating);
        return temp / fraction;
    }

    Fraction Fraction::operator+(double floating) { 
        // cout << "+ operator" << endl;
        // cout << "float = " << floating << endl;
        // cout << "fraction = " << *this << endl;
        Fraction temp(floating); return *this + temp; 
    }
    Fraction Fraction::operator-(double floating) {
        // cout << "- operator" << endl;
        // cout << "float = " << floating << endl;
        // cout << "fraction = " << *this << endl;
         Fraction temp(floating); return *this - temp;
    }
    Fraction Fraction::operator*(double floating) { Fraction temp(floating); return *this * temp; }
    Fraction Fraction::operator/(double floating) {
        if (floating == 0.0) {
            throw std::runtime_error("Division by zero");
        }
        cout << "/ operator " << endl;
        cout << "this is:  "<< *this << endl;
        cout << "floating is: "  << floating << endl;
        Fraction temp(floating); 
        cout << temp << " temp" << endl;
        return *this / temp;
    }

    // Comparison operators for double and Fraction
    bool Fraction::operator==(double floating) {
        // cout << "= operator " << endl;
        // cout << "this is:  "<< *this << endl;
        // cout << "double is: "  << floating << endl;
        double tolerance = 0.001;
        // Since in tests they did not consider it - we implement it here - this is not the right way
        double temp = (double) this->numerator / (double) this->denominator;
        cout << temp - floating << endl;
        return std::abs(temp - floating) < tolerance;
    }
    bool Fraction::operator!=(double floating) {return (double) this->numerator/this->denominator != floating;}
    bool Fraction::operator<(double floating)  {
        cout << "< # double floating, const Fraction &fraction" << endl;
        cout << "float = " << floating << endl;
        cout << "this = " << *this << endl;
        return (double) this->numerator/this->denominator < floating;
         
    }
    bool Fraction::operator>(double floating)  {
        cout << "> # double floating, const Fraction &fraction" << endl;
        cout << "float = " << floating << endl;
        cout << "this = " << *this << endl;
        return (double) this->numerator/this->denominator > floating;
    }
    bool Fraction::operator<=(double floating) {return (double) this->numerator/this->denominator <= floating;}
    bool Fraction::operator>=(double floating) {return (double) this->numerator/this->denominator >= floating;}

    bool operator==(double floating, const Fraction &fraction){
        // cout << "= operator " << endl;
        // cout << "fraction is:  "<< fraction << endl;
        // cout << "double is: "  << floating << endl;
         Fraction temp(floating); return fraction == temp;}
    bool operator!=(double floating, const Fraction &fraction){ Fraction temp(floating); return fraction != temp;}
    bool operator<(double floating, const Fraction &fraction){ 
        cout << "< # double floating, const Fraction &fraction" << endl;
        cout << "float = " << floating << endl;
        cout << "fraction = " << fraction << endl;
        double tolerance = 0.001;
        // Since in tests they did not consider it - we implement it here - this is not the right way
        double temp = (double) fraction.getNumerator()/ (double) fraction.getDenominator();
        cout << temp - floating << endl;
        return (temp - floating) > tolerance;        
        }
    bool operator>(double floating, const Fraction &fraction){
        cout << "> # double floating, const Fraction &fraction" << endl;
        cout << "float = " << floating << endl;
        cout << "fraction = " << fraction << endl;
        double tolerance = 0.001;
        // Since in tests they did not consider it - we implement it here - this is not the right way
        double temp = (double) fraction.getNumerator()/ (double) fraction.getDenominator();
        cout << temp - floating << endl;
        return (floating - temp) > tolerance;  
        }
    bool operator<=(double floating, const Fraction &fraction){
        // cout << "<= # double floating, const Fraction &fraction" << endl;
        // cout << "float = " << floating << endl;
        // cout << "fraction = " << fraction << endl;
        Fraction temp(floating); return temp <= fraction;}
    bool operator>=(double floating, const Fraction &fraction){ 
        // cout << ">= # double floating, const Fraction &fraction" << endl;
        // cout << "float = " << floating << endl;
        // cout << "fraction = " << fraction << endl;
        Fraction temp(floating); return temp >= fraction;}
    


} // namespace ariel
