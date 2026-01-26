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

template class matrix<float>;
template class matrix<Complex>;