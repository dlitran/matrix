#include "../inc/tester.hpp"

matrix<float> projection(float fov, float ratio, float near, float far)
{
    matrix<float> m({{(1/ratio*(std::tan(fov/2))), 0, 0, 0},
                {0, 1/(std::tan(fov/2)), 0, 0},
                {0, 0, 1/(far - near), (-near)/(far - near)},
                {0, 0, 0, 1}});
    return m;                                                                                                                                                                                                                                                                                   
}