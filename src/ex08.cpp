#include "../inc/tester.hpp"

template <number T>
T   matrix<T>::trace(void)
{
    if (this->shape().first != this->shape().second)
        throw matrix::InvalidOperationException();

    T result;

    result = 0;
    for (int i = 0; i < this->shape().first; i++)
        result += (*this)(i, i);
    return(result);
}

void    trace_tester(void)
{
    matrix<float> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    matrix<Complex> m2({
        {Complex(1, 2), Complex(1, 0)},
        {Complex(1, 1), Complex(0, 1)}
    });

	std::cout << "\033[31mReal numbers\033[0m"<< std::endl;
	std::cout << "m1:\n" << m1 << std::endl;
    std::cout << "trace of m1: " << m1.trace() << std::endl;

	std::cout << "\033[31mComplex numbers\033[0m"<< std::endl;
		std::cout << "m2:\n" << m2 << std::endl;
    std::cout << "trace of m2: " << m2.trace() << std::endl;
}