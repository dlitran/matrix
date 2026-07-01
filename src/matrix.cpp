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
bool    matrix<T>::isSquare(void) const
{
    if (this->_shape.first == this->_shape.second)
        return(true);
    else
        return(false);
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

template class matrix<float>;
template class matrix<Complex>;

template void swap_rows<float>(int, std::vector<float>&, std::pair<int, int>);
template void swap_rows<Complex>(int, std::vector<Complex>&, std::pair<int, int>);