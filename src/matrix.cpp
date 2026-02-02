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
matrix<T>   matrix<T>::mul_mat(matrix<T>   &m)
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

template class matrix<float>;
template class matrix<Complex>;