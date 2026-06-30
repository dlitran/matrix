#include "../inc/tester.hpp"

template <number T>
void vector<T>::add(vector<T>&v)
{
    if (this->size() != v.size())
        throw vector::InvalidOperationException();
    else
    {
        typename std::vector<T>::iterator it1 = this->_data.begin();
        typename std::vector<T>::iterator it2 = v._data.begin();
        while (it1 != this->_data.end())
        {
            *it1 += *it2;
            it1++;
            it2++;
        }
    }

}

template <number T>
void vector<T>::sub(vector<T>&v)
{
    if (this->size() != v.size())
        throw vector<T>::InvalidOperationException();
    else
    {
        typename std::vector<T>::iterator it1 = this->_data.begin();
        typename std::vector<T>::iterator it2 = v._data.begin();
        while (it1 != this->_data.end())
        {
            *it1 -= *it2;
            it1++;
            it2++;
        }
    }

}

template <number T>
void vector<T>::scl(const T &k)
{
    typename std::vector<T>::iterator it = this->_data.begin();
    while (it != this->_data.end())
    {
        *it = *it * k;
        it++;
    }

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
void matrix<T>::scl(const T &k)
{
    typename std::vector<T>::iterator it = this->_data.begin();
    while (it != this->_data.end())
    {
        *it = *it * k;
        it++;
    }
}

//EX00
void tester_add_sub_scl(void)
{
    // REAL VECTORS
    std::vector<float> data1 = {1, 2, 3};
    std::vector<float> data2 = {1, 1, 1};
    std::vector<float> differtSizeData = {1, 3};
    float k = -2.5;

    std::cout << "\033[31mReal numbers:\033[0m" << std::endl;
    vector myVector1(data1);
    vector myVector2(data2);
    vector differentSizeVector(differtSizeData);
    std::cout << "\033[34mVector 1: \033[0m" << myVector1 << "\n\033[34mVector 2: \033[0m" << myVector2 << std::endl;

    myVector1.add(myVector2);
    std::cout << "\033[32mVector 1 after adding Vector 2:\033[0m " << myVector1 << std::endl;

    myVector1.sub(myVector2);
    std::cout << "\033[32mVector 1 after subtracting Vector 2:\033[0m " << myVector1 << std::endl;

    myVector1.scl(k);
    std::cout << "\033[32mVector 1 after scaling by -2.5:\033[0m " << myVector1 << std::endl;
    // myVector1.add(differentSizeVector); //Throws an exception.

    // COMPLEX VECTORS
    std::cout << "\033[31mComplex numbers:\033[0m" << std::endl;
    vector c1({Complex(1, -1), Complex(0, 2), Complex(1, 1)});
    vector c2({Complex(1, 0), Complex(0, 0), Complex(0, 1)});
    // vector differentSizeVector(differtSizeData);
    std::cout << "\033[34mVector 1: \033[0m" << c1 << "\n\033[34mVector 2: \033[0m" << c2 << std::endl;

    c1.add(c2);
    std::cout << "\033[32mVector 1 after adding Vector 2:\033[0m " << c1 << std::endl;

    c1.sub(c2);
    std::cout << "\033[32mVector 1 after subtracting Vector 2:\033[0m " << c1 << std::endl;

    c1.scl(k);
    std::cout << "\033[32mVector 1 after scaling by -2.5:\033[0m " << c1 << std::endl;

    // REAL MATRICES
    std::cout << "\033[31mReal numbers:\033[0m" << std::endl;
    matrix<float> m1({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
    matrix<float> m2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

    std::cout << "\033[34mMatrix 1:\n\033[0m" << m1 << "\033[34m\nMatrix 2:\n\033[0m" << m2 << std::endl;
    m1.add(m2);
    std::cout << "\033[32mMatrix 1 after adding Matrix 2:\033[0m\n" << m1 << std::endl;
    m1.sub(m2);
    std::cout << "\033[32mMatrix 1 after subtracting Matrix 2:\033[0m\n" << m1 << std::endl;
    m1.scl(k);
    std::cout << "\033[32mMatrix 1 after scaling by -2.5:\033[0m\n" << m1 << std::endl;

    // COMPLEX MATRICES
    std::cout << "\033[31mComplex numbers:\033[0m" << std::endl;
    matrix<Complex> m3({{1, 1, 1}, {1, 1, 1}, {1, Complex(0, 1), 1}});
    matrix<Complex> m4({{Complex(1, 2), 2, 3}, {4, 5, 6}, {7, 8, 9}});

    std::cout << "\033[34mMatrix 1:\n\033[0m" << m3 << "\033[34m\nMatrix 2:\n\033[0m" << m3 << std::endl;
    m3.add(m4);
    std::cout << "\033[32mMatrix 1 after adding Matrix 2:\033[0m\n" << m3 << std::endl;
    m3.sub(m4);
    std::cout << "\033[32mMatrix 1 after subtracting Matrix 2:\033[0m\n" << m3 << std::endl;
    m3.scl(k);
    std::cout << "\033[32mMatrix 1 after scaling by -2.5:\033[0m\n" << m3 << std::endl;
}

//Mirar por que aqui sirve con instanciar los dos templates (vector de complex, vector de float, matrix de complex, matrix de float).
template class vector<float>;
template class vector<Complex>;

template class matrix<float>;
template class matrix<Complex>;