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
		constexpr vec operator-() const
		{
			vec res{};
			for (size_t i = 0; i < N; i++)
			{
				res[i] = -data[i];
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
}//namespace mafs


