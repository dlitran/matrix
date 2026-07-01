#include "../inc/tester.hpp"


template <number T>
matrix<T>   matrix<T>::transpose(void)
{
    std::vector<T> result(this->shape().first * this->shape().second, 0); //space complexity m*n

    for (int inputRow = 0; inputRow < this->shape().first; inputRow++) //time complexity m
    {
        for (int inputCol = 0; inputCol <this->shape().second; inputCol++) //time complexity n
            result[inputCol * this->shape().second + inputRow] = (*this)(inputRow, inputCol);
    }
    return(matrix(result.data(), this->shape().second, this->shape().first));
}


void    transpose_tester(void)
{
    matrix<float> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    matrix<Complex> m2({
        {Complex(1, 2), Complex(1, 0)},
        {Complex(1, 1), Complex(0, 1)}
    });

	std::cout << "\033[31mReal numbers\033[0m"<< std::endl;
	std::cout << "m1:\n" << m1 << std::endl;
    std::cout << "transpose:\n" << m1.transpose() << std::endl;

	std::cout << "\033[31mComplex numbers\033[0m"<< std::endl;
	std::cout << "m2:\n" << m2 << std::endl;
    std::cout << "transpose:\n" << m2.transpose() << std::endl;
}