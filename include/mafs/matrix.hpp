#pragma once
#include "mafs/vector.hpp"
namespace mafs
{
	template<typename T, size_t N, size_t M>
	requires std::floating_point<T> || std::integral<T>
	class Matrix
	{
	public:
	//-----------------------------Constructors-----------------------------
	 Matrix() { data.fill(T(0)); }
	 explicit Matrix(const std::array<T, N* M>& vals) { data = vals; }
	 Matrix(const std::initializer_list<std::initializer_list<T>>& rows)
	 {
		 assert(rows.size() <= N && "To many rows in initializer list");
		 auto it = data.begin();
		 for (auto& row : rows)
		 {
			 assert(row.size() <= M && "To many columns in initializer list");
			 it = std::copy(row.begin(), row.end(), it);
			 it = std::fill_n(it, M - row.size(), T(0));
		 }
		 std::fill(it, data.end(), T(0));
	 }
	 Matrix(const std::initializer_list<mafs::Vector<T, M>>& init_rows)
	 {
		 auto it = data.begin();
		 for (auto& row_vector : init_rows)
		 {
			 it = std::copy(row_vector.begin(), row_vector.end(), it);
		 }
		 std::fill(it, data.end(), T(0));
	 }
	 //-----------------------------Operators-----------------------------
	 constexpr T& operator()(size_t row, size_t col)
	 {
		 return data[row * M + col];
	 }
	 constexpr const T& operator()(size_t row, size_t col) const
	 {
		 return data[row * M + col];
	 }
	 constexpr Matrix operator+(const Matrix& mat) const
	 {
		 Matrix res;
		 for (size_t i = 0; i < N; i++)
		 {
			 for (size_t j = 0; j < M; j++)
			 {
				 res(i, j) = (*this)(i, j) + mat(i, j);
			 }
		 }
		 return res;
	 }
	 constexpr Matrix operator-(const Matrix& mat) const
	 {
		 Matrix res;
		 for (size_t i = 0; i < N; i++)
		 {
			 for (size_t j = 0; j < M; j++)
			 {
				 res(i, j) = (*this)(i, j) - mat(i, j);
			 }
		 }
		 return res;
	 }
	 constexpr Matrix operator-() const
	 {
		 Matrix res;
		 for (size_t i = 0; i < N; i++)
		 {
			 for (size_t j = 0; j < M; j++)
			 {
				 res(i, j) = -(*this)(i, j);
			 }
		 }
		 return res;
	 }
	 constexpr Matrix operator*(T t)const
	 {
		 Matrix res;
		 for (size_t i = 0; i < N; i++)
		 {
			 for (size_t j = 0; j < M; j++)
			 {
				 res(i, j) = (*this)(i, j)*t;
			 }
		 }
		 return res;
	 }
	 constexpr Matrix operator/(T t) const
	 {
		 return *this * (T(1) / t);
	 }
	 constexpr Vector<T,N> operator*(const mafs::Vector<T,M>& v)
	 {

	 }
	 constexpr Matrix<T,N,K> operator*(const Matrix<T,M,K>& mat)
	 {

	 }
	 friend std::ostream& operator<< (std::ostream& out, const Matrix& mat)
	 {
		 
		 for (int i = 0; i < N; i++)
		 {
			 out << "[";
			 for (int j = 0; j < M; j++)
				 out << mat(i, j) << (j <M - 1 ? "," : "");
			 out << "]\n";

		 }
		 return out;
	 }
	 //-----------------------------Functions-----------------------------
	 constexpr Matrix<T, M, N> transpose() const
	 {

	 }
	 constexpr auto determinant() const
	 {

	 }

	 constexpr Vector<T, N> column(size_t) const
	 {

	 }
	 constexpr Vector<T, M> row(size_t) const
	 {

	 }
	 constexpr Matrix<T, M, N> inverse() const
	 {

	 }
	private:
		std::array<T, N* M> data;
	};
}

