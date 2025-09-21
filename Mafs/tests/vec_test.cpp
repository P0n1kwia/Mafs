#include "../include/mafs/vec.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>

namespace mafs::tests {

    int tests_run = 0;
    int tests_passed = 0;

    void assert_float(float a, float b, const char* msg, float eps = 1e-6f) {
        if (std::abs(a - b) > eps) {
            std::cerr << "FAIL: " << msg << " (Expected " << b << ", got " << a << ")\n";
            assert(false);
        }
        else {
            ++tests_passed;
        }
        ++tests_run;
    }

    void assert_true(bool condition, const char* msg) {
        if (!condition) {
            std::cerr << "FAIL: " << msg << "\n";
            assert(false);
        }
        else {
            ++tests_passed;
        }
        ++tests_run;
    }

    void test_constructors() {
        std::cout << "Testing constructors...\n";
        vec<float, 3> v1; // Default
        for (size_t i = 0; i < 3; ++i) {
            assert_float(v1[i], 0.0f, "Default constructor");
        }

        vec<float, 3> v_scalar(5.0f); // Scalar
        for (size_t i = 0; i < 3; ++i) {
            assert_float(v_scalar[i], 5.0f, "Scalar constructor");
        }

        std::array<float, 3> arr = { 1.0f, 2.0f, 3.0f };
        vec<float, 3> v2(arr); // Array
        assert_float(v2[0], 1.0f, "Array constructor x");
        assert_float(v2[1], 2.0f, "Array constructor y");
        assert_float(v2[2], 3.0f, "Array constructor z");

        vec<float, 3> v3{ 4.0f, 5.0f }; // Initializer list (partial)
        assert_float(v3[0], 4.0f, "Initializer list x");
        assert_float(v3[1], 5.0f, "Initializer list y");
        assert_float(v3[2], 0.0f, "Initializer list z");

        vec<int, 2> v4{ 1, 2 }; // Integral type
        assert_true(v4[0] == 1 && v4[1] == 2, "Integral initializer list");

       
    }

    void test_operators() {
        std::cout << "Testing operators...\n";
        vec<float, 3> v1{ 1.0f, 2.0f, 3.0f };
        vec<float, 3> v2{ 4.0f, 5.0f, 6.0f };

        // Accessor
        assert_float(v1[0], 1.0f, "Accessor x");
        assert_float(v1[1], 2.0f, "Accessor y");
        assert_float(v1[2], 3.0f, "Accessor z");

        // += operator
        auto v3 = v1;
        v3 += v2;
        assert_float(v3[0], 5.0f, "operator+= x");
        assert_float(v3[1], 7.0f, "operator+= y");
        assert_float(v3[2], 9.0f, "operator+= z");

        // + operator
        auto v4 = v1 + v2;
        assert_float(v4[0], 5.0f, "operator+ x");
        assert_float(v4[1], 7.0f, "operator+ y");
        assert_float(v4[2], 9.0f, "operator+ z");

        // -= operator
        auto v5 = v2;
        v5 -= v1;
        assert_float(v5[0], 3.0f, "operator-= x");
        assert_float(v5[1], 3.0f, "operator-= y");
        assert_float(v5[2], 3.0f, "operator-= z");

        // - operator
        auto v6 = v2 - v1;
        assert_float(v6[0], 3.0f, "operator- x");
        assert_float(v6[1], 3.0f, "operator- y");
        assert_float(v6[2], 3.0f, "operator- z");

        // Unary - operator
        auto v7 = -v1;
        assert_float(v7[0], -1.0f, "unary operator- x");
        assert_float(v7[1], -2.0f, "unary operator- y");
        assert_float(v7[2], -3.0f, "unary operator- z");

        // *= operator
        auto v8 = v1;
        v8 *= 2.0f;
        assert_float(v8[0], 2.0f, "operator*= x");
        assert_float(v8[1], 4.0f, "operator*= y");
        assert_float(v8[2], 6.0f, "operator*= z");

        // * operator (vector * scalar)
        auto v9 = v1 * 2.0f;
        assert_float(v9[0], 2.0f, "operator* x");
        assert_float(v9[1], 4.0f, "operator* y");
        assert_float(v9[2], 6.0f, "operator* z");

        // * operator (scalar * vector)
        auto v10 = 2.0f * v1;
        assert_float(v10[0], 2.0f, "scalar * vector x");
        assert_float(v10[1], 4.0f, "scalar * vector y");
        assert_float(v10[2], 6.0f, "scalar * vector z");

        // /= operator
        auto v11 = v9;
        v11 /= 2.0f;
        assert_float(v11[0], 1.0f, "operator/= x");
        assert_float(v11[1], 2.0f, "operator/= y");
        assert_float(v11[2], 3.0f, "operator/= z");

        // / operator
        auto v12 = v9 / 2.0f;
        assert_float(v12[0], 1.0f, "operator/ x");
        assert_float(v12[1], 2.0f, "operator/ y");
        assert_float(v12[2], 3.0f, "operator/ z");

        // == and != operators
        assert_true(v1 == v1, "operator== failed");
        assert_true(v1 != v2, "operator!= failed");

        // Integral type comparison
        vec<int, 2> vi1{ 1, 2 };
        vec<int, 2> vi2{ 1, 2 };
        vec<int, 2> vi3{ 2, 3 };
        assert_true(vi1 == vi2 && vi1 != vi3, "Integral comparison");
    }

    void test_math_functions() {
        std::cout << "Testing math functions...\n";
        vec<float, 3> v1{ 1.0f, 0.0f, 0.0f };
        vec<float, 3> v2{ 0.0f, 1.0f, 0.0f };

        // Dot product
        assert_float(v1.dot(v2), 0.0f, "Dot product orthogonal");
        assert_float(v1.dot(v1), 1.0f, "Dot product self");

        // Norm and length_squared
        vec<float, 3> v3{ 3.0f, 4.0f, 0.0f };
        assert_float(v3.length_squared(), 25.0f, "Length squared");
        assert_float(v3.norm(), 5.0f, "Norm");

        // Size
        assert_true(v3.size() == 3, "Size");

        // Normalize
        auto norm_v3 = v3.normalize();
        assert_float(norm_v3.norm(), 1.0f, "Normalized length");
        assert_float(norm_v3[0], 3.0f / 5.0f, "Normalized x");
        assert_float(norm_v3[1], 4.0f / 5.0f, "Normalized y");
        assert_float(norm_v3[2], 0.0f, "Normalized z");

        // Zero vector normalization
        vec<float, 3> zero_vec;
        auto norm_zero = zero_vec.normalize();
        assert_float(norm_zero[0], 0.0f, "Zero vector normalize x");
        assert_float(norm_zero[1], 0.0f, "Zero vector normalize y");
        assert_float(norm_zero[2], 0.0f, "Zero vector normalize z");

        // Distance
        assert_float(v1.distance(v2), std::sqrt(2.0f), "Distance");

        // Lerp
        auto lerp = v1.lerp(v2, 0.5f);
        assert_float(lerp[0], 0.5f, "Lerp x");
        assert_float(lerp[1], 0.5f, "Lerp y");
        assert_float(lerp[2], 0.0f, "Lerp z");

        // Iterators
        float sum = 0.0f;
        for (auto x : v3) sum += x;
        assert_float(sum, 7.0f, "Iterator sum");
    }



} // namespace mafs::tests

int main() {
    std::cout << "Running Vector tests...\n";
    mafs::tests::test_constructors();
    mafs::tests::test_operators();
    mafs::tests::test_math_functions();
    std::cout << "Tests completed: " << mafs::tests::tests_passed << "/" << mafs::tests::tests_run << " passed\n";
    return mafs::tests::tests_passed == mafs::tests::tests_run ? 0 : 1;
}