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
	class Vector
	{
	public:
		//-----------------------------Constructors-----------------------------
		Vector() { data.fill(T(0)); }
		explicit Vector(const std::array<T, N>& vals) :data(vals) {}
		Vector(std::initializer_list<T> init)
		{
			assert(init.size() <= N && "Initializer list to large");
			std::copy(init.begin(), init.end(), data.begin());
			std::fill(data.begin() + init.size(), data.end(), T(0));
		}
		//-----------------------------Operators-----------------------------
		constexpr T& operator[] (size_t i) { return data[i]; }
		constexpr const T& operator[] (size_t i) const { return data[i]; }

		Vector& operator +=(const Vector& v)
		{
			for (size_t i = 0; i < N; i++)
			{
				 data[i] += v[i];
			}
			return *this;
			
		}
		constexpr Vector operator+(const Vector& v) const
		{
			Vector res{};
			for (size_t i = 0; i < N; i++)
			{
				res[i] = data[i] + v[i];
			}
			return res;
		}
		constexpr Vector operator-(const Vector& v) const
		{
			Vector res;
			for (size_t i = 0; i < N; ++i) {
				res[i] = data[i] - v[i];
			}
			return res;
		}
		constexpr Vector operator-() const
		{
			Vector res{};
			for (size_t i = 0; i < N; i++)
			{
				res[i] = -data[i];
			}
			return res;
		}
		constexpr Vector operator*(T t) const
		{
			Vector res;
			for (size_t i = 0; i < N; i++)
			{
				res[i] = data[i] * t;
			}
			return res;
		}
		constexpr Vector operator/(T t) const
		{
			return *this * (T(1) / t);
		}
		bool operator==(const Vector& v) const {
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
		bool operator!=(const Vector& v) const { return !(*this == v); }
		
		friend std::ostream& operator<<(std::ostream& out, const Vector& v) 
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
		constexpr T dot(const Vector& v) const
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
		constexpr size_t size() const 
		{
			return N;
		}
		constexpr Vector cross(const Vector& v) const
		{
			static_assert(N == 3, "Cross product is only defined for 3D vectors");
			Vector res{};
			res[0] = data[1] * v[2] - data[2] * v[1];
			res[1] = data[2] * v[0] - data[0] * v[2];
			res[2] = data[0] * v[1] - data[1] * v[0];
			return res;
			
		}
		constexpr Vector normalize() const 
		{
			T len = norm();
			if (len == T(0)) throw std::runtime_error("Cannot normalize zero vector");
			return *this / len;
		}
		constexpr T distance(const Vector& v) const { return (*this - v).norm(); }
		constexpr Vector lerp(const Vector& v, T t) const
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
}


