#include <iostream>
#include "CVector.h"

int main()
{
    CVector vec1(10, 45, VectorType::POLAR);
    CVector vec2(10, -45, VectorType::POLAR);
    CVector vec3(10, 135, VectorType::POLAR);

    CVector vec4(7.07107, 7.07107, VectorType::XY);
    CVector vec5(7.07107, -7.07107, VectorType::XY);
    CVector vec6(-7.07107, 7.07107, VectorType::XY);
    CVector vec7(-7.07107, -7.07107, VectorType::XY);
    
    std::cout << vec1 << std::endl; 
    std::cout << vec2 << std::endl; 
    std::cout << vec3 << std::endl; 

    std::cout << vec4 << std::endl; 
    std::cout << vec5 << std::endl; 
    std::cout << vec6 << std::endl; 
    std::cout << vec7 << std::endl; 
    
}