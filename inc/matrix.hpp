#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <iostream>
# include <list>
# include <vector.hpp>

template<number T>
class matrix
{
    public:
        matrix();
        matrix(T *Array2D, int m, int n);
        matrix(std::initializer_list<std::initializer_list<T>> list);
        ~matrix();
        matrix(matrix &src);
        matrix &operator=(const matrix &rhs);
        T   operator()(const int &i, const int &j) const;
        std::pair<int, int>  shape(void) const;
        bool    isSquare(void) const;

        void add(matrix<T>&v);
        void sub(matrix<T>&v);
        void scl(T &k);

        matrix<T> lerp(matrix<T> m1, matrix<T> m2, float ratio);

    private:
        std::vector<T>  _data;
        std::pair<int, int> _shape;
        
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
    
};

template<number T>
matrix<T> matrix<T>::lerp(matrix<T> m1, matrix<T> m2, float ratio)
{
    if (ratio < 0 || ratio > 1)
        throw typename vector<T>::InvalidOperationException();
    else if (m1.shape() != m2.shape())
        throw typename vector<T>::InvalidOperationException();

    vector<T> result(m1.shape().first * m1.shape().second);
    std::vector<T>  complete;
    for (int i = 0; i < m1.shape().second; i++)
    {
        typename std::vector<T>::iterator start1 = m1._data.begin() + i * m1.shape().first;
        typename std::vector<T>::iterator end1 = m1._data.begin() + i * m1.shape().first + m1.shape().second;
        typename std::vector<T>::iterator start2 = m2._data.begin() + i * m2.shape().first;
        typename std::vector<T>::iterator end2 = m2._data.begin() + i * m2.shape().first + m2.shape().second;
        std::vector<T>  tmp = std::vector<T>(vector<T>(start1, end1).scale(1 - ratio) + vector<T>(std::vector<T>(start2, end2)).scale(ratio));
        complete.insert(complete.begin(), tmp.begin(), tmp.end());
    }
    result(complete);
    return(matrix(result, m1.shape().first, m1.shape().second));
}

template<number T>
std::ostream    &operator<<(std::ostream &stream, matrix<T> const &matrix)
{
    int i;
    int j;

    i = 0;
    while (i < matrix.shape().first)
    {
        j = 0;
        stream << "[";
        while (j < matrix.shape().second)
        {
            stream << " " << matrix(i, j) << ", ";
            j++;
        }
        i++;
        stream << "]";
    }
    return(stream);
}

#endif