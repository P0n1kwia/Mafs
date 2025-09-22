#pragma once
#include <array>
#include <cassert>
#include <concepts>
#include <cmath>
#include <algorithm>
#include <iostream>

namespace mafs {
	template<typename T = float, size_t N = 3>
		requires std::floating_point<T> || std::integral<T>
	class vec
	{
	static_assert(N >= 1, "Vector dimension must be at least 1");
	public:
		//-----------------------------Constructors-----------------------------
		constexpr vec() { data.fill(T(0)); }
		constexpr vec(T scalar) { data.fill(scalar); }
		explicit vec(const std::array<T, N>& vals) { data = vals; }
		constexpr vec(std::initializer_list<T> init)
		{
			assert(init.size() <= N && "Initializer list to large");
			std::copy(init.begin(), init.end(), data.begin());
			std::fill(data.begin() + init.size(), data.end(), T(0));
		}
		//-----------------------------Operators-----------------------------
		constexpr T& operator[] (size_t i) { return data[i]; }
		constexpr const T& operator[] (size_t i) const { return data[i]; }

		constexpr vec& operator +=(const vec& v)
		{
			for (size_t i = 0; i < N; i++)
			{
				data[i] += v[i];
			}
			return *this;

		}
		constexpr vec& operator*=(T t)
		{
			for (size_t i = 0; i < N; ++i)
				data[i] *= t;
			return *this;
		}
		constexpr vec& operator/=(T t)
		{
			return *this *= (T(1) / t);
		}
		constexpr vec& operator-=(const vec& v)
		{
			for (size_t i = 0; i < N; i++)
			{
				data[i] -= v[i];
			}
			return *this;
		}
		constexpr vec operator-() const
		{
			vec res = *this;
			res *= -1;
			return res;
		}
		constexpr vec operator+(const vec& v) const
		{
			vec res = *this;
			res += v;
			return res;
		}
		constexpr vec operator-(const vec& v) const
		{
			vec res;
			for (size_t i = 0; i < N; ++i) {
				res[i] = data[i] - v[i];
			}
			return res;
		}
		
		constexpr vec operator*(T t) const
		{
			vec res;
			for (size_t i = 0; i < N; i++)
			{
				res[i] = data[i] * t;
			}
			return res;
		}
		friend constexpr vec operator*(T t, const vec& v)
		{
			return v * t;
		}
		template<typename U = T>
		constexpr vec operator/(U t) const
		{
			return *this * (U(1) / t);
		}
		bool operator==(const vec& v) const {
			if constexpr (std::floating_point<T>)
			{
				constexpr T eps = T(1e-8);
				for (size_t i = 0; i < N; ++i) {
					if (std::abs(data[i] - v[i]) > eps) return false;
				}
				return true;
			}
			else
				return data == v.data;
		}
		bool operator!=(const vec& v) const { return !(*this == v); }

		friend std::ostream& operator<<(std::ostream& out, const vec& v)
		{
			out << "[";
			for (size_t i = 0; i < N; i++)
			{
				out << v[i] << (i < N - 1 ? "," : "");
			}
			out << "]";
			return out;
		}
		//-----------------------------Functions-----------------------------
		constexpr T dot(const vec& v) const
		{
			T res = T(0);
			for (size_t i = 0; i < N; i++)
			{
				res += data[i] * v[i];
			}
			return res;
		}
		constexpr auto norm() const
		{
			return std::sqrt(dot(*this));
		}
		constexpr auto length_squared() const
		{
			return dot(*this);
		}
		constexpr size_t size() const
		{
			return N;
		}
		constexpr vec normalize() const
		{
			T len = norm();
			if (len < T(1e-8)) return vec{}; // Zero vector
			return *this / len;
		}
		constexpr T distance(const vec& v) const { return (*this - v).norm(); }
		constexpr vec lerp(const vec& v, T t) const
		{
			return *this + (v - *this) * t;
		}

		constexpr auto begin() { return data.begin(); }
		constexpr auto end() { return data.end(); }

		constexpr auto begin() const { return data.begin(); }
		constexpr auto end() const { return data.end(); }


		//-----------------------------Public Variables -----------------------------
		std::array<T, N> data;
	};

	template<typename T>
	class vec<T, 2>
	{
	public:
		T x, y;
		constexpr vec() : x{ T(0) }, y{ T(0) } {}
		constexpr vec(T xx, T yy) : x{ xx }, y{ yy } {}
		constexpr vec(T scalar) : x{ scalar }, y{ scalar } {}
		constexpr vec(std::initializer_list<T> init)
		{
			assert(init.size() <= 2 && "Initializer list too big!");
			auto it = init.begin();
			x = (it != init.end()) ? *it++ : T(0);
			y = (it != init.end()) ? *it++ : T(0);
		}
		constexpr T& operator[] (size_t i) { return (&x)[i]; }
		constexpr const T& operator[] (size_t i) const { return (&x)[i]; }

		constexpr vec& operator +=(const vec& v)
		{
			x += v[0];
			y += v[1];
			return *this;
		}
		constexpr vec& operator*=(T t)
		{
			x *= t;
			y *= t;
			return *this;
		}
		constexpr vec& operator/=(T t)
		{
			return *this *= (T(1) / t);
		}
		constexpr vec& operator-=(const vec& v)
		{
			x -= v[0];
			y -= v[1];
			return *this;
		}
		constexpr vec operator+(const vec& v) const
		{
			vec res = *this;
			res += v;
			return res;
		}
		constexpr vec operator-(const vec& v) const
		{
			vec res = *this;
			res -= v;
			return res;
		}
		constexpr vec operator-() const
		{
			return vec{ -x,-y };
		}
		constexpr vec operator*(T t) const
		{
			vec res = *this;
			res *= t;
			return res;
		}
		friend constexpr vec operator*(T t, const vec& v)
		{
			return v * t;
		}
		template<typename U = T>
		constexpr vec operator/(U t) const
		{
			return *this * (U(1) / t);
		}
		bool operator==(const vec& v) const {
			if constexpr (std::floating_point<T>)
			{
				constexpr T eps = T(1e-8);
				if (std::abs(x - v[0]) < eps && std::abs(y - v[1]) < eps)return true;
				return false;

			}
			else
				return x == v[0] && y == v[1];
		}
		bool operator!=(const vec& v) const { return !(*this == v); }

		friend std::ostream& operator<<(std::ostream& out, const vec& v)
		{
			out << "[";
			out << v[0] << "," << v[1];
			out << "]";
			return out;
		}
		//-----------------------------Functions-----------------------------
		constexpr T dot(const vec& v) const
		{	
			return x * v[0] + y * v[1];
		}
		constexpr auto norm() const
		{
			return std::sqrt(dot(*this));
		}
		constexpr auto length_squared() const
		{
			return dot(*this);
		}
		constexpr vec normalize() const
		{
			T len = norm();
			if (len < T(1e-8)) return vec{}; // Zero vector
			return *this / len;
		}
		constexpr T distance(const vec& v) const { return (*this - v).norm(); }
		constexpr vec lerp(const vec& v, T t) const
		{
			return *this + (v - *this) * t;
		}
	};
	template<typename T>
	class vec<T, 3>
	{
	public:
		T x, y,z;
		constexpr vec() : x{ T(0) }, y{ T(0) }, z{ T(0) } {}
		constexpr vec(T xx, T yy, T zz) : x{ xx }, y{ yy }, z{ zz } {}
		constexpr vec(T scalar) : x{ scalar }, y{ scalar }, z{ scalar } {}
		constexpr vec(std::initializer_list<T> init)
		{
			assert(init.size() <= 3 && "Initializer list too big!");
			auto it = init.begin();
			x = (it != init.end()) ? *it++ : T(0);
			y = (it != init.end()) ? *it++ : T(0);
			z = (it != init.end()) ? *it++ : T(0);
		}
		constexpr T& operator[] (size_t i) { return (&x)[i]; }
		constexpr const T& operator[] (size_t i) const { return (&x)[i]; }

		constexpr vec& operator +=(const vec& v)
		{
			x += v[0];
			y += v[1];
			z += v[2];
			return *this;
		}
		constexpr vec& operator*=(T t)
		{
			x *= t;
			y *= t;
			z *= t;
			return *this;
		}
		constexpr vec& operator/=(T t)
		{
			return *this *= (T(1) / t);
		}
		constexpr vec& operator-=(const vec& v)
		{
			x -= v[0];
			y -= v[1];
			z -= v[2];
			return *this;
		}
		constexpr vec operator+(const vec& v) const
		{
			vec res = *this;
			res += v;
			return res;
		}
		constexpr vec operator-(const vec& v) const
		{
			vec res = *this;
			res -= v;
			return res;
		}
		constexpr vec operator-() const
		{
			return vec{ -x,-y,-z};
		}
		constexpr vec operator*(T t) const
		{
			vec res = *this;
			res *= t;
			return res;
		}
		friend constexpr vec operator*(T t, const vec& v)
		{
			return v * t;
		}
		template<typename U = T>
		constexpr vec operator/(U t) const
		{
			return *this * (U(1) / t);
		}
		bool operator==(const vec& v) const {
			if constexpr (std::floating_point<T>)
			{
				constexpr T eps = T(1e-8);
				if (std::abs(x - v[0]) < eps && std::abs(y - v[1]) < eps && std::abs(z-v[2]) < eps)return true;
				return false;

			}
			else
				return x == v[0] && y == v[1] && z==v[2];
		}
		bool operator!=(const vec& v) const { return !(*this == v); }

		friend std::ostream& operator<<(std::ostream& out, const vec& v)
		{
			out << "[";
			out << v[0] << "," << v[1] <<","<<v[2];
			out << "]";
			return out;
		}
		//-----------------------------Functions-----------------------------
		constexpr T dot(const vec& v) const
		{
			return x * v[0] + y * v[1] + z*v[2];
		}
		constexpr vec cross(const vec& v) const
		{
			return vec{ y * v[2] - z * v[1],z * v[0] - x * v[2],x * v[1] - y * v[0] };
		}
		constexpr auto norm() const
		{
			return std::sqrt(dot(*this));
		}
		constexpr auto length_squared() const
		{
			return dot(*this);
		}
		constexpr vec normalize() const
		{
			T len = norm();
			if (len < T(1e-8)) return vec{}; // Zero vector
			return *this / len;
		}
		constexpr T distance(const vec& v) const { return (*this - v).norm(); }
		constexpr vec lerp(const vec& v, T t) const
		{
			return *this + (v - *this) * t;
		}
		constexpr vec<T, 2> xy() const { return vec<T, 2>{ x,y }; }
		constexpr vec<T, 2> xz() const { return vec<T, 2>{ x,z }; }
		constexpr vec<T, 2> yz() const { return vec<T, 2>{ y,z }; }
	};
	template<typename T>
	class vec<T, 4>
	{
	public:
		T x, y, z,w;
		constexpr vec() : x{ T(0) }, y{ T(0) }, z{ T(0) }, w{ T(0) } {}
		constexpr vec(T xx, T yy, T zz, T ww) : x{ xx }, y{ yy }, z{ zz }, w{ ww } {}
		constexpr vec(T scalar) : x{ scalar }, y{ scalar }, z{ scalar }, w{ scalar } {}
		constexpr vec(std::initializer_list<T> init)
		{
			assert(init.size() <= 4 && "Initializer list too big!");
			auto it = init.begin();
			x = (it != init.end()) ? *it++ : T(0);
			y = (it != init.end()) ? *it++ : T(0);
			z = (it != init.end()) ? *it++ : T(0);
			w = (it != init.end()) ? *it++ : T(0);
		}
		constexpr T& operator[] (size_t i) { return (&x)[i]; }
		constexpr const T& operator[] (size_t i) const { return (&x)[i]; }

		constexpr vec& operator +=(const vec& v)
		{
			x += v[0];
			y += v[1];
			z += v[2];
			w += v[3];
			return *this;
		}
		constexpr vec& operator*=(T t)
		{
			x *= t;
			y *= t;
			z *= t;
			w *= t;
			return *this;
		}
		constexpr vec& operator/=(T t)
		{
			return *this *= (T(1) / t);
		}
		constexpr vec& operator-=(const vec& v)
		{
			x -= v[0];
			y -= v[1];
			z -= v[2];
			w -= v[3];
			return *this;
		}
		constexpr vec operator+(const vec& v) const
		{
			vec res = *this;
			res += v;
			return res;
		}
		constexpr vec operator-(const vec& v) const
		{
			vec res = *this;
			res -= v;
			return res;
		}
		constexpr vec operator-() const
		{
			return vec{ -x,-y,-z,-w };
		}
		constexpr vec operator*(T t) const
		{
			vec res = *this;
			res *= t;
			return res;
		}
		friend constexpr vec operator*(T t, const vec& v)
		{
			return v * t;
		}
		template<typename U = T>
		constexpr vec operator/(U t) const
		{
			return *this * (U(1) / t);
		}
		bool operator==(const vec& v) const {
			if constexpr (std::floating_point<T>)
			{
				constexpr T eps = T(1e-8);
				if (std::abs(x - v[0]) < eps && std::abs(y - v[1]) < eps && std::abs(z - v[2]) < eps && std::abs(w-v[3]) < eps)return true;
				return false;

			}
			else
				return x == v[0] && y == v[1] && z == v[2] && w == v[3];
		}
		bool operator!=(const vec& v) const { return !(*this == v); }

		friend std::ostream& operator<<(std::ostream& out, const vec& v)
		{
			out << "[";
			out << v[0] << "," << v[1] << "," << v[2] <<","<<v[3];
			out << "]";
			return out;
		}
		//-----------------------------Functions-----------------------------
		constexpr T dot(const vec& v) const
		{
			return x * v[0] + y * v[1] + z * v[2] + w*v[3];
		}
		constexpr auto norm() const
		{
			return std::sqrt(dot(*this));
		}
		constexpr auto length_squared() const
		{
			return dot(*this);
		}
		constexpr vec normalize() const
		{
			T len = norm();
			if (len < T(1e-8)) return vec{}; // Zero vector
			return *this / len;
		}
		constexpr T distance(const vec& v) const { return (*this - v).norm(); }
		constexpr vec lerp(const vec& v, T t) const
		{
			return *this + (v - *this) * t;
		}
		constexpr vec<T, 2> xy() const { return vec<T, 2>{ x,y }; }
		constexpr vec<T, 2> xz() const { return vec<T, 2>{ x,z }; }
		constexpr vec<T, 2> yz() const { return vec<T,2>{ y,z }; }
		constexpr vec<T, 3> xyz() const { return vec<T, 3>{x, y, z}; }
	};

	using vec3f = vec<float, 3>;
	using vec3d = vec<double, 3>;
	using vec3i = vec<int, 3>;
	using vec4f = vec<float, 4>;
	using vec4d = vec<double, 4>;
	using vec4i = vec<int, 4>;

}//namespace mafs


