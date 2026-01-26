#ifndef COMPLEX_HPP
# define COMPLEX_HPP

# include <iostream>
# include <string>

class Complex
{
    public:
        Complex();
        Complex(float real);
        Complex(float real, float imag);
        Complex(const Complex &other);
        ~Complex();
        float real;
        float imag;

        Complex &operator=(const Complex    &rhs);
        Complex &operator+=(const Complex    &rhs);
        Complex &operator-=(const Complex    &rhs);
        Complex operator+(const Complex    &rhs) const;
        Complex operator-(const Complex    &rhs) const;
        Complex operator*(const Complex    &rhs) const;
};

inline std::ostream& operator<<(std::ostream& os, const Complex& c)
{
    os << c.real;
    if (c.imag >= 0) os << '+';
    os << c.imag << 'i';
    return os;
}


#endif