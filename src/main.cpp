#include "../inc/vector.hpp"
#include "../inc/matrix.hpp"

void tester_add_sub_scl(void)
{
    std::vector<float> data1 = {1, 2, 3};
    std::vector<float> data2 = {1, 1, 1};
    std::vector<float> differtSizeData = {1, 3};

    vector myVector1(data1);
    vector myVector2(data2);
    vector differentSizeVector(differtSizeData);

    std::cout << std::to_string(myVector1.size()) << std::endl;
    std::cout << std::to_string(myVector2.size()) << std::endl;

    std::cout << myVector1 << std::endl;

    myVector1.add(myVector2);
    std::cout << myVector1 << std::endl;

    myVector1.sub(myVector2);
    std::cout << myVector1 << std::endl;

    float k = -2.5;
    myVector1.scl(k);
    std::cout << myVector1 << std::endl;

    std::cout << "Vector 1: " << myVector1 << "Vector 2: " << myVector2 << "Sum: " << (myVector1 + myVector2) << std::endl;
    std::cout << "Vector 1: " << myVector1 << "Vector 2: " << myVector2 << "Diff: " << (myVector1 - myVector2) << std::endl;

   // myVector1.add(differentSizeVector); //Throws an exception.
}

void    some_random_tests(void)
{
    std::vector<Complex> c = {Complex(1, 2), Complex(1, 0), Complex(1, 1)};
    vector num(c);
    std::cout << num << std::endl;
    float dataArray[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int m = ((int)sizeof(dataArray) / (int)sizeof(*dataArray));
    int n = ((int)sizeof(*dataArray) / (int)sizeof(float));
    matrix<float> myMatrix(*dataArray, m, n); //We pass an arr[] that decades ot a pointer.
    std::cout << myMatrix.shape().first << " " << myMatrix.shape().second << std::endl;
    std::cout << myMatrix << std::endl;

    std::cout << std::to_string(dataArray[1][0]) << std::endl;

    std::initializer_list<std::initializer_list<float>> dataList = {{6, 5, 4}, {3, 2, 1}};
    matrix<float>   myMatrix2(dataList);
    std::cout << myMatrix2 << std::endl;

    myMatrix.add(myMatrix2);
    std::cout << myMatrix <<  std::endl;

    myMatrix.sub(myMatrix2);
    myMatrix.sub(myMatrix);
    std::cout << myMatrix <<  std::endl;

    float   k = 3.5; //It doesn't allow this it when writing directly 3.5 because it treats it as a double, not a float.
    myMatrix2.scl(k);
    std::cout << myMatrix2 << std::endl;
    std::cout << myMatrix.isSquare() << std::endl;
}

void    linear_combination_test()
{
    vector<float> vec1({1, 1, 1});
    vector<float> vec2({1, 2, 1});
    vector<float> vec3({1, 0, 0});
    vector<float> coefs({1, 1, -10});

    std::cout << "vector 1: " << vec1;
    std::cout << "vector 2: " << vec2;
    std::cout << "vector 3: " << vec3;
    std::cout << "Coefficients: " << coefs;
    std::vector<vector<float>> vectorList = {vec1, vec2, vec3};
    std::cout << "Result: " << linear_combination(vectorList, coefs) << std::endl;
}

void    lerpTester(void)
{
    vector<float> v1({1, 0});
    vector<float> v2({1, 1});
    matrix<float> m1({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
    matrix<float> m2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    float   t;
    
    t = 0.6;

    std::cout << lerp((float)0., (float)5., (float)0.5) << std::endl;
    std::cout << lerp(v1, v2, t) << std::endl;
    std::cout << lerp(m1, m2, t) << std::endl;
}

void    dot_norm_cos_tester(void)
{
    vector<float> v1({1, 1});
        vector<float> v2({1, 0});
        vector<Complex> c1({Complex(1, 2), Complex(0, 1)});
        vector<Complex> c2({Complex(0, -1), Complex(2, 0)});

        std::cout << "The dot product is: " << v1.dot(v2) << std::endl;
        std::cout << "The manhattan norm is: " << c1.norm_1() << std::endl;
        std::cout << "The manhattan norm is: " << v1.norm_1() << std::endl;
        std::cout << "The euclidian norm is: " << c1.norm() << std::endl;
        std::cout << "The euclidian norm is: " << v1.norm() << std::endl;
        std::cout << "The supreme norm is: " << c1.norm_inf() << std::endl;
        std::cout << "The supreme norm is: " << v1.norm_inf() << std::endl;
        std::cout << "angle cos: " << angle_cos(v1, v2) << std::endl;
}

void    cross_product_tester(void)
{
    vector<Complex> c1({Complex(1, 2), Complex(0, 1), Complex(1, 1)});
    vector<Complex> c2({Complex(0, -1), Complex(2, 0), Complex(-1, -1)});

    std::cout << "cross product: " << cross_product(c1, c2) << std::endl;
}

void    matrix_multiplication_tester(void)
{
    matrix<float> m1({{1, 0, 0}, {0, 10, 0}, {0, 0, 1}});
    matrix<float> m2({{1, 2, 3, 4, 1}, {5, 6, 7, 8, 1}, {9, 10, 11, 12, 1}});
    vector<float> v1({1, 0, 2});
    //std::cout << m1.mul_vec(v1) << std::endl;
    std::cout << m1.mul_mat(m2) << std::endl;
}

void    trace_tester(void)
{
    matrix<float> m1({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    matrix<Complex> m2({{Complex(1, 2), Complex(1, 0)},
                        {Complex(1, 1), Complex(0, 1)}
                        });
    std::cout << m1.trace() << std::endl;
    std::cout << m2.trace() << std::endl;
}

int main(void)
{
    try
    {
        //tester_add_sub_scl();
        //some_random_tests()
        //liner_combination_test();
        //lerpTester();
        // dot_norm_cos_tester(void);
        // cross_product_tester();
        //matrix_multiplication_tester();
        trace_tester();

    }
    catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}

//Hay que poner esto aquí porque si no el linker ignora las definiciones específicas de los templates y da error de compilación.
template class vector<float>;
template class vector<Complex>;

