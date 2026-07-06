#include "../inc/tester.hpp"

matrix<float> projection(float fov, float ratio, float near, float far)
{
    matrix<float> m({{(1/(ratio * std::tan(fov/2))), 0, 0, 0},
                {0, 1/(std::tan(fov/2)), 0, 0},
                {0, 0, (far + near)/(near - far), (2*far*near)/(near - far)},
                {0, 0, -1, 0}});
    return m;                                                                                                                                                                                                                                                                                   
}