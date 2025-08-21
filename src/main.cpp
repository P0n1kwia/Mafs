#include <iostream>
#include "mafs/matrix.hpp"
int main() {
    mafs::Vector<float, 2> v1{ 1.0f, 2.0f };
    mafs::Vector<float, 2> v2{ 3.0f,4.0f };
    mafs::Matrix<float, 2, 2> mat{ v1,v2 };
    
    std::cout << mat;
    return 0;
}