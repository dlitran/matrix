#include "../inc/vector.hpp"

template <number T>
vector<T>::vector()
{
    std::vector<T> zero_vector = { T(0) }; // T will be float(0) or Complex(0).
    this->_data = zero_vector;
}

template <number T>
vector<T>::vector(int size)
{
    std::vector<T> zero_vector(size, T(0) );
    this->_data = zero_vector;
}

template <number T>
vector<T>::~vector()
{
}

template <number T>
vector<T>::vector(const std::vector<T> &src): _data(src)
{
}

template <number T>
vector<T>::vector(std::initializer_list<T> src)
{
    for (typename std::initializer_list<T>::iterator it = src.begin(); it != src.end(); it++)
        this->_data.push_back(*it);
}

template <number T>
vector<T>::vector(const vector<T>   &src)
{
    *this = src;
}

template <number T>
void vector<T>::add(vector<T>&v)
{
    if (this->size() != v.size())
        throw vector::InvalidOperationException();
    else
    {
        typename std::vector<T>::iterator it1 = this->_data.begin();
        typename std::vector<T>::iterator it2 = v._data.begin();
        while (it1 != this->_data.end())
        {
            *it1 += *it2;
            it1++;
            it2++;
        }
    }

}

template <number T>
void vector<T>::sub(vector<T>&v)
{
    if (this->size() != v.size())
        throw vector<T>::InvalidOperationException();
    else
    {
        typename std::vector<T>::iterator it1 = this->_data.begin();
        typename std::vector<T>::iterator it2 = v._data.begin();
        while (it1 != this->_data.end())
        {
            *it1 -= *it2;
            it1++;
            it2++;
        }
    }

}

template <number T>
void vector<T>::scl(T &k)
{
    typename std::vector<T>::iterator it = this->_data.begin();
    while (it != this->_data.end())
    {
        *it = *it * k;
        it++;
    }

}

template <number T>
vector<T> vector<T>::scale(const T &k) const
{
    vector<T> result(this->size());
    typename std::vector<T>::const_iterator it = this->_data.begin();
    typename std::vector<T>::iterator itResult = result._data.begin();
    while (it != this->_data.end())
    {
        *itResult = (*it) * k;
        it++;
        itResult++;
    }
    return (result);
}

template <number T>
T   vector<T>::dot(const vector<T> &v)
{
    T   result(0);

    if (this->size() != v.size())
        throw vector<T>::InvalidOperationException();
    typename std::vector<T>::const_iterator it1 = this->getVector().begin();
    typename std::vector<T>::const_iterator it2 = v.getVector().begin();

    while (it1 != this->getVector().end())
    {
        result += *it1 * *it2;
        it1++;
        it2++;
    }
    return(result);
}

template <number T>
vector<T>   &vector<T>::operator=(const vector<T>&rhs)
{
    this->_data = rhs._data;
    return (*this);
}

template <number T>
vector<T>   vector<T>::operator+(const vector<T>    &v) const
{
    vector<T> result(this->size());
    if (this->size() != v.size())
        throw vector<T>::InvalidOperationException();
    else
    {
        typename std::vector<T>::const_iterator it1 = this->_data.begin();
        typename std::vector<T>::const_iterator it2 = v._data.begin();
        typename std::vector<T>::iterator itResult = result._data.begin();
        while (it1 != this->_data.end())
        {
            *itResult = *it1 + *it2;
            it1++;
            it2++;
            itResult++;
        }
    }
    return (result);
}

template <number T>
vector<T>   vector<T>::operator-(const vector<T>    &v) const
{
    vector<T> result(this->size());
    if (this->size() != v.size())
        throw vector<T>::InvalidOperationException();
    else
    {
        typename std::vector<T>::const_iterator it1 = this->_data.begin();
        typename std::vector<T>::const_iterator it2 = v._data.begin();
        typename std::vector<T>::iterator itResult = result._data.begin();
        while (it1 != this->_data.end())
        {
            *itResult = *it1 - *it2;
            it1++;
            it2++;
            itResult++;
        }
    }
    return (result);
}


float   mod(Complex   &num)
{
    return (std::sqrt(num.real * num.real + num.imag * num.imag));
}

float   mod(float   &num)
{
    if (num < 0)
        return (num * -1);
    else
        return (num);
}

template <number T>
float   vector<T>::norm_1(void)
{
    float   result;

    result = 0;
    for (typename std::vector<T>::iterator it = this->_data.begin(); it != this->_data.end(); it++)
        result += mod(*it);
    return (result);
}

template <number T>
float   vector<T>::norm(void)
{
    float   result;
    float   modulus;

    result = 0;
    for (typename std::vector<T>::iterator it = this->_data.begin(); it != this->_data.end(); it++)
    {
        modulus = mod(*it);
        result += modulus * modulus;
    }
    return (std::sqrt(result));
}
template <number T>
float   vector<T>::norm_inf(void)
{
    float   result;
    float   modulus;

    result = 0;
    for (typename std::vector<T>::iterator it = this->_data.begin(); it != this->_data.end(); it++)
    {
        modulus = mod(*it);
        if (result < modulus)
            result = modulus;
    }
    return (result);
}

template <number T>
unsigned int   vector<T>::size(void) const
{
    return((unsigned int)_data.size());
}

template <number T>
const std::vector<T> &vector<T>::getVector(void) const
{
    return(this->_data);
}

template <number T>
const char *vector<T>::InvalidOperationException::what() const throw()
{
	return("Error: Invalid operation.");
}

template <number T>
const char *vector<T>::InvalidInputException::what() const throw()
{
	return("Error: Invalid input.");
}

template class vector<float>;
template class vector<Complex>;
