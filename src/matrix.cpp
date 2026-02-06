#include "../inc/matrix.hpp"

template <number T>
matrix<T>::matrix()
{
}

template <number T>
matrix<T>::~matrix()
{
}

template <number T>
matrix<T>::matrix(T *Array2D, int m, int n)
{
    this->_data = std::vector<T>(Array2D, Array2D + (m * n));
    this->_shape.first = m;
    this->_shape.second = n;
}

template <number T>
matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> list)
{
    this->_shape.first = list.size();
    this->_shape.second = list.begin()->size();
    // Flatten the 2D list into your 1D vector
    for (auto& row : list) {
        this->_data.insert(this->_data.end(), row.begin(), row.end());
    }
}

//TODO  Finish initializer list constructor.
//TODO Create accessor [] for vector class.

template <number T>
std::pair<int, int>  matrix<T>::shape(void) const
{
    return(this->_shape);
}

template <number T>
T   matrix<T>::operator()(const int &i, const int &j) const
{
    if (i >= this->shape().first || j >= this->shape().second)
        throw matrix<T>::InvalidOperationException();
    return(this->_data[i * this->shape().second + j]);
}

template <number T>
const std::vector<T> &matrix<T>::getData(void) const
{
    return(this->_data);
}

template <number T>
void matrix<T>::add(matrix<T>&m)
{
    if (this->shape() != m.shape())
        throw matrix::InvalidOperationException();
    else
    {
        typename std::vector<T>::iterator it1 = this->_data.begin();
        typename std::vector<T>::iterator it2 = m._data.begin();
        while (it1 != this->_data.end())
        {
            *it1 += *it2;
            it1++;
            it2++;
        }
    }

}

template <number T>
bool    matrix<T>::isSquare(void) const
{
    if (this->_shape.first == this->_shape.second)
        return(true);
    else
        return(false);
}

template <number T>
void matrix<T>::sub(matrix<T>&m)
{
    if (this->shape() != m.shape())
        throw matrix::InvalidOperationException();
    else
    {
        typename std::vector<T>::iterator it1 = this->_data.begin();
        typename std::vector<T>::iterator it2 = m._data.begin();
        while (it1 != this->_data.end())
        {
            *it1 -= *it2;
            it1++;
            it2++;
        }
    }

}

template <number T>
void matrix<T>::scl(T &k)
{

    typename std::vector<T>::iterator it = this->_data.begin();
    while (it != this->_data.end())
    {
        *it = *it * k;
        it++;
    }
}

template <number T>
const char *matrix<T>::InvalidOperationException::what() const throw()
{
	return("Error: Invalid operation.");
}

template <number T>
const char *matrix<T>::InvalidInputException::what() const throw()
{
	return("Error: Invalid input.");
}

template <number T>
vector<T>   matrix<T>::mul_vec(vector<T>   &u)
{
    if ((unsigned int)this->shape().second != u.size())
        throw matrix::InvalidOperationException();

    std::vector<T>  resultVector;
    T   number;

    typename std::vector<T>::const_iterator it2 = u.getVector().begin();
    number = 0;
    for (typename std::vector<T>::iterator it1 = this->_data.begin(); it1 != this->_data.end(); it1++)
    {
        number += (*it1) * (*it2);
        it2++;
        if (it2 == u.getVector().end())
        {
            resultVector.insert(resultVector.end(), number); 
            it2 = u.getVector().begin();
            number = 0;
        }
    }
    vector<T> result(resultVector);
    return(result);
}


 //TODO Opcionalmente hacer la multiplicacion de matrices sin el jumping para aprovechar la memoria chache de la CPU. (haciendo el loop distinto, un dot product.)
template <number T>
matrix<T>   matrix<T>::mul_mat(const matrix<T>   &m)
{
    if (this->shape().second != m.shape().first)
        throw matrix::InvalidOperationException();

    std::vector<T>  resultVector(this->shape().first * m.shape().second, 0); //memory complexity: esto y las dos matrices del input.
    T   number;

    typename std::vector<T>::const_iterator it2 = m.getData().begin();
    typename std::vector<T>::iterator it = resultVector.begin();
    number = 0;
    int col = 0;
    int row = 0;
    while (col < m.shape().second) //time complexity: p
    {
        row = 0;
        number = 0;
        for (typename std::vector<T>::iterator it1 = this->_data.begin(); it1 != this->_data.end(); it1++) //time complexity:  m * n
        {
            number += (*it1) * *(it2 + col + m.shape().second * row);
            row++;
            if (row == (m.shape().first))
            {
                int index = (it1 - this->_data.begin());
                int pos = index + 1;
                int row_result  = (pos / this->shape().second) -1;
                *(it + col + (m.shape().second * row_result)) = number;
                row = 0;
                number = 0;
            }
        }
        col++;
    }
    return (matrix(resultVector.data(), this->shape().first, m.shape().second));
}

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

template <number T>
void    swap_rows(int mainRow, std::vector<T> &result, std::pair<int, int> shape)
{
    typename std::vector<T>::iterator it = result.begin();
    for (int row = mainRow + 1; row < shape.first; row++)
    {
        if (*(it + row * shape.second + mainRow) != 0)
        {
            typename std::vector<T>::iterator beginPreviousRow = (it + mainRow * shape.second);
            typename std::vector<T>::iterator endPreviousRow = (it + mainRow * shape.second + shape.second);
            typename std::vector<T>::iterator beginNewRow = (it + row * shape.second);
            std::swap_ranges(beginPreviousRow, endPreviousRow, beginNewRow);
            //std::cout << "AFTER SWAP" << std::endl;
            //std::cout << matrix(result.data(), this->shape().first, this->shape().second) << std::endl;
            return ;
        }
    }
}

template <number T>
matrix<T>   matrix<T>::row_enchelon(void)
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
        for (int column = mainRow; column < shape.second; column++) //number 1 at the beginning. (normalization)
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
    return(matrix(result.data(), shape.first, shape.second));
}


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

template class matrix<float>;
template class matrix<Complex>;