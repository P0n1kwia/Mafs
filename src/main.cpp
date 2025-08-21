#include <iostream>
#include "mafs/matrix.hpp"
int main() {
    mafs::Vector<float, 2> v1{ 1.0f };
    mafs::Vector<float, 2> v2{ 3.0f,4.0f };
    mafs::Matrix<float, 1, 2> mat{ v1 };
    mafs::Matrix<float, 1, 2>matr{ v2 };
  mafs::Matrix ma=  mafs::Matrix<float, 2, 2>::identity();
    
    std::cout << -matr;
    return 0;
}