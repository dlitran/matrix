#include "../inc/complex.hpp"

Complex::Complex(): real(0), imag(0)
{
}

Complex::~Complex()
{
}

Complex::Complex(float r): real(r), imag(0)
{
}

Complex::Complex(float r, float i): real(r), imag(i)
{
}

Complex::Complex(const Complex &other) : real(other.real), imag(other.imag) 
{
}

Complex &Complex::operator=(const Complex    &rhs)
{
    this->real = rhs.getReal();
    this->imag = rhs.getImag();
    return(*this);
}

Complex &Complex::operator+=(const Complex    &rhs)
{
    this->real += rhs.real;
    this->imag += rhs.imag;
    return(*this);
}

Complex &Complex::operator-=(const Complex    &rhs)
{
    this->real -= rhs.real;
    this->imag -= rhs.imag;
    return(*this);
}

Complex Complex::operator+(const Complex    &rhs) const
{
    Complex result;

    result.real = this->real + rhs.real;
    result.imag = this->imag + rhs.imag;
    return(result);
}

Complex Complex::operator-(const Complex    &rhs) const
{
    Complex result;

    result.real = this->real - rhs.real;
    result.imag = this->imag - rhs.imag;
    return(result);
}

Complex Complex::operator*(const Complex    &rhs) const
{
    Complex result;

    result.real = (this->real * rhs.real) - (this->imag * rhs.imag);
    result.imag = (this->real * rhs.imag) + (this->imag * rhs.real);
    return(result);
}

float   Complex::getReal(void) const
{
    return(this->real);
}

float   Complex::getImag(void) const
{
    return (this->imag);
}

Complex conjugate(const Complex z)
{
    Complex conjugate;

    conjugate.real = z.getReal();
    conjugate.imag = z.getImag() * -1;
    return (conjugate);
}

float   conjugate(const float n)
{
    return (n);
}