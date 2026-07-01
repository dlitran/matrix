#include "../inc/tester.hpp"

template<number T>
T   vector<T>::dot(const vector<T> &v)
{
    T   result(0);

    if (this->size() != v.size())
        throw vector<T>::InvalidOperationException();
    typename std::vector<T>::const_iterator it1 = this->getVector().begin();
    typename std::vector<T>::const_iterator it2 = v.getVector().begin();

    while (it1 != this->getVector().end())
    {
        result += *it1 * conjugate(*it2);
        it1++;
        it2++;
    }
    return(result);
}

void    dot_product_tester(void)
{
    vector<float> v1({1, 1});
    vector<float> v2({1, 0});
    vector<Complex> c1({Complex(1, 2), Complex(0, 1)});
    vector<Complex> c2({Complex(0, -1), Complex(2, 0)});

    std::cout << "The dot product is: " << v1.dot(v2) << std::endl;
	std::cout << "The dot product is: " << c1.dot(c2) << std::endl;
}

template class vector<float>;
template class vector<Complex>;