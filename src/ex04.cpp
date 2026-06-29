#include "../inc/tester.hpp"

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

void    norm_tester(void)
{
    vector<float> v1({1, 1});
    vector<float> v2({1, 0});
    vector<Complex> c1({Complex(1, 2), Complex(0, 1)});
    vector<Complex> c2({Complex(0, -1), Complex(2, 0)});

    std::cout << "The manhattan norm is: " << c1.norm_1() << std::endl;
    std::cout << "The manhattan norm is: " << v1.norm_1() << std::endl;
    std::cout << "The euclidian norm is: " << c1.norm() << std::endl;
    std::cout << "The euclidian norm is: " << v1.norm() << std::endl;
    std::cout << "The supreme norm is: " << c1.norm_inf() << std::endl;
    std::cout << "The supreme norm is: " << v1.norm_inf() << std::endl;
}

template class vector<float>;
template class vector<Complex>;