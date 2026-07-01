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
        void scl(const T &k);
        vector<T> scale(const T &k) const;

        T   dot(const vector<T> &v);
        // Complex dot(const vector<Complex> &v);

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
vector<T>   linear_combination(const std::vector<vector<T>> u, const vector<T>  coefs);

template<number T>
vector<T> lerp(vector<T> v1, vector<T> v2, float ratio);

template<number T>
T lerp(T f1, T f2, float ratio);

// template <number T> 
// T   angle_cos(vector<T> &v1, vector<T> &v2);

float   angle_cos(vector<float> &v1, vector<float> &v2);
float   angle_cos(vector<Complex> &v1, vector<Complex> &v2);


template <number T>
vector<T>  cross_product(vector<T> &v1, vector<T> &v2);

template <number T>
std::ostream &operator<<(std::ostream &stream, vector<T>const &src)
{
    std::vector<T> data;

    data = src.getVector();
    stream << "(";
    if (src.size() == 0)
    {
        stream << ")";
	    return (stream);
    }
    for (typename std::vector<T>::iterator it = data.begin(); it != data.end(); ++it)
    {
        if (it == data.end() - 1)
            stream << *it;
        else
            stream << *it << ", ";
    }
    stream << ")";
	return (stream);
}

#endif