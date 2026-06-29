#include "../inc/tester.hpp"

template <number T>
T   angle_cos(vector<T> &v1, vector<T> &v2)
{
    if (v1.norm() == 0|| v2.norm() == 0)
        throw typename vector<T>::InvalidOperationException();
    return (v1.dot(v2) / (v1.norm() * v2.norm()));
}

void    angle_cos_tester(void)
{
    vector<float> v1({1, 1});
    vector<float> v2({1, 0});
    vector<Complex> c1({Complex(1, 2), Complex(0, 1)});
    vector<Complex> c2({Complex(0, -1), Complex(2, 0)});

    std::cout << "angle cos: " << angle_cos(v1, v2) << std::endl;
	std::cout << "angle cos: " << angle_cos(c1, c2) << std::endl;
}

template class vector<float>;
template class vector<Complex>;