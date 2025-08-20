cmake_minimum_required(VERSION 3.15)
project(MyMathLib VERSION 0.1.0 LANGUAGES CXX)

# Require modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Create the library (header-only for now)
add_library(mymath INTERFACE)
target_include_directories(mymath INTERFACE ${PROJECT_SOURCE_DIR}/include)

# Example executable (src/main.cpp)
add_executable(demo src/main.cpp)
target_link_libraries(demo PRIVATE mymath)

# Add tests
enable_testing()
add_subdirectory(tests)