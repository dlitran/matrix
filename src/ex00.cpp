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
void vector<T>::scl(T &k)
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
void matrix<T>::scl(T &k)
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
    std::vector<float> data1 = {1, 2, 3};
    std::vector<float> data2 = {1, 1, 1};
    std::vector<float> differtSizeData = {1, 3};

    vector myVector1(data1);
    vector myVector2(data2);
    vector differentSizeVector(differtSizeData);

    // std::cout << std::to_string(myVector1.size()) << std::endl;
    // std::cout << std::to_string(myVector2.size()) << std::endl;

    std::cout << "\033[34mVector 1: \033[0m" << myVector1 << "\n\033[34mVector 2: \033[0m" << myVector2 << std::endl;

    myVector1.add(myVector2);
    std::cout << "Vector 1 after adding Vector 2: " << myVector1 << std::endl;

    myVector1.sub(myVector2);
    std::cout << "Vector 1 after subtracting Vector 2: " << myVector1 << std::endl;

    float k = -2.5;
    myVector1.scl(k);
    std::cout << "Vector 1 after scaling by -2.5: " << myVector1 << std::endl;

    // std::cout << "Operator overload of + and -: " << std::endl;
    // std::cout << "Vector 1: " << myVector1 << "Vector 2: " << myVector2 << "Sum: " << (myVector1 + myVector2) << std::endl;
    // std::cout << "Vector 1: " << myVector1 << "Vector 2: " << myVector2 << "Diff: " << (myVector1 - myVector2) << std::endl;

    // myVector1.add(differentSizeVector); //Throws an exception.

    matrix<float> m1({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
    matrix<float> m2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

    std::cout << "\n\033[34mMatrix 1:\n\033[0m" << m1 << "\033[34m\nMatrix 2:\n\033[0m" << m2 << std::endl;
    m1.add(m2);
    std::cout << "Matrix 1 after adding Matrix 2:\n" << m1 << std::endl;
    m1.sub(m2);
    std::cout << "Matrix 1 after subtracting Matrix 2:\n" << m1 << std::endl;
    m1.scl(k);
    std::cout << "Matrix 1 after scaling by -2.5:\n" << m1 << std::endl;
}

//Mirar por que aqui sirve con instanciar los dos templates (vector de complex, vector de float, matrix de complex, matrix de float).
template class vector<float>;
template class vector<Complex>;

template class matrix<float>;
template class matrix<Complex>;