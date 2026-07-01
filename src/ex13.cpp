#include "../inc/tester.hpp"

template <number T>
int   matrix<T>::rank(void)
{
    std::vector<T>  result;
    std::pair<int, int> shape = this->shape();

    result = this->_data;
    typename std::vector<T>::iterator it = result.begin();
    for (int mainRow = 0; mainRow < shape.first && mainRow < shape.second; mainRow++) //potser no totes les files si ja s'ha arribat al final de les columnes.
    {
        T denominator =  *(it + mainRow * shape.second + mainRow);
        if (denominator == 0) // < 10^9
        {
            swap_rows(mainRow, result, shape);
            denominator =  *(it + mainRow * shape.second + mainRow);
            if (denominator == 0) // < 10^9
                continue;
        }
        for (int column = mainRow; column < shape.second; column++) //number 1 at the beginning.
                *(it + mainRow * shape.second + column) = *(it + mainRow * shape.second + column) / denominator;
        denominator =  1;
        for (int row = mainRow + 1; row < shape.first; row++)
        {
            T numerator = *(it + row * shape.second + mainRow);
            //std::cout << "numerator: " << numerator << "denorminator: " << denominator << std::endl;
            for (int column = 0; column < shape.second; column++)
                *(it + row * shape.second + column) = *(it + row * shape.second + column) - (*(it + mainRow * shape.second + column) * (numerator / denominator));
            //std::cout << matrix(result.data(), shape.first, shape.second) << std::endl;
        }
    }
    int rank;
    rank = shape.first;
    for (int i = shape.first -1; i >= 0; i--)
    {
        if (*(it + i * shape.first + i) == 0)
            rank--;
        else
            break;
    }
    return(rank);
}

void    rank_tester(void)
{
    matrix<float> m1({{1, 1, 1}, {2, 2, 2}, {3, 3, 3}});
    matrix<float> m2({{1, 1, 1}, {1, 2, 1}, {1, 1, 1}});
    matrix<float> m3({{1, 1, 1}, {1, 2, 1}, {1, 1, 3}});
    matrix<Complex> m4({{Complex(0, 1), Complex(1, 0)},
                        {Complex(1, 0), Complex(0, -1)}});
    matrix<Complex> m5({{Complex(0, 1), Complex(1, 0)},
                        {Complex(1, 1), Complex(0, 1)}});

    std::cout << "\033[31mReal numbers\033[0m"<< std::endl;
    std::cout << "m1:\n" << m1 << std::endl;
    std::cout << "rank: " << m1.rank() << std::endl;
    std::cout << "m2:\n" << m2 << std::endl;
    std::cout << "rank: " << m2.rank() << std::endl;
    std::cout << "m3:\n" << m3 << std::endl;
    std::cout << "rank: " << m3.rank() << std::endl;

    std::cout << "\033[31mComplex numbers\033[0m"<< std::endl;
    std::cout << "m4:\n" << m4 << std::endl;
    std::cout << "rank: " <<  m4.rank() << std::endl;
    std::cout << "m5:\n" << m5 << std::endl;
    std::cout << "rank: " << m5.rank() << std::endl;
}