#include "../inc/tester.hpp"

template<number T>
vector<T>   linear_combination(const std::vector<vector<T>> u, const vector<T>  coefs)
{
    unsigned int vectors_size;

    if (u.size() != coefs.size() || u.size() == 0)
        throw typename vector<T>::InvalidOperationException();
    vectors_size = u[0].size();

    vector<T> result(vectors_size); //Creates a vector of size vectors_size filled of zeros.
    typename std::vector<vector<T>>::const_iterator it1 = u.begin(); 
    typename std::vector<T>::const_iterator it2 = coefs.getVector().begin();
    while (it1 != u.end())
    {
        if ((*it1).size() != vectors_size)
            throw typename vector<T>::InvalidOperationException();
        result = result + (*it1).scale(*it2);
        it1++;
        it2++;
    }
    return(result);
}


//EX01
void    linear_combination_test(void)
{
    vector<float> vec1({1, 1, 1});
    vector<float> vec2({1, 2, 1});
    vector<float> vec3({1, 0, 0});
    vector<float> coefs({1, 1, -10});

    std::cout << "\033[31mReal numbers\033[0m"<< std::endl;
    std::cout << "vector 1: " << vec1 << std::endl;
    std::cout << "vector 2: " << vec2 << std::endl;
    std::cout << "vector 3: " << vec3 << std::endl;
    std::cout << "Coefficients: " << coefs << std::endl;
    std::vector<vector<float>> vectorList = {vec1, vec2, vec3};
    std::cout << "\033[34mResult: (k1*v1 + k2*v2 + k3*v3): \033[0m" << linear_combination(vectorList, coefs) << std::endl;


    std::cout << "\033[31mComplex numbers\033[0m"<< std::endl;
    vector<Complex> c1({Complex(1, 1), 1, 1});
    vector<Complex> c2({1, 2, 1});
    vector<Complex> c3({1, 0, 0});
    vector<Complex> complexCoefs({Complex(1, 1), 1, -10});
    std::cout << "vector 1: " << c1 << std::endl;
    std::cout << "vector 2: " << c2 << std::endl;
    std::cout << "vector 3: " << c3 << std::endl;
    std::cout << "Coefficients: " << coefs << std::endl;
    std::vector<vector<Complex>> complexVectorList = {c1, c2, c3};
    std::cout << "\033[34mResult: (k1*v1 + k2*v2 + k3*v3): \033[0m" << linear_combination(complexVectorList, complexCoefs) << std::endl;
}

// template vector<float> linear_combination(const std::vector<vector<float>>, const vector<float>);
// template vector<Complex> linear_combination(const std::vector<vector<Complex>>, const vector<Complex>);

template class vector<float>;
template class vector<Complex>;

template class matrix<float>;
template class matrix<Complex>;