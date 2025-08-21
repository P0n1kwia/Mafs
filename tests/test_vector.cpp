#include "mafs/vector.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>

namespace mafs {

    void test_constructors() {
        std::cout << "Testing constructors...\n";
        Vector<float, 3> v1; // Default
        for (size_t i = 0; i < 3; ++i) {
            assert(v1[i] == 0.0f && "Default constructor failed");
        }

        std::array<float, 3> arr = { 1.0f, 2.0f, 3.0f };
        Vector<float, 3> v2(arr); // Array constructor
        assert(v2[0] == 1.0f && v2[1] == 2.0f && v2[2] == 3.0f && "Array constructor failed");

        Vector<float, 3> v3{ 4.0f, 5.0f }; // Initializer list (partial)
        assert(v3[0] == 4.0f && v3[1] == 5.0f && v3[2] == 0.0f && "Initializer list constructor failed");

        Vector<int, 2> v4{ 1, 2 }; // Integral type
        assert(v4[0] == 1 && v4[1] == 2 && "Integral initializer list failed");
    }

    void test_operators() {
        std::cout << "Testing operators...\n";
        Vector<float, 3> v1{ 1.0f, 2.0f, 3.0f };
        Vector<float, 3> v2{ 4.0f, 5.0f, 6.0f };

        // Accessor
        assert(v1[0] == 1.0f && v1[1] == 2.0f && v1[2] == 3.0f && "Accessor failed");

        // += operator
        auto v3 = v1;
        v3 += v2;
        assert(v3[0] == 5.0f && v3[1] == 7.0f && v3[2] == 9.0f && "+= operator failed");

        // + operator
        auto v4 = v1 + v2;
        assert(v4[0] == 5.0f && v4[1] == 7.0f && v4[2] == 9.0f && "+ operator failed");

        // - operator
        auto v5 = v2 - v1;
        assert(v5[0] == 3.0f && v5[1] == 3.0f && v5[2] == 3.0f && "- operator failed");

        // Unary - operator
        auto v6 = -v1;
        assert(v6[0] == -1.0f && v6[1] == -2.0f && v6[2] == -3.0f && "Unary - operator failed");

        // * operator (scalar)
        auto v7 = v1 * 2.0f;
        assert(v7[0] == 2.0f && v7[1] == 4.0f && v7[2] == 6.0f && "* operator failed");

        // / operator (scalar)
        auto v8 = v7 / 2.0f;
        assert(v8 == v1 && "/ operator failed");

        // == and != operators
        assert(v1 == v1 && "== operator failed");
        assert(v1 != v2 && "!= operator failed");

        // Integral type comparison
        Vector<int, 2> vi1{ 1, 2 };
        Vector<int, 2> vi2{ 1, 2 };
        Vector<int, 2> vi3{ 2, 3 };
        assert(vi1 == vi2 && vi1 != vi3 && "Integral comparison failed");
    }

    void test_math_functions() {
        std::cout << "Testing math functions...\n";
        Vector<float, 3> v1{ 1.0f, 0.0f, 0.0f };
        Vector<float, 3> v2{ 0.0f, 1.0f, 0.0f };

        // Dot product
        float dot = v1.dot(v2);
        assert(std::abs(dot - 0.0f) < 1e-6 && "Dot product failed");

        // Norm
        Vector<float, 3> v3{ 3.0f, 4.0f, 0.0f };
        float norm = v3.norm();
        assert(std::abs(norm - 5.0f) < 1e-6 && "Norm failed");

        // Size
        assert(v3.size() == 3 && "Size failed");

        // Cross product
        auto cross = v1.cross(v2);
        assert(std::abs(cross[0] - 0.0f) < 1e-6 && std::abs(cross[1] - 0.0f) < 1e-6 && std::abs(cross[2] - 1.0f) < 1e-6 && "Cross product failed");

        // Normalize
        auto norm_v3 = v3.normalize();
        assert(std::abs(norm_v3.norm() - 1.0f) < 1e-6 && "Normalize failed");

        // Zero norm case
        Vector<float, 3> zero_vec;
        try {
            zero_vec.normalize();
            assert(false && "Normalize should throw on zero vector");
        }
        catch (const std::runtime_error&) {
            // Expected
        }

        // Distance
        float dist = v1.distance(v2);
        assert(std::abs(dist - std::sqrt(2.0f)) < 1e-6 && "Distance failed");

        // Lerp
        auto lerp = v1.lerp(v2, 0.5f);
        assert(std::abs(lerp[0] - 0.5f) < 1e-6 && std::abs(lerp[1] - 0.5f) < 1e-6 && lerp[2] == 0.0f && "Lerp failed");
    }

    void test_graphics_use_case() {
        std::cout << "Testing graphics use case (triangle normal)...\n";
        Vector<float, 3> p1{ 0.0f, 0.0f, 0.0f };
        Vector<float, 3> p2{ 1.0f, 0.0f, 0.0f };
        Vector<float, 3> p3{ 0.0f, 1.0f, 0.0f };

        // Triangle edges
        auto v1 = p2 - p1;
        auto v2 = p3 - p1;

        // Surface normal
        auto normal = v1.cross(v2).normalize();
        assert(std::abs(normal[0] - 0.0f) < 1e-6 && std::abs(normal[1] - 0.0f) < 1e-6 && std::abs(normal[2] - 1.0f) < 1e-6 && "Triangle normal failed");

        // Lighting intensity
        Vector<float, 3> light_dir{ 0.0f, 0.0f, 1.0f };
        float intensity = normal.dot(light_dir);
        assert(std::abs(intensity - 1.0f) < 1e-6 && "Lighting intensity failed");
    }

} // namespace mafs

int main() {
    std::cout << "Running Vector tests...\n";
    mafs::test_constructors();
    mafs::test_operators();
    mafs::test_math_functions();
    mafs::test_graphics_use_case();
    std::cout << "All tests passed!\n";
    return 0;
}