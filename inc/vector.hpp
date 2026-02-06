#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <vector>
# include <string>
# include <stdexcept>
# include <concepts>
# include <set>
# include "complex.hpp"

template <typename T>
concept number =
        std::same_as<T, Complex> || std::same_as<T, float>;


template <number T>
class vector
{
    public:
        vector(const vector<T>    &src);
        vector(int size);
        vector(const std::vector<T> &src);
        vector(std::initializer_list<T> src);
        ~vector();
        vector<T>   &operator=(const vector<T> &rhs);
        vector<T>   operator+(const vector<T> &rhs) const;
        vector<T>   operator-(const vector<T> &rhs) const;

        const std::vector<T> &getVector(void) const;
        unsigned int   size(void) const;

        void add(vector<T>&v);
        void sub(vector<T>&v);
        void scl(T &k);
        vector<T> scale(const T &k) const;
        T   dot(const vector<T> &v);

        float   norm_1(void);
        float   norm(void);
        float   norm_inf(void);

        class InvalidOperationException: public std::exception
        {
            public: 
                virtual const char *what() const throw();
        };
        class InvalidInputException: public std::exception
        {
            public: 
                virtual const char *what() const throw();
        };


    private:
        vector();
        std::vector<T> _data;

};

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

template<number T>
vector<T> lerp(vector<T> v1, vector<T> v2, float ratio)
{
    if (ratio < 0 || ratio > 1)
        throw typename vector<T>::InvalidOperationException();
    else if (v1.size() != v2.size())
        throw typename vector<T>::InvalidOperationException();

    vector<T> result(v1.size());

    result = v1.scale(1 - ratio) + v2.scale(ratio);
    return(result);
}

template<number T>
T lerp(T f1, T f2, float ratio)
{
    if (ratio < 0 || ratio > 1)
        throw typename vector<T>::InvalidOperationException();

    T result;

    result = (f1 * (1 - T(ratio))) + (f2 * T(ratio)); //T concstructor in case T we have to multiply a complex * float.
    return(result);
}

template <number T>
float   angle_cos(vector<T> &v1, vector<T> &v2)
{
    if (v1.norm() == 0|| v1.norm() == 0)
        throw typename vector<T>::InvalidOperationException();
    return (v1.dot(v2) / (v1.norm() * v2.norm()));
}

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

template <number T>
std::ostream &operator<<(std::ostream &stream, vector<T>const &src)
{
    std::vector<T> data;

    data = src.getVector();
    for (typename std::vector<T>::iterator it = data.begin(); it != data.end(); ++it)
    {
        stream << ' ' << *it;
    }

	return (stream);
}

#endif