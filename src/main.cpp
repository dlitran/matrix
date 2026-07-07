#include "../inc/tester.hpp"

// void    some_random_tests(void)
// {
//     std::vector<Complex> c = {Complex(1, 2), Complex(1, 0), Complex(1, 1)};
//     vector num(c);
//     std::cout << num << std::endl;
//     float dataArray[2][3] = {
//         {1, 2, 3},
//         {4, 5, 6}
//     };
//     int m = ((int)sizeof(dataArray) / (int)sizeof(*dataArray));
//     int n = ((int)sizeof(*dataArray) / (int)sizeof(float));
//     matrix<float> myMatrix(*dataArray, m, n); //We pass an arr[] that decades ot a pointer.
//     std::cout << myMatrix.shape().first << " " << myMatrix.shape().second << std::endl;
//     std::cout << myMatrix << std::endl;

//     std::cout << std::to_string(dataArray[1][0]) << std::endl;

//     std::initializer_list<std::initializer_list<float>> dataList = {{6, 5, 4}, {3, 2, 1}};
//     matrix<float>   myMatrix2(dataList);
//     std::cout << myMatrix2 << std::endl;

//     myMatrix.add(myMatrix2);
//     std::cout << myMatrix <<  std::endl;

//     myMatrix.sub(myMatrix2);
//     myMatrix.sub(myMatrix);
//     std::cout << myMatrix <<  std::endl;

//     float   k = 3.5; //It doesn't allow this it when writing directly 3.5 because it treats it as a double, not a float.
//     myMatrix2.scl(k);
//     std::cout << myMatrix2 << std::endl;
//     std::cout << myMatrix.isSquare() << std::endl;
// }

// void    complex_operators_tests(void)
// {
//     Complex a(1, 2);
//     Complex b(1, 1);

//     std::cout << "a: " << a << ", b: " << b << std::endl;
//     std::cout << "b + b: " << a + b << std::endl;
//     std::cout << "b - b: " << a - b << std::endl;
//     std::cout << "a * b: " << a * b << std::endl;
//     std::cout << "a / b:  " << a/b << std::endl;
// }

void tester_bonus(void)
{
    matrix<float> matrix = projection(1.2, 1, 1, 100);
    // std::cout << m << std::endl;

    int i;
    int j;

    i = 0;
    while (i < matrix.shape().first)
    {
        j = 0;
        while (j < matrix.shape().second)
        {
            std::cout << matrix(i, j);
            if (j != matrix.shape().second - 1) 
                std::cout << ", ";
            j++;
        }
        i++;
        if (i != matrix.shape().first) 
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(void)
{
    try
    {
        // tester_add_sub_scl();
        // linear_combination_test();
        // lerpTester();
        // dot_product_tester();
        // norm_tester();
        // angle_cos_tester();
        // cross_product_tester();
        // matrix_multiplication_tester();
        // trace_tester();
        // transpose_tester();
        // row_enchelon_tester();
        // determinant_tester();
        // inverse_tester();
        // rank_tester();
        tester_bonus();
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
