#ifndef MATRIX_HPP
# define MATRIX_HPP

# include <iostream>
# include <list>
# include <iomanip>
# include "vector.hpp"

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
        const std::vector<T> &getData(void) const;

        void add(matrix<T>&v);
        void sub(matrix<T>&v);
        void scl(const T &k);
        vector<T>   mul_vec(vector<T>   &u);
        matrix<T>   mul_mat(const matrix<T>   &m);
        
        T   trace(void);
        matrix<T>   transpose(void);
        matrix<T>   row_enchelon(void);
        T   determinantInefficient(void);
        T   determinant(void);
        matrix<T>   inverse(void);
        int   rank(void);
        
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
matrix<T> lerp(matrix<T> &m1, matrix<T> &m2, float ratio);

template <number T>
void    swap_rows(int mainRow, std::vector<T> &result, std::pair<int, int> shape);

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
            stream << " " << matrix(i, j);
            if (j != matrix.shape().second - 1) 
                stream << ", ";
            j++;
        }
        i++;
        stream << "]";
        if (i != matrix.shape().first) 
            stream << std::endl;
    }
    return(stream);
}

// matrix<float> projection(float fov, float ratio, float near, float far)
// {
    
// }

#endif