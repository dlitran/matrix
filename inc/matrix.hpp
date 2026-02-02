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
        const std::vector<T> &getData(void) const;

        void add(matrix<T>&v);
        void sub(matrix<T>&v);
        void scl(T &k);
        vector<T>   mul_vec(vector<T>   &u);
        matrix<T>   mul_mat(matrix<T>   &m);
        
        T   trace(void);
        // matrix<T>   transpose(void);
        

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
matrix<T> lerp(matrix<T> &m1, matrix<T> &m2, float ratio)
{
    if (ratio < 0 || ratio > 1)
        throw typename vector<T>::InvalidOperationException();
    else if (m1.shape() != m2.shape())
        throw typename vector<T>::InvalidOperationException();

    std::vector<T>  resultVector;
    for (int i = 0; i < m1.shape().second; i++)
    {
        //m1 iterators
        typename std::vector<T>::const_iterator start1 = m1.getData().begin() + i * m1.shape().first;
        typename std::vector<T>::const_iterator end1 = m1.getData().begin() + i * m1.shape().first + m1.shape().second; // end iterator -> + second.
        //m2 iterators
        typename std::vector<T>::const_iterator start2 = m2.getData().begin() + i * m2.shape().first;
        typename std::vector<T>::const_iterator end2 = m2.getData().begin() + i * m2.shape().first + m2.shape().second; // end iterator -> + second.

        //row 1
        vector<T>   vectorMatrix1(std::vector<T>(start1, end1));
        //row 2
        vector<T>   vectorMatrix2(std::vector<T>(start2, end2));

        std::vector<T> lerpRow = (vectorMatrix1.scale(1 - ratio) + vectorMatrix2.scale(ratio)).getVector();
        resultVector.insert(resultVector.end(), lerpRow.begin(), lerpRow.end()); //We insert each row of the std::vector.
    }
    return(matrix<T>(resultVector.data(), m1.shape().first, m1.shape().second));
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

#endif