#include "../inc/tester.hpp"


template <number T>
void    swap_rows_inverse(int mainRow, std::vector<T> &result, std::vector<T> &inverse, std::pair<int, int> shape)
{
    typename std::vector<T>::iterator it = result.begin();
    typename std::vector<T>::iterator itInverse = inverse.begin();
    for (int row = mainRow + 1; row < shape.first; row++)
    {
        if (*(it + row * shape.second + mainRow) != 0)
        {
            typename std::vector<T>::iterator beginPreviousRow = (it + mainRow * shape.second);
            typename std::vector<T>::iterator endPreviousRow = (it + mainRow * shape.second + shape.second);
            typename std::vector<T>::iterator beginNewRow = (it + row * shape.second);
            std::swap_ranges(beginPreviousRow, endPreviousRow, beginNewRow);

            typename std::vector<T>::iterator beginPreviousRowInverse = (itInverse + mainRow * shape.second);
            typename std::vector<T>::iterator endPreviousRowInverse = (itInverse + mainRow * shape.second + shape.second);
            typename std::vector<T>::iterator beginNewRowInverse = (itInverse + row * shape.second);
            std::swap_ranges(beginPreviousRowInverse, endPreviousRowInverse, beginNewRowInverse);
            //std::cout << "AFTER SWAP" << std::endl;
            //std::cout << matrix(result.data(), this->shape().first, this->shape().second) << std::endl;
            return ;
        }
    }
}

template <number T>
matrix<T>   matrix<T>::inverse(void)
{
    if (this->shape().first != this->shape().second)
        throw matrix::InvalidOperationException();
    std::vector<T>  result;
    std::pair<int, int> shape = this->shape();

    result = this->_data;
    std::vector<T>  inverse = {};
    for (int i = 0; i < shape.first; i++)
    {
        for (int j = 0; j < shape.second; j++)
        {
            if (i == j)
                inverse.insert(inverse.end(), 1);
            else
                inverse.insert(inverse.end(), 0);
        }
    }
    typename std::vector<T>::iterator it = result.begin();
    typename std::vector<T>::iterator itInverse = inverse.begin();
    for (int mainRow = 0; mainRow < shape.first && mainRow < shape.second; mainRow++) //potser no totes les files si ja s'ha arribat al final de les columnes.
    {
        T denominator =  *(it + mainRow * shape.second + mainRow);
        if (denominator == 0) // < 10^9
        {
            swap_rows_inverse(mainRow, result, inverse, shape);
            denominator =  *(it + mainRow * shape.second + mainRow);
            if (denominator == 0) // < 10^9
            {
                std::cout << "not invertible matrix" << std::endl;
                throw matrix::InvalidOperationException(); //implies determinant == 0
                continue;
            }
        }
        for (int column = 0; column < shape.second; column++) //number 1 at the beginning.
        {
            *(it + mainRow * shape.second + column) = *(it + mainRow * shape.second + column) / denominator;
            *(itInverse + mainRow * shape.second + column) = *(itInverse + mainRow * shape.second + column) / denominator;
        }
        denominator =  1;

        for (int row = mainRow + 1; row < shape.first; row++)
        {
            T numerator = *(it + row * shape.second + mainRow);
            //std::cout << "numerator: " << numerator << "denorminator: " << denominator << std::endl;
            for (int column = 0; column < shape.second; column++)
            {
                *(it + row * shape.second + column) = *(it + row * shape.second + column) - (*(it + mainRow * shape.second + column) * (numerator / denominator));
                *(itInverse + row * shape.second + column) = *(itInverse + row * shape.second + column) - (*(itInverse + mainRow * shape.second + column) * (numerator / denominator));
            }
            //std::cout << matrix(result.data(), shape.first, shape.second) << std::endl;
        }

        for (int row = mainRow -1; row >= 0; row--)
        {
            T numerator = *(it + row * shape.second + mainRow);
            //std::cout << "numerator: " << numerator << "denorminator: " << denominator << std::endl;
            for (int column = 0; column < shape.second; column++)
            {
                *(it + row * shape.second + column) = *(it + row * shape.second + column) - (*(it + mainRow * shape.second + column) * (numerator / denominator));
                *(itInverse + row * shape.second + column) = *(itInverse + row * shape.second + column) - (*(itInverse + mainRow * shape.second + column) * (numerator / denominator));
            }
            //std::cout << matrix(result.data(), shape.first, shape.second) << std::endl;
        }
    }
    //std::cout << matrix(result.data(), shape.first, shape.second) << std::endl;
    return(matrix(inverse.data(), shape.first, shape.second));
}

void    inverse_tester(void)
{
    matrix<float> m1({{1, 0, 0}, {0, 1, 0}, {0, 0, 5}});
    matrix<float> m2({{-5, 1, -4, 1}, {1, 4, -1, 5}, {-4, 1, -8, -1}, {3, 2, 6, 2}});
    matrix<Complex> m3({{Complex(1, 1), Complex(0, 2)}, {Complex(1, 0), Complex(-3, 1)}});
    matrix<Complex> m4({{Complex(1, 1), 2, 7}, {1, -3, 5}, {Complex(1, 1), 1, Complex(3, 2)}});

	std::cout << "\033[31mReal numbers\033[0m"<< std::endl;
	std::cout << "m1:\n" << m1 << std::endl;
    std::cout << "inverse:\n" << m1.inverse() << std::endl;
	std::cout << "m2:\n" << m2 << std::endl;
    std::cout << "inverse:\n" << m2.inverse() << std::endl;

	std::cout << "\033[31mComplex numbers\033[0m"<< std::endl;
	std::cout << "m1:\n" << m3 << std::endl;
    std::cout << "inverse:\n" << m3.inverse() << std::endl;
	std::cout << "m1:\n" << m4 << std::endl;
    std::cout << "inverse:\n" << m4.inverse() << std::endl;

    std::cout << std::fixed << std::setprecision(2);
	std::cout << "\033[34mm1 x m1(-1):\033[0m" << std::endl;
	std::cout << m1.mul_mat(m1.inverse()) << std::endl;
	std::cout << "\033[34mm2 x m2(-1):\033[0m" << std::endl;
    std::cout << m2.mul_mat(m2.inverse()) << std::endl;
	std::cout << "\033[34mm3 x m3(-1):\033[0m" << std::endl;
    std::cout << m3.mul_mat(m3.inverse()) << std::endl;
	std::cout << "\033[34mm4 x m4(-1):\033[0m" << std::endl;
    std::cout << m4.mul_mat(m4.inverse()) << std::endl;
    std::cout << std::defaultfloat << std::setprecision(6);
}