#include "../inc/tester.hpp"


template <number T>
vector<T>  cross_product(vector<T> &v1, vector<T> &v2)
{
    if (v1.size() != v2.size() || v1.size() != 3)
        throw typename vector<T>::InvalidOperationException();
    // vector<T> result(3);

    typename std::vector<T>::const_iterator it1 = v1.getVector().begin();
    typename std::vector<T>::const_iterator it2 = v2.getVector().begin();
    //typename std::vector<T>::iterator it = result.getVector().begin();
    // This formula doesn't work for complex numbers.
    T   a1 = *it1;
    T   a2 = *(it1 + 1);
    T   a3 = *(it1 + 2);
    T   b1 = *it2;
    T   b2 = *(it2 + 1);
    T   b3 = *(it2 + 2);
    //Hay que aplicar el conjugado para preservar la ortonormalidad en los complejos
    // *it = conjugate(a2 * b3 - a3 * b2);
    // *(it + 1) = conjugate(a3 * b1 - a1 * b3);
    // *(it + 2) = conjugate(a1 * b2 - a2 * b1);
    std::vector<T> tmp = {conjugate(a2 * b3 - a3 * b2), conjugate(a3 * b1 - a1 * b3), conjugate(a1 * b2 - a2 * b1)};
    vector<T> result(tmp);
    return (result);
}

void    cross_product_tester(void)
{
	vector<float> v1({1, 1, 0});
    vector<float> v2({1, 2, 1});

	std::cout << "\033[31mReal numbers\033[0m"<< std::endl;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "cross product: " << cross_product(v1, v2) << std::endl;

    vector<Complex> c1({Complex(1, 2), Complex(0, 1), Complex(1, 1)});
    vector<Complex> c2({Complex(0, -1), Complex(2, 0), Complex(-1, -1)});

	std::cout << "\033[31mComplex numbers\033[0m"<< std::endl;
	std::cout << "c1: " << c1 << std::endl;
	std::cout << "c2: " << c2 << std::endl;
    std::cout << "cross product: " << cross_product(c1, c2) << std::endl;
}