#include "../inc/tester.hpp"

bool    oddNumberSwaps(std::vector<int> &indexes)
{
    int numberSwaps;
    numberSwaps = 0;
    typename std::vector<int>::iterator it1 = indexes.begin();
    typename std::vector<int>::iterator it2 = it1 + 1;
    while (it2 != indexes.end())
    {
        if (*it1 > *it2)
        {
            int tmp; 
        
            tmp = *it1;
            *it1 = *it2;
            *it2 = tmp;
            numberSwaps++;
            it1 = indexes.begin();
            it2 = it1 + 1;
        }
        else
        {
            it1++;
            it2 = it1 + 1;
        }
    }
    if (numberSwaps % 2 == 0)
        return (false);
    else
        return (true);
}

template <number T>
void    permutation(matrix<T>   &m, std::set<int> set, std::vector<int> indexes, T &determinant)
{
    T   result;

    result = 1;
    if (set.empty())
    {
        for(int i = 0; i < (int)indexes.size(); i++)
        {
            result *= m(i, indexes[i]);
        }
            if (oddNumberSwaps(indexes) == true)
                result *= -1;
            determinant += result;
    }
    else
    {
        for (std::set<int>::iterator it = set.begin(); it != set.end(); it++)
        {
            std::set<int> newSet = set;
            std::vector<int> newIndex = indexes;
            newSet.erase(*it);
            newIndex.insert(newIndex.end(), *it);
            permutation(m, newSet, newIndex, determinant);
        }
    }
}

template <number T>
T   matrix<T>::determinantInefficient(void)
{
    if (this->shape().first != this->shape().second)
        throw matrix::InvalidOperationException();

    std::set<int> set = {};
    std::vector<int> indexes = {};
    T   determinant = 0;
    for (int i = 0; i < this->shape().first; i++)
        set.insert(i);
    permutation(*this, set, indexes, determinant);
    return (determinant);
}

template <number T>
T   matrix<T>::determinant(void)
{
    if (this->shape().first != this->shape().second)
        throw matrix::InvalidOperationException();

    std::vector<T>  result;
    std::pair<int, int> shape = this->shape();
    T   determinant;

    result = this->_data;
    determinant = 1;
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
            else
                determinant *= -1;
        }
        for (int column = mainRow; column < shape.second; column++) //number 1 at the beginning.
        {
                *(it + mainRow * shape.second + column) = *(it + mainRow * shape.second + column) / denominator;
        }
        determinant *= denominator;
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
    return(determinant);
}

void    determinant_tester(void)
{
	matrix<float> m1({{1, 1}, {2, 24}});
    matrix<float> m2({{1, 0, 0}, {0, 1, 0}, {0, 0, 5}});
    matrix<float> m3({{-5, 1, -4, 1}, {1, 4, -1, 5}, {-4, 1, -8, -1}, {3, 2, 6, 2}});
    matrix<Complex> m4({{Complex(7, 1), 2, 3}, {Complex(5, 1), -3, 2}, {3, 1, Complex(1, 1)}});
    matrix<Complex> m5({{1, Complex(0, 2), 7, Complex(1, 1)}, {1, -3, 5, Complex(1, 1)}, {1, Complex(1, 1), 3, 5}, {3, 2, Complex(6, 1), 2}});

	std::cout << "\033[31mReal numbers\033[0m"<< std::endl;
	std::cout << "m1:\n" << m1 << std::endl;
    std::cout << "determinant: " << m1.determinant() << std::endl;
	std::cout << "m2:\n" << m2 << std::endl;
    std::cout << "determinant: " << m2.determinant() << std::endl;
	std::cout << "m3:\n" << m3 << std::endl;
    std::cout << "determinant: " << m3.determinant() << std::endl;

	std::cout << "\033[31mComplex numbers\033[0m"<< std::endl;
	std::cout << "m4:\n" << m4 << std::endl;
    std::cout << "determinant: " << m4.determinant() << std::endl;
	std::cout << "m5:\n" << m5 << std::endl;
	std::cout << "determinant: " << m5.determinant() << std::endl;
}