#ifndef COMPLEX_HPP
# define COMPLEX_HPP

# include <iostream>
# include <string>
# include <cmath>

class Complex
{
    public:
        Complex();
        Complex(float real);
        Complex(float real, float imag);
        Complex(const Complex &other);
        ~Complex();
        float   getReal(void) const;
        float   getImag(void) const;
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

Complex conjugate(const Complex z);
float   conjugate(const float n);

#endif