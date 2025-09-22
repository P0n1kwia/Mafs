#include "../include/mafs/vec.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

namespace mafs::test {

    void assert_true(bool condition, const std::string& test_name) {
        if (condition) {
            std::cout << "[PASS] " << test_name << std::endl;
        }
        else {
            std::cout << "[FAIL] " << test_name << std::endl;
            assert(false);
        }
    }

    template<typename T>
    bool approx_equal(T a, T b, T eps = T(1e-6)) {
        return std::abs(a - b) < eps;
    }

    void test_vec_general() {
        // Test vec<float, 3> (general template)
        mafs::vec<float, 3> v1; // Default constructor
        assert_true(v1[0] == 0 && v1[1] == 0 && v1[2] == 0, "vec<float, 3> default constructor");

        mafs::vec<float, 3> v2(5.0f); // Scalar constructor
        assert_true(approx_equal(v2[0], 5.0f) && approx_equal(v2[1], 5.0f) && approx_equal(v2[2], 5.0f), "vec<float, 3> scalar constructor");

       

        mafs::vec<float, 3> v4{ 1.0f, 2.0f }; // Initializer list
        assert_true(approx_equal(v4[0], 1.0f) && approx_equal(v4[1], 2.0f) && approx_equal(v4[2], 0.0f), "vec<float, 3> initializer list");

        // Operators
        mafs::vec<float, 3> v5{ 1.0f, 2.0f, 3.0f };
        mafs::vec<float, 3> v6{ 4.0f, 5.0f, 6.0f };
        mafs::vec<float, 3> sum = v5 + v6;
        assert_true(approx_equal(sum[0], 5.0f) && approx_equal(sum[1], 7.0f) && approx_equal(sum[2], 9.0f), "vec<float, 3> addition");

        mafs::vec<float, 3> diff = v6 - v5;
        assert_true(approx_equal(diff[0], 3.0f) && approx_equal(diff[1], 3.0f) && approx_equal(diff[2], 3.0f), "vec<float, 3> subtraction");

        mafs::vec<float, 3> neg = -v5;
        assert_true(approx_equal(neg[0], -1.0f) && approx_equal(neg[1], -2.0f) && approx_equal(neg[2], -3.0f), "vec<float, 3> negation");

        mafs::vec<float, 3> scale = v5 * 2.0f;
        assert_true(approx_equal(scale[0], 2.0f) && approx_equal(scale[1], 4.0f) && approx_equal(scale[2], 6.0f), "vec<float, 3> scalar multiply");

        mafs::vec<float, 3> scale2 = 2.0f * v5;
        assert_true(scale == scale2, "vec<float, 3> scalar multiply commutative");

        mafs::vec<float, 3> div = v5 / 2.0f;
        assert_true(approx_equal(div[0], 0.5f) && approx_equal(div[1], 1.0f) && approx_equal(div[2], 1.5f), "vec<float, 3> division");

        v5 += v6;
        assert_true(approx_equal(v5[0], 5.0f) && approx_equal(v5[1], 7.0f) && approx_equal(v5[2], 9.0f), "vec<float, 3> += operator");

        v5 -= v6;
        assert_true(approx_equal(v5[0], 1.0f) && approx_equal(v5[1], 2.0f) && approx_equal(v5[2], 3.0f), "vec<float, 3> -= operator");

        v5 *= 2.0f;
        assert_true(approx_equal(v5[0], 2.0f) && approx_equal(v5[1], 4.0f) && approx_equal(v5[2], 6.0f), "vec<float, 3> *= operator");

        v5 /= 2.0f;
        assert_true(approx_equal(v5[0], 1.0f) && approx_equal(v5[1], 2.0f) && approx_equal(v5[2], 3.0f), "vec<float, 3> /= operator");

        // Equality
        assert_true(v5 == mafs::vec<float, 3>{1.0f, 2.0f, 3.0f}, "vec<float, 3> equality");
        assert_true(v5 != v6, "vec<float, 3> inequality");

        // Functions
        float dot = v5.dot(v6);
        assert_true(approx_equal(dot, 32.0f), "vec<float, 3> dot product");

        float norm = v5.norm();
        assert_true(approx_equal(norm, std::sqrt(14.0f)), "vec<float, 3> norm");

        float len_sq = v5.length_squared();
        assert_true(approx_equal(len_sq, 14.0f), "vec<float, 3> length_squared");

       

        mafs::vec<float, 3> normed = v5.normalize();
        assert_true(approx_equal(normed.norm(), 1.0f) || normed == mafs::vec<float, 3>{}, "vec<float, 3> normalize");

        float dist = v5.distance(v6);
        assert_true(approx_equal(dist, std::sqrt(27.0f)), "vec<float, 3> distance");

        mafs::vec<float, 3> lerp = v5.lerp(v6, 0.5f);
        assert_true(approx_equal(lerp[0], 2.5f) && approx_equal(lerp[1], 3.5f) && approx_equal(lerp[2], 4.5f), "vec<float, 3> lerp");

        
        
    }

    void test_vec2() {
        // Test vec<float, 2>
        mafs::vec<float, 2> v1; // Default constructor
        assert_true(approx_equal(v1.x, 0.0f) && approx_equal(v1.y, 0.0f), "vec<float, 2> default constructor");

        mafs::vec<float, 2> v2(5.0f); // Scalar constructor
        assert_true(approx_equal(v2.x, 5.0f) && approx_equal(v2.y, 5.0f), "vec<float, 2> scalar constructor");

        mafs::vec<float, 2> v3{ 1.0f, 2.0f }; // Initializer list
        assert_true(approx_equal(v3.x, 1.0f) && approx_equal(v3.y, 2.0f), "vec<float, 2> initializer list");

        mafs::vec<float, 2> v4{ 1.0f }; // Partial initializer list
        assert_true(approx_equal(v4.x, 1.0f) && approx_equal(v4.y, 0.0f), "vec<float, 2> partial initializer list");

        // Operators
        mafs::vec<float, 2> v5{ 1.0f, 2.0f };
        mafs::vec<float, 2> v6{ 3.0f, 4.0f };
        mafs::vec<float, 2> sum = v5 + v6;
        assert_true(approx_equal(sum.x, 4.0f) && approx_equal(sum.y, 6.0f), "vec<float, 2> addition");

        mafs::vec<float, 2> diff = v6 - v5;
        assert_true(approx_equal(diff.x, 2.0f) && approx_equal(diff.y, 2.0f), "vec<float, 2> subtraction");

        mafs::vec<float, 2> neg = -v5;
        assert_true(approx_equal(neg.x, -1.0f) && approx_equal(neg.y, -2.0f), "vec<float, 2> negation");

        mafs::vec<float, 2> scale = v5 * 2.0f;
        assert_true(approx_equal(scale.x, 2.0f) && approx_equal(scale.y, 4.0f), "vec<float, 2> scalar multiply");

        mafs::vec<float, 2> scale2 = 2.0f * v5;
        assert_true(scale == scale2, "vec<float, 2> scalar multiply commutative");

        mafs::vec<float, 2> div = v5 / 2.0f;
        assert_true(approx_equal(div.x, 0.5f) && approx_equal(div.y, 1.0f), "vec<float, 2> division");

        v5 += v6;
        assert_true(approx_equal(v5.x, 4.0f) && approx_equal(v5.y, 6.0f), "vec<float, 2> += operator");

        v5 -= v6;
        assert_true(approx_equal(v5.x, 1.0f) && approx_equal(v5.y, 2.0f), "vec<float, 2> -= operator");

        v5 *= 2.0f;
        assert_true(approx_equal(v5.x, 2.0f) && approx_equal(v5.y, 4.0f), "vec<float, 2> *= operator");

        v5 /= 2.0f;
        assert_true(approx_equal(v5.x, 1.0f) && approx_equal(v5.y, 2.0f), "vec<float, 2> /= operator");

        // Equality
        assert_true(v5 == mafs::vec<float, 2>{1.0f, 2.0f}, "vec<float, 2> equality");
        assert_true(v5 != v6, "vec<float, 2> inequality");

        // Functions
        float dot = v5.dot(v6);
        assert_true(approx_equal(dot, 11.0f), "vec<float, 2> dot product");

        float norm = v5.norm();
        assert_true(approx_equal(norm, std::sqrt(5.0f)), "vec<float, 2> norm");

        float len_sq = v5.length_squared();
        assert_true(approx_equal(len_sq, 5.0f), "vec<float, 2> length_squared");

        mafs::vec<float, 2> normed = v5.normalize();
        assert_true(approx_equal(normed.norm(), 1.0f) || normed == mafs::vec<float, 2>{}, "vec<float, 2> normalize");

        float dist = v5.distance(v6);
        assert_true(approx_equal(dist, std::sqrt(8.0f)), "vec<float, 2> distance");

        mafs::vec<float, 2> lerp = v5.lerp(v6, 0.5f);
        assert_true(approx_equal(lerp.x, 2.0f) && approx_equal(lerp.y, 3.0f), "vec<float, 2> lerp");
    }

    void test_vec3() {
        // Test vec<float, 3>
        mafs::vec<float, 3> v1; // Default constructor
        assert_true(approx_equal(v1.x, 0.0f) && approx_equal(v1.y, 0.0f) && approx_equal(v1.z, 0.0f), "vec<float, 3> default constructor");

        mafs::vec<float, 3> v2(5.0f); // Scalar constructor
        assert_true(approx_equal(v2.x, 5.0f) && approx_equal(v2.y, 5.0f) && approx_equal(v2.z, 5.0f), "vec<float, 3> scalar constructor");

        mafs::vec<float, 3> v3{ 1.0f, 2.0f, 3.0f }; // Initializer list
        assert_true(approx_equal(v3.x, 1.0f) && approx_equal(v3.y, 2.0f) && approx_equal(v3.z, 3.0f), "vec<float, 3> initializer list");

        mafs::vec<float, 3> v4{ 1.0f, 2.0f }; // Partial initializer list
        assert_true(approx_equal(v4.x, 1.0f) && approx_equal(v4.y, 2.0f) && approx_equal(v4.z, 0.0f), "vec<float, 3> partial initializer list");

        // Operators
        mafs::vec<float, 3> v5{ 1.0f, 2.0f, 3.0f };
        mafs::vec<float, 3> v6{ 4.0f, 5.0f, 6.0f };
        mafs::vec<float, 3> sum = v5 + v6;
       

        mafs::vec<float, 3> diff = v6 - v5;
        assert_true(approx_equal(diff.x, 3.0f) && approx_equal(diff.y, 3.0f) && approx_equal(diff.z, 3.0f), "vec<float, 3> subtraction");

        mafs::vec<float, 3> neg = -v5;
        assert_true(approx_equal(neg.x, -1.0f) && approx_equal(neg.y, -2.0f) && approx_equal(neg.z, -3.0f), "vec<float, 3> negation");

        mafs::vec<float, 3> scale = v5 * 2.0f;
        assert_true(approx_equal(scale.x, 2.0f) && approx_equal(scale.y, 4.0f) && approx_equal(scale.z, 6.0f), "vec<float, 3> scalar multiply");

        mafs::vec<float, 3> scale2 = 2.0f * v5;
        assert_true(scale == scale2, "vec<float, 3> scalar multiply commutative");

        mafs::vec<float, 3> div = v5 / 2.0f;
        assert_true(approx_equal(div.x, 0.5f) && approx_equal(div.y, 1.0f) && approx_equal(div.z, 1.5f), "vec<float, 3> division");

        v5 += v6;
        assert_true(approx_equal(v5.x, 5.0f) && approx_equal(v5.y, 7.0f) && approx_equal(v5.z, 9.0f), "vec<float, 3> += operator");

        v5 -= v6;
        assert_true(approx_equal(v5.x, 1.0f) && approx_equal(v5.y, 2.0f) && approx_equal(v5.z, 3.0f), "vec<float, 3> -= operator");

        v5 *= 2.0f;
        assert_true(approx_equal(v5.x, 2.0f) && approx_equal(v5.y, 4.0f) && approx_equal(v5.z, 6.0f), "vec<float, 3> *= operator");

        v5 /= 2.0f;
        assert_true(approx_equal(v5.x, 1.0f) && approx_equal(v5.y, 2.0f) && approx_equal(v5.z, 3.0f), "vec<float, 3> /= operator");

        // Equality
        assert_true(v5 == mafs::vec<float, 3>{1.0f, 2.0f, 3.0f}, "vec<float, 3> equality");
        assert_true(v5 != v6, "vec<float, 3> inequality");

        // Functions
        float dot = v5.dot(v6);
        assert_true(approx_equal(dot, 32.0f), "vec<float, 3> dot product");

        float norm = v5.norm();
        assert_true(approx_equal(norm, std::sqrt(14.0f)), "vec<float, 3> norm");

        float len_sq = v5.length_squared();
        assert_true(approx_equal(len_sq, 14.0f), "vec<float, 3> length_squared");

        mafs::vec<float, 3> normed = v5.normalize();
        assert_true(approx_equal(normed.norm(), 1.0f) || normed == mafs::vec<float, 3>{}, "vec<float, 3> normalize");

        float dist = v5.distance(v6);
        assert_true(approx_equal(dist, std::sqrt(27.0f)), "vec<float, 3> distance");

        mafs::vec<float, 3> lerp = v5.lerp(v6, 0.5f);
        assert_true(approx_equal(lerp.x, 2.5f) && approx_equal(lerp.y, 3.5f) && approx_equal(lerp.z, 4.5f), "vec<float, 3> lerp");

        // Cross product
        mafs::vec<float, 3> v7{ 1.0f, 0.0f, 0.0f };
        mafs::vec<float, 3> v8{ 0.0f, 1.0f, 0.0f };
        mafs::vec<float, 3> cross = v7.cross(v8);
        assert_true(approx_equal(cross.x, 0.0f) && approx_equal(cross.y, 0.0f) && approx_equal(cross.z, 1.0f), "vec<float, 3> cross product");

        // Swizzling
        mafs::vec<float, 2> xy = v5.xy();
        assert_true(approx_equal(xy.x, 1.0f) && approx_equal(xy.y, 2.0f), "vec<float, 3> xy swizzle");

        mafs::vec<float, 2> xz = v5.xz();
        assert_true(approx_equal(xz.x, 1.0f) && approx_equal(xz.y, 3.0f), "vec<float, 3> xz swizzle");

        mafs::vec<float, 2> yz = v5.yz();
        assert_true(approx_equal(yz.x, 2.0f) && approx_equal(yz.y, 3.0f), "vec<float, 3> yz swizzle");
    }

    void test_vec4() {
        // Test vec<float, 4>
        mafs::vec<float, 4> v1; // Default constructor
        assert_true(approx_equal(v1.x, 0.0f) && approx_equal(v1.y, 0.0f) && approx_equal(v1.z, 0.0f) && approx_equal(v1.w, 0.0f), "vec<float, 4> default constructor");

        mafs::vec<float, 4> v2(5.0f); // Scalar constructor
        assert_true(approx_equal(v2.x, 5.0f) && approx_equal(v2.y, 5.0f) && approx_equal(v2.z, 5.0f) && approx_equal(v2.w, 5.0f), "vec<float, 4> scalar constructor");

        mafs::vec<float, 4> v3{ 1.0f, 2.0f, 3.0f, 4.0f }; // Initializer list
        assert_true(approx_equal(v3.x, 1.0f) && approx_equal(v3.y, 2.0f) && approx_equal(v3.z, 3.0f) && approx_equal(v3.w, 4.0f), "vec<float, 4> initializer list");

        mafs::vec<float, 4> v4{ 1.0f, 2.0f }; // Partial initializer list
        assert_true(approx_equal(v4.x, 1.0f) && approx_equal(v4.y, 2.0f) && approx_equal(v4.z, 0.0f) && approx_equal(v4.w, 0.0f), "vec<float, 4> partial initializer list");

        // Operators
        mafs::vec<float, 4> v5{ 1.0f, 2.0f, 3.0f, 4.0f };
        mafs::vec<float, 4> v6{ 5.0f, 6.0f, 7.0f, 8.0f };
        mafs::vec<float, 4> sum = v5 + v6;
        assert_true(approx_equal(sum.x, 6.0f) && approx_equal(sum.y, 8.0f) && approx_equal(sum.z, 10.0f) && approx_equal(sum.w, 12.0f), "vec<float, 4> addition");

        mafs::vec<float, 4> diff = v6 - v5;
        assert_true(approx_equal(diff.x, 4.0f) && approx_equal(diff.y, 4.0f) && approx_equal(diff.z, 4.0f) && approx_equal(diff.w, 4.0f), "vec<float, 4> subtraction");

        mafs::vec<float, 4> neg = -v5;
        assert_true(approx_equal(neg.x, -1.0f) && approx_equal(neg.y, -2.0f) && approx_equal(neg.z, -3.0f) && approx_equal(neg.w, -4.0f), "vec<float, 4> negation");

        mafs::vec<float, 4> scale = v5 * 2.0f;
        assert_true(approx_equal(scale.x, 2.0f) && approx_equal(scale.y, 4.0f) && approx_equal(scale.z, 6.0f) && approx_equal(scale.w, 8.0f), "vec<float, 4> scalar multiply");

        mafs::vec<float, 4> scale2 = 2.0f * v5;
        assert_true(scale == scale2, "vec<float, 4> scalar multiply commutative");

        mafs::vec<float, 4> div = v5 / 2.0f;
        assert_true(approx_equal(div.x, 0.5f) && approx_equal(div.y, 1.0f) && approx_equal(div.z, 1.5f) && approx_equal(div.w, 2.0f), "vec<float, 4> division");

        v5 += v6;
        assert_true(approx_equal(v5.x, 6.0f) && approx_equal(v5.y, 8.0f) && approx_equal(v5.z, 10.0f) && approx_equal(v5.w, 12.0f), "vec<float, 4> += operator");

        v5 -= v6;
        assert_true(approx_equal(v5.x, 1.0f) && approx_equal(v5.y, 2.0f) && approx_equal(v5.z, 3.0f) && approx_equal(v5.w, 4.0f), "vec<float, 4> -= operator");

        v5 *= 2.0f;
        assert_true(approx_equal(v5.x, 2.0f) && approx_equal(v5.y, 4.0f) && approx_equal(v5.z, 6.0f) && approx_equal(v5.w, 8.0f), "vec<float, 4> *= operator");

        v5 /= 2.0f;
        assert_true(approx_equal(v5.x, 1.0f) && approx_equal(v5.y, 2.0f) && approx_equal(v5.z, 3.0f) && approx_equal(v5.w, 4.0f), "vec<float, 4> /= operator");

        // Equality
        assert_true(v5 == mafs::vec<float, 4>{1.0f, 2.0f, 3.0f, 4.0f}, "vec<float, 4> equality");
        assert_true(v5 != v6, "vec<float, 4> inequality");

        // Functions
        float dot = v5.dot(v6);
        assert_true(approx_equal(dot, 70.0f), "vec<float, 4> dot product");

        float norm = v5.norm();
        assert_true(approx_equal(norm, std::sqrt(30.0f)), "vec<float, 4> norm");

        float len_sq = v5.length_squared();
        assert_true(approx_equal(len_sq, 30.0f), "vec<float, 4> length_squared");

        mafs::vec<float, 4> normed = v5.normalize();
        assert_true(approx_equal(normed.norm(), 1.0f) || normed == mafs::vec<float, 4>{}, "vec<float, 4> normalize");

        float dist = v5.distance(v6);
        assert_true(approx_equal(dist, std::sqrt(64.0f)), "vec<float, 4> distance");

        mafs::vec<float, 4> lerp = v5.lerp(v6, 0.5f);
        assert_true(approx_equal(lerp.x, 3.0f) && approx_equal(lerp.y, 4.0f) && approx_equal(lerp.z, 5.0f) && approx_equal(lerp.w, 6.0f), "vec<float, 4> lerp");

        // Swizzling
        mafs::vec<float, 2> xy = v5.xy();
        assert_true(approx_equal(xy.x, 1.0f) && approx_equal(xy.y, 2.0f), "vec<float, 4> xy swizzle");

        mafs::vec<float, 2> xz = v5.xz();
        assert_true(approx_equal(xz.x, 1.0f) && approx_equal(xz.y, 3.0f), "vec<float, 4> xz swizzle");

        mafs::vec<float, 2> yz = v5.yz();
        assert_true(approx_equal(yz.x, 2.0f) && approx_equal(yz.y, 3.0f), "vec<float, 4> yz swizzle");

        mafs::vec<float, 3> xyz = v5.xyz();
        assert_true(approx_equal(xyz.x, 1.0f) && approx_equal(xyz.y, 2.0f) && approx_equal(xyz.z, 3.0f), "vec<float, 4> xyz swizzle");
    }

    void test_vec_int() {
        // Test vec<int, 3> for integral type
        mafs::vec<int, 3> v1; // Default constructor
        assert_true(v1[0] == 0 && v1[1] == 0 && v1[2] == 0, "vec<int, 3> default constructor");

        mafs::vec<int, 3> v2(5); // Scalar constructor
        assert_true(v2[0] == 5 && v2[1] == 5 && v2[2] == 5, "vec<int, 3> scalar constructor");

        mafs::vec<int, 3> v3{ 1, 2, 3 }; // Initializer list
        assert_true(v3[0] == 1 && v3[1] == 2 && v3[2] == 3, "vec<int, 3> initializer list");

        mafs::vec<int, 3> v4{ 1, 2 }; // Partial initializer list
        assert_true(v4[0] == 1 && v4[1] == 2 && v4[2] == 0, "vec<int, 3> partial initializer list");

        // Operators
        mafs::vec<int, 3> v5{ 1, 2, 3 };
        mafs::vec<int, 3> v6{ 4, 5, 6 };
        mafs::vec<int, 3> sum = v5 + v6;
        assert_true(sum[0] == 5 && sum[1] == 7 && sum[2] == 9, "vec<int, 3> addition");

        mafs::vec<int, 3> diff = v6 - v5;
        assert_true(diff[0] == 3 && diff[1] == 3 && diff[2] == 3, "vec<int, 3> subtraction");

        mafs::vec<int, 3> neg = -v5;
        assert_true(neg[0] == -1 && neg[1] == -2 && neg[2] == -3, "vec<int, 3> negation");

        mafs::vec<int, 3> scale = v5 * 2;
        assert_true(scale[0] == 2 && scale[1] == 4 && scale[2] == 6, "vec<int, 3> scalar multiply");

        v5 += v6;
        assert_true(v5[0] == 5 && v5[1] == 7 && v5[2] == 9, "vec<int, 3> += operator");

        v5 -= v6;
        assert_true(v5[0] == 1 && v5[1] == 2 && v5[2] == 3, "vec<int, 3> -= operator");

        v5 *= 2;
        assert_true(v5[0] == 2 && v5[1] == 4 && v5[2] == 6, "vec<int, 3> *= operator");

        // Equality
        assert_true(v5 == mafs::vec<int, 3>{2, 4, 6}, "vec<int, 3> equality");
        assert_true(v5 != v6, "vec<int, 3> inequality");

        // Functions
        int dot = v5.dot(v6);
        assert_true(dot == 64, "vec<int, 3> dot product");

        float norm = v5.norm();
        assert_true(approx_equal(norm, std::sqrt(56.0f)), "vec<int, 3> norm");

        int len_sq = v5.length_squared();
        assert_true(len_sq == 56, "vec<int, 3> length_squared");

       
    }

    void test_edge_cases() {
        // Zero vector normalization
        mafs::vec<float, 3> zero;
        mafs::vec<float, 3> normed = zero.normalize();
        assert_true(normed == mafs::vec<float, 3>{}, "vec<float, 3> zero vector normalize");

        // Division by small number
        mafs::vec<float, 3> v1{ 1.0f, 2.0f, 3.0f };
        mafs::vec<float, 3> div = v1 / 1e-10f;
        assert_true(std::isfinite(div[0]) && std::isfinite(div[1]) && std::isfinite(div[2]), "vec<float, 3> division by small number");

        // Equality with small differences
        mafs::vec<float, 3> v2{ 1.0f, 2.0f, 3.0f };
        mafs::vec<float, 3> v3{ 1.0f + 1e-9f, 2.0f, 3.0f };
        assert_true(v2 == v3, "vec<float, 3> equality with small difference");
        mafs::vec3d vektor{ {3,2,1} };
        std::cout << vektor;
    }

} // namespace mafs::test

int main() {
    std::cout << "Testing vec<float, 3> (general template)..." << std::endl;
    mafs::test::test_vec_general();

    std::cout << "\nTesting vec<float, 2>..." << std::endl;
    mafs::test::test_vec2();

    std::cout << "\nTesting vec<float, 3> (specialization)..." << std::endl;
    mafs::test::test_vec3();

    std::cout << "\nTesting vec<float, 4>..." << std::endl;
    mafs::test::test_vec4();

    std::cout << "\nTesting vec<int, 3>..." << std::endl;
    mafs::test::test_vec_int();

    std::cout << "\nTesting edge cases..." << std::endl;
    mafs::test::test_edge_cases();

    std::cout << "\nAll tests completed!" << std::endl;
    return 0;
}