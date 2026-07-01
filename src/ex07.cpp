#include "../inc/tester.hpp"


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


// TODO Opcionalmente hacer la multiplicacion de matrices sin el jumping para aprovechar la memoria chache de la CPU. (haciendo el loop distinto, un dot product.)
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

void    matrix_multiplication_tester(void)
{
    matrix<float> m1({{1, 0, 0}, {0, 10, 0}, {0, 0, 1}});
    matrix<float> m2({{1, 2, 3, 4, 1}, {5, 6, 7, 8, 1}, {9, 10, 11, 12, 1}});
    vector<float> v1({1, 0, 2});
	vector<Complex> c1({1, 0, 2});

	std::cout << "\033[31mReal numbers\033[0m"<< std::endl;
	std::cout << "m1:\n" << m1 << std::endl;
	std::cout << "m2:\n" << m2 << std::endl;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "\033[34mm1 x v1\033[0m"<< std::endl;
    std::cout << m1.mul_vec(v1) << std::endl;
	std::cout << "\033[34mm1 x m2\033[0m"<< std::endl;
    std::cout << m1.mul_mat(m2) << std::endl;

	std::cout << "\033[31mComplex numbers\033[0m"<< std::endl;
	matrix<Complex> m3({
        {Complex(1, 2), Complex(1, 0), Complex(0, 0)},
        {Complex(1, 1), Complex(0, 1), Complex(2, 1)},
		{Complex(0, 1), Complex(0, 0), Complex(1, 2)},
    });
	matrix<Complex> m4({
        {Complex(0, 1), Complex(0, 0), Complex(0, 0)},
        {Complex(0, 0), Complex(0, 1), Complex(0, 0)},
		{Complex(0, 0), Complex(0, 0), Complex(0,1)},
    });
	std::cout << "m3:\n" << m3 << std::endl;
	std::cout << "m4:\n" << m4 << std::endl;
	std::cout << "\033[34mm3 x v1\033[0m"<< std::endl;
	std::cout << m3.mul_vec(c1) << std::endl;
	std::cout << "\033[34mm3 x m4\033[0m"<< std::endl;
	std::cout << m3.mul_mat(m4) << std::endl;
}
