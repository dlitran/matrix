#include "../inc/tester.hpp"
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
T lerp(T f1, T f2, float ratio)
{
    if (ratio < 0 || ratio > 1)
        throw typename vector<T>::InvalidOperationException();

    T result;

    result = (f1 * (T(1) - T(ratio))) + (f2 * T(ratio)); //T concstructor in case T we have to multiply a complex * float.
    return(result);
}

void    lerpTester(void)
{
    vector<float> v1({1, 0});
    vector<float> v2({1, 1});
    matrix<float> m1({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
    matrix<float> m2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    float   t;
    
    t = 0.6;

    std::cout << "\033[31mReal numbers\033[0m"<< std::endl;
    std::cout << lerp((float)0., (float)5., (float)0.5) << std::endl;
    std::cout << lerp(v1, v2, t) << std::endl;
    std::cout << lerp(m1, m2, t) << std::endl;

    std::cout << "\033[31mComplex numbers\033[0m"<< std::endl;
    vector<Complex> c1({1, 0});
    vector<Complex> c2({1, 1});
    matrix<Complex> cm1({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
    matrix<Complex> cm2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

    std::cout << lerp(Complex(2, 1), Complex(1, 2), 0.5) << std::endl;
    std::cout << lerp(c1, c2, t) << std::endl;
    std::cout << lerp(cm1, cm2, t) << std::endl;    
}

template class vector<float>;
template class vector<Complex>;

template class matrix<float>;
template class matrix<Complex>;