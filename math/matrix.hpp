#pragma once

#ifndef __MATRIX__
#define __MATRIX__

#include "vector.hpp"

#define ret0(tuple) std::get<0>(tuple)
#define ret1(tuple) std::get<1>(tuple)
#define ret2(tuple) std::get<2>(tuple)
#define ret3(tuple) std::get<3>(tuple)

template<class T>
class mat3x3;

template<class T>
class mat4x4;

using mat3x3f = mat3x3<float>;
using mat3x3d = mat3x3<double>;
using mat3x3ld = mat3x3<long double>;

using mat4x4f = mat4x4<float>;
using mat4x4d = mat4x4<double>;
using mat4x4ld = mat4x4<long double>;

template<class T>
class mat3x3
{
private:
	//[Row][Col] indexed
	std::array<std::array<T, 3>, 3> elements;

public:
	static mat3x3<T> zero;
	static mat3x3<T> identity;

public:
	mat3x3()
	{
		static_assert(std::is_floating_point<T>::value, "Type T of mat3x3 must be a floating-point type!");
		elements[0] = { 1.0, 0.0, 0.0 };
		elements[1] = { 0.0, 1.0, 0.0 };
		elements[2] = { 0.0, 0.0, 1.0 };
	}

	mat3x3(T* elements, bool is_input_row_major = true/*or column major?*/)
	{
		if (is_input_row_major)
		{
			this->elements[0] = { elements[0], elements[1], elements[2] };
			this->elements[1] = { elements[3], elements[4], elements[5] };
			this->elements[2] = { elements[6], elements[7], elements[8] };
		}
		else
		{
			this->elements[0] = { elements[0], elements[3], elements[6] };
			this->elements[1] = { elements[1], elements[4], elements[7] };
			this->elements[2] = { elements[2], elements[5], elements[8] };
		}
	}

	mat3x3(T e00, T e01, T e02, T e10, T e11, T e12, T e20, T e21, T e22)
	{
		elements[0] = { e00, e01, e02 };
		elements[1] = { e10, e11, e12 };
		elements[2] = { e20, e21, e22 };
	}

	mat3x3(std::array<T, 3> subs0, std::array<T, 3> subs1, std::array<T, 3> subs2, 
		bool is_input_row_major = true/*or column major?*/)
	{
		if (is_input_row_major)
		{
			elements[0] = subs0;
			elements[1] = subs1;
			elements[2] = subs2;
		}
		else
		{
			elements[0] = { subs0[0], subs1[0], subs2[0] };
			elements[1] = { subs0[1], subs1[1], subs2[1] };
			elements[2] = { subs0[2], subs1[2], subs2[2] };
		}
	}

public:
	std::unique_ptr<T[]> copy(bool is_output_row_major = true/*or column major?*/) const
	{
		std::unique_ptr<T[]> ptr = std::make_unique<T[]>(9);
		if (is_output_row_major)
		{
			ptr[0] = elements[0][0]; ptr[1] = elements[0][1]; ptr[2] = elements[0][2];
			ptr[3] = elements[1][0]; ptr[4] = elements[1][1]; ptr[5] = elements[1][2];
			ptr[6] = elements[2][0]; ptr[7] = elements[2][1]; ptr[8] = elements[2][2];
		}
		else
		{
			ptr[0] = elements[0][0]; ptr[3] = elements[0][1]; ptr[6] = elements[0][2];
			ptr[1] = elements[1][0]; ptr[4] = elements[1][1]; ptr[7] = elements[1][2];
			ptr[2] = elements[2][0]; ptr[5] = elements[2][1]; ptr[8] = elements[2][2];
		}
		return ptr;
	}

	T& operator()(size_t row_index, size_t col_index)
	{
		if (row_index >= 3 || col_index >= 3 || row_index < 0 || col_index < 0) { throw std::out_of_range("mat3x3 index out of range!"); }
		return elements[row_index][col_index];
	}

	T operator()(size_t row_index, size_t col_index) const
	{
		if (row_index >= 3 || col_index >= 3 || row_index < 0 || col_index < 0) { throw std::out_of_range("mat3x3 index out of range!"); }
		return elements[row_index][col_index];
	}

	std::array<T, 3> row(size_t index) const
	{
		if (index >= 3 || index < 0) { throw std::out_of_range("mat3x3 index out of range!"); }
		return elements[index];
	}

	std::array<T, 3> col(size_t index) const
	{
		if (index >= 3 || index < 0) { throw std::out_of_range("mat3x3 index out of range!"); }
		return { elements[0][index], elements[1][index], elements[2][index] };
	}

	void set_row(size_t index, std::array<T, 3> rows)
	{
		if (index >= 3 || index < 0) { throw std::out_of_range("mat3x3 index out of range!"); }
		elements[index] = rows;
	}

	void set_col(size_t index, std::array<T, 3> cols)
	{
		if (index >= 3 || index < 0) { throw std::out_of_range("mat3x3 index out of range!"); }
		elements[0][index] = rows[0];
		elements[1][index] = rows[1];
		elements[2][index] = rows[2];
	}

public:
	T det() const
	{
		T cofactor00 = elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1];
		T cofactor10 = elements[1][2] * elements[2][0] - elements[1][0] * elements[2][2];
		T cofactor20 = elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0];

		return elements[0][0] * cofactor00 + elements[0][1] * cofactor10 + elements[0][2] * cofactor20;
	}

	std::tuple<bool, mat3x3<T>> inverse(T threshold = FLOATING_POINT_THRESHOLD) const
	{
		mat3x3<T> inversed;
		inversed(0, 0) = elements[1][1] * elements[2][2] - elements[1][2] * elements[2][1];
		inversed(0, 1) = elements[0][2] * elements[2][1] - elements[0][1] * elements[2][2];
		inversed(0, 2) = elements[0][1] * elements[1][2] - elements[0][2] * elements[1][1];
		inversed(1, 0) = elements[1][2] * elements[2][0] - elements[1][0] * elements[2][2];
		inversed(1, 1) = elements[0][0] * elements[2][2] - elements[0][2] * elements[2][0];
		inversed(1, 2) = elements[0][2] * elements[1][0] - elements[0][0] * elements[1][2];
		inversed(2, 0) = elements[1][0] * elements[2][1] - elements[1][1] * elements[2][0];
		inversed(2, 1) = elements[0][1] * elements[2][0] - elements[0][0] * elements[2][1];
		inversed(2, 2) = elements[0][0] * elements[1][1] - elements[0][1] * elements[1][0];

		T det = elements[0][0] * inversed(0, 0) + elements[0][1] * inversed(1, 0) + elements[0][2] * inversed(2, 0);

		if (abs(det) <= threshold)
		{
			return { false,  mat3x3<T>() };
		}

		T det_inv = 1.0 / det;

		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				inversed(row, col) *= det_inv;
			}
		}

		return { true, inversed };
	}

	mat3x3<T> transpose() const
	{
		mat3x3<T> ret;
		for (size_t row = 0; row < 3; row++)
		{
			for (size_t col = 0; col < 3; col++)
			{
				ret(row, col) = elements(col, row);
			}
		}
		return ret;
	}
};

template<class T>
class mat4x4
{
private:
	//[Row][Col] indexed
	std::array<std::array<T, 4>, 4> elements;

public:
	static mat4x4<T> zero;
	static mat4x4<T> identity;

public:
	mat4x4()
	{
		static_assert(std::is_floating_point<T>::value, "Type T of mat4x4 must be a floating-point type!");
		elements[0] = { 1.0, 0.0, 0.0, 0.0 };
		elements[1] = { 0.0, 1.0, 0.0, 0.0 };
		elements[2] = { 0.0, 0.0, 1.0, 0.0 };
		elements[3] = { 0.0, 0.0, 0.0, 1.0 };
	}

	mat4x4(T* elements, bool is_input_row_major = true/*or column major?*/)
	{
		if (is_input_row_major)
		{
			this->elements[0] = { elements[0],  elements[1],  elements[2],  elements[3]  };
			this->elements[1] = { elements[4],  elements[5],  elements[6],  elements[7]  };
			this->elements[2] = { elements[8],  elements[9],  elements[10], elements[11] };
			this->elements[3] = { elements[12], elements[13], elements[14], elements[15] };
		}
		else
		{
			this->elements[0] = { elements[0], elements[4], elements[8],  elements[12] };
			this->elements[1] = { elements[1], elements[5], elements[9],  elements[13] };
			this->elements[2] = { elements[2], elements[6], elements[10], elements[14] };
			this->elements[3] = { elements[3], elements[7], elements[11], elements[15] };
		}
	}

	mat4x4(T e00, T e01, T e02, T e03, T e10, T e11, T e12, T e13, T e20, T e21, T e22, T e23, T e30, T e31, T e32, T e33)
	{
		elements[0] = { e00, e01, e02, e03 };
		elements[1] = { e10, e11, e12, e13 };
		elements[2] = { e20, e21, e22, e23 };
		elements[3] = { e30, e31, e32, e33 };
	}

	mat4x4(std::array<T, 4> subs0, std::array<T, 4> subs1, std::array<T, 4> subs2, std::array<T, 4> subs3,
		bool is_input_row_major = true/*or column major?*/)
	{
		if (is_input_row_major)
		{
			elements[0] = subs0;
			elements[1] = subs1;
			elements[2] = subs2;
			elements[3] = subs3;
		}
		else
		{
			elements[0] = { subs0[0], subs1[0], subs2[0], subs3[0] };
			elements[1] = { subs0[1], subs1[1], subs2[1], subs3[1] };
			elements[2] = { subs0[2], subs1[2], subs2[2], subs3[2] };
			elements[3] = { subs0[3], subs1[3], subs2[3], subs3[3] };
		}
	}

public:
	std::unique_ptr<T[]> copy(bool is_output_row_major = true/*or column major?*/) const
	{
		std::unique_ptr<T[]> ptr = std::make_unique<T[]>(16);
		if (is_output_row_major)
		{
			ptr[0]  = elements[0][0]; ptr[1]  = elements[0][1]; ptr[2]  = elements[0][2]; ptr[3]  = elements[0][3];
			ptr[4]  = elements[1][0]; ptr[5]  = elements[1][1]; ptr[6]  = elements[1][2]; ptr[7]  = elements[1][3];
			ptr[8]  = elements[2][0]; ptr[9]  = elements[2][1]; ptr[10] = elements[2][2]; ptr[11] = elements[2][3];
			ptr[12] = elements[3][0]; ptr[13] = elements[3][1]; ptr[14] = elements[3][2]; ptr[15] = elements[3][3];
		}
		else
		{
			ptr[0] = elements[0][0]; ptr[4] = elements[0][1]; ptr[8]  = elements[0][2]; ptr[12] = elements[0][3];
			ptr[1] = elements[1][0]; ptr[5] = elements[1][1]; ptr[9]  = elements[1][2]; ptr[13] = elements[1][3];
			ptr[2] = elements[2][0]; ptr[6] = elements[2][1]; ptr[10] = elements[2][2]; ptr[14] = elements[2][3];
			ptr[3] = elements[3][0]; ptr[7] = elements[3][1]; ptr[11] = elements[3][2]; ptr[15] = elements[3][3];
		}
		return ptr;
	}

	T& operator()(size_t row_index, size_t col_index)
	{
		if (row_index >= 4 || col_index >= 4 || row_index < 0 || col_index < 0) { throw std::out_of_range("mat4x4 index out of range!"); }
		return elements[row_index][col_index];
	}

	T operator()(size_t row_index, size_t col_index) const
	{
		if (row_index >= 4 || col_index >= 4 || row_index < 0 || col_index < 0) { throw std::out_of_range("mat4x4 index out of range!"); }
		return elements[row_index][col_index];
	}

	std::array<T, 4> row(size_t index) const
	{
		if (index >= 4 || index < 0) { throw std::out_of_range("mat4x4 index out of range!"); }
		return elements[index];
	}

	std::array<T, 4> col(size_t index) const
	{
		if (index >= 4 || index < 0) { throw std::out_of_range("mat4x4 index out of range!"); }
		return { elements[0][index], elements[1][index], elements[2][index], elements[3][index] };
	}

	void set_row(size_t index, std::array<T, 4> rows)
	{
		if (index >= 4 || index < 0) { throw std::out_of_range("mat4x4 index out of range!"); }
		elements[index] = rows;
	}

	void set_col(size_t index, std::array<T, 4> cols)
	{
		if (index >= 4 || index < 0) { throw std::out_of_range("mat4x4 index out of range!"); }
		elements[0][index] = rows[0];
		elements[1][index] = rows[1];
		elements[2][index] = rows[2];
		elements[3][index] = rows[3];
	}

	T det() const
	{
		return
			elements[0][0] * sub_mat_det(1, 2, 3, 1, 2, 3) -
			elements[0][1] * sub_mat_det(1, 2, 3, 0, 2, 3) +
			elements[0][2] * sub_mat_det(1, 2, 3, 0, 1, 3) -
			elements[0][3] * sub_mat_det(1, 2, 3, 0, 1, 2);
	}

	std::tuple<bool, mat4x4<T>> inverse(T threshold = FLOATING_POINT_THRESHOLD) const
	{
		T e00 = elements[0][0], e01 = elements[0][1], e02 = elements[0][2], e03 = elements[0][3];
		T e10 = elements[1][0], e11 = elements[1][1], e12 = elements[1][2], e13 = elements[1][3];
		T e20 = elements[2][0], e21 = elements[2][1], e22 = elements[2][2], e23 = elements[2][3];
		T e30 = elements[3][0], e31 = elements[3][1], e32 = elements[3][2], e33 = elements[3][3];
		
		T v0 = e20 * e31 - e21 * e30;
		T v1 = e20 * e32 - e22 * e30;
		T v2 = e20 * e33 - e23 * e30;
		T v3 = e21 * e32 - e22 * e31;
		T v4 = e21 * e33 - e23 * e31;
		T v5 = e22 * e33 - e23 * e32;
		
		T t00 = +(v5 * e11 - v4 * e12 + v3 * e13);
		T t10 = -(v5 * e10 - v2 * e12 + v1 * e13);
		T t20 = +(v4 * e10 - v2 * e11 + v0 * e13);
		T t30 = -(v3 * e10 - v1 * e11 + v0 * e12);
		
		T det = t00 * e00 + t10 * e01 + t20 * e02 + t30 * e03;

		if (abs(det) <= threshold)
		{
			return { false, mat4x4<T>() };
		}

		T det_inv = 1.0 / det;

		T d00 = t00 * det_inv;
		T d10 = t10 * det_inv;
		T d20 = t20 * det_inv;
		T d30 = t30 * det_inv;

		T d01 = -(v5 * e01 - v4 * e02 + v3 * e03) * det_inv;
		T d11 = +(v5 * e00 - v2 * e02 + v1 * e03) * det_inv;
		T d21 = -(v4 * e00 - v2 * e01 + v0 * e03) * det_inv;
		T d31 = +(v3 * e00 - v1 * e01 + v0 * e02) * det_inv;

		v0 = e10 * e31 - e11 * e30;
		v1 = e10 * e32 - e12 * e30;
		v2 = e10 * e33 - e13 * e30;
		v3 = e11 * e32 - e12 * e31;
		v4 = e11 * e33 - e13 * e31;
		v5 = e12 * e33 - e13 * e32;

		T d02 = +(v5 * e01 - v4 * e02 + v3 * e03) * det_inv;
		T d12 = -(v5 * e00 - v2 * e02 + v1 * e03) * det_inv;
		T d22 = +(v4 * e00 - v2 * e01 + v0 * e03) * det_inv;
		T d32 = -(v3 * e00 - v1 * e01 + v0 * e02) * det_inv;

		v0 = e21 * e10 - e20 * e11;
		v1 = e22 * e10 - e20 * e12;
		v2 = e23 * e10 - e20 * e13;
		v3 = e22 * e11 - e21 * e12;
		v4 = e23 * e11 - e21 * e13;
		v5 = e23 * e12 - e22 * e13;

		T d03 = -(v5 * e01 - v4 * e02 + v3 * e03) * det_inv;
		T d13 = +(v5 * e00 - v2 * e02 + v1 * e03) * det_inv;
		T d23 = -(v4 * e00 - v2 * e01 + v0 * e03) * det_inv;
		T d33 = +(v3 * e00 - v1 * e01 + v0 * e02) * det_inv;

		mat4x4<T> inversed(
			d00, d01, d02, d03,
			d10, d11, d12, d13,
			d20, d21, d22, d23,
			d30, d31, d32, d33
		);

		return { true, inversed };
	}

	mat4x4<T> transpose() const
	{
		mat4x4<T> ret;
		for (size_t row = 0; row < 4; row++)
		{
			for (size_t col = 0; col < 4; col++)
			{
				ret(row, col) = elements(col, row);
			}
		}
		return ret;
	}

private:
	T sub_mat_det(size_t row0, const size_t row1, const size_t row2, size_t col0, const size_t col1, const size_t col2) const
	{
		return
			elements[row0][col0] * (elements[row1][col1] * elements[row2][col2] - elements[row2][col1] * elements[row1][col2]) -
			elements[row0][col1] * (elements[row1][col0] * elements[row2][col2] - elements[row2][col0] * elements[row1][col2]) +
			elements[row0][col2] * (elements[row1][col0] * elements[row2][col1] - elements[row2][col0] * elements[row1][col1]);
	}

};

template<class T>
mat3x3<T> mat3x3<T>::zero = mat3x3<T>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

template<class T>
mat3x3<T> mat3x3<T>::identity = mat3x3<T>(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

template<class T>
mat4x4<T> mat4x4<T>::zero = mat4x4<T>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

template<class T>
mat4x4<T> mat4x4<T>::identity = mat4x4<T>(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);

template<class T>
std::unique_ptr<T[]> copy(const mat3x3<T>& mat, bool is_output_row_major = true)
{
	return mat.copy(is_output_row_major);
}

template<class T>
std::unique_ptr<T[]> copy(const mat4x4<T>& mat, bool is_output_row_major = true)
{
	return mat.copy(is_output_row_major);
}

template<class T>
T det(const mat3x3<T>& mat)
{
	return mat.det();
}

template<class T>
T det(const mat4x4<T>& mat)
{
	return mat.det();
}

template<class T>
std::tuple<bool, mat3x3<T>> inverse(const mat3x3<T>& mat, T threshold = FLOATING_POINT_THRESHOLD)
{
	return mat.inverse(threshold);
}

template<class T>
std::tuple<bool, mat4x4<T>> inverse(const mat3x3<T>& mat, T threshold = FLOATING_POINT_THRESHOLD)
{
	return mat.inverse(threshold);
}

template<class T>
mat3x3<T> transpose(const mat3x3<T>& mat)
{
	return mat.transpose();
}

template<class T>
mat4x4<T> transpose(const mat4x4<T>& mat)
{
	return mat.transpose();
}

template<class T>
inline bool operator==(const mat3x3<T>& mat1, const mat3x3<T>& mat2)
{
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			if (!equal(mat1(row, col), mat2(row, col)))
			{
				return false;
			}
		}
	}
	return true;
}

template<class T>
inline bool operator==(const mat4x4<T>& mat1, const mat4x4<T>& mat2)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			if (!equal(mat1(row, col), mat2(row, col)))
			{
				return false;
			}
		}
	}
	return true;
}

template<class T>
inline bool operator!=(const mat3x3<T>& mat1, const mat3x3<T>& mat2)
{
	return !(mat1 == mat2);
}

template<class T>
inline bool operator!=(const mat4x4<T>& mat1, const mat4x4<T>& mat2)
{
	return !(mat1 == mat2);
}

template<class T>
inline mat3x3<T> operator-(const mat3x3<T>& mat)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			ret(row, col) = -mat(row, col);
		}
	}
	return ret;
}

template<class T>
inline mat4x4<T> operator-(const mat4x4<T>& mat)
{
	mat4x4<T> ret;
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			ret(row, col) = -mat(row, col);
		}
	}
	return ret;
}

template<class T>
inline mat3x3<T> operator+(const mat3x3<T>& mat1, const mat3x3<T>& mat2)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			ret(row, col) = mat1(row, col) + mat2(row, col);
		}
	}
	return ret;
}

template<class T>
inline mat4x4<T> operator+(const mat4x4<T>& mat1, const mat4x4<T>& mat2)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			ret(row, col) = mat1(row, col) + mat2(row, col);
		}
	}
	return ret;
}

template<class T>
inline mat3x3<T> operator+(const mat3x3<T>& mat, T t)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			ret(row, col) = mat(row, col) + t;
		}
	}
	return ret;
}

template<class T>
inline mat4x4<T> operator+(const mat4x4<T>& mat, T t)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			ret(row, col) = mat(row, col) + t;
		}
	}
	return ret;
}

template<class T>
inline mat3x3<T> operator+(T t, const mat3x3<T>& mat)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			ret(row, col) = mat(row, col) + t;
		}
	}
	return ret;
}

template<class T>
inline mat4x4<T> operator+(T t, const mat4x4<T>& mat)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			ret(row, col) = mat(row, col) + t;
		}
	}
	return ret;
}

template<class T>
inline void operator+=(mat3x3<T>& mat1, const mat3x3<T>& mat2)
{
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			mat1(row, col) += mat2(row, col);
		}
	}
}

template<class T>
inline void operator+=(mat4x4<T>& mat1, const mat4x4<T>& mat2)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			mat1(row, col) += mat2(row, col);
		}
	}
}

template<class T>
inline void operator+=(mat3x3<T>& mat, T t)
{
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			mat(row, col) += t;
		}
	}
}

template<class T>
inline void operator+=(mat4x4<T>& mat, T t)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			mat(row, col) += t;
		}
	}
}

template<class T>
inline mat3x3<T> operator-(const mat3x3<T>& mat1, const mat3x3<T>& mat2)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			ret(row, col) = mat1(row, col) - mat2(row, col);
		}
	}
	return ret;
}

template<class T>
inline mat4x4<T> operator-(const mat4x4<T>& mat1, const mat4x4<T>& mat2)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			ret(row, col) = mat1(row, col) - mat2(row, col);
		}
	}
	return ret;
}


template<class T>
inline mat3x3<T> operator-(const mat3x3<T>& mat, T t)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			ret(row, col) = mat(row, col) - t;
		}
	}
	return ret;
}

template<class T>
inline mat4x4<T> operator-(const mat4x4<T>& mat, T t)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			ret(row, col) = mat(row, col) - t;
		}
	}
	return ret;
}

template<class T>
inline mat3x3<T> operator-(T t, const mat3x3<T>& mat)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			ret(row, col) = mat(row, col) - t;
		}
	}
	return ret;
}

template<class T>
inline mat4x4<T> operator-(T t, const mat4x4<T>& mat)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			ret(row, col) = mat(row, col) - t;
		}
	}
	return ret;
}

template<class T>
inline void operator-=(mat3x3<T>& mat1, const mat3x3<T>& mat2)
{
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			mat1(row, col) -= mat2(row, col);
		}
	}
}

template<class T>
inline void operator-=(mat4x4<T>& mat1, const mat4x4<T>& mat2)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			mat1(row, col) -= mat2(row, col);
		}
	}
}

template<class T>
inline void operator-=(mat3x3<T>& mat, T t)
{
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			mat(row, col) -= t;
		}
	}
}

template<class T>
inline void operator-=(mat4x4<T>& mat, T t)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			mat(row, col) -= t;
		}
	}
}

template<class T>
inline mat3x3<T> operator*(const mat3x3<T>& mat1, const mat3x3<T>& mat2)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			ret(row, col) = mat1(row, 0) * mat2(0, col) + mat1(row, 1) * mat2(1, col) + mat1(row, 2) * mat2(2, col);
		}
	}
	return ret;
}

template<class T>
inline mat4x4<T> operator*(const mat4x4<T>& mat1, const mat4x4<T>& mat2)
{
	mat4x4<T> ret;
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			ret(row, col) = mat1(row, 0) * mat2(0, col) + mat1(row, 1) * mat2(1, col) + mat1(row, 2) * mat2(2, col) + mat1(row, 3) * mat2(3, col);
		}
	}
	return ret;
}

template<class T>
inline mat3x3<T> operator*(const mat3x3<T>& mat, T t)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			ret(row, col) = mat(row, col) * t;
		}
	}
	return ret;
}

template<class T>
inline mat4x4<T> operator*(const mat4x4<T>& mat, T t)
{
	mat4x4<T> ret;
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			ret(row, col) = mat(row, col) * t;
		}
	}
	return ret;
}

template<class T>
inline mat3x3<T> operator*(T t, const mat3x3<T>& mat)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			ret(row, col) = mat(row, col) * t;
		}
	}
	return ret;
}

template<class T>
inline mat4x4<T> operator*(T t, const mat4x4<T>& mat)
{
	mat4x4<T> ret;
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			ret(row, col) = mat(row, col) * t;
		}
	}
	return ret;
}

template<class T>
inline void operator*=(mat3x3<T>& mat1, const mat3x3<T>& mat2)
{
	mat3x3<T> ret;
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			ret(row, col) = mat1(row, 0) * mat2(0, col) + mat1(row, 1) * mat2(1, col) + mat1(row, 2) * mat2(2, col);
		}
	}
	mat1 = ret;
}

template<class T>
inline void operator*=(mat4x4<T>& mat1, const mat4x4<T>& mat2)
{
	mat4x4<T> ret;
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			ret(row, col) = mat1(row, 0) * mat2(0, col) + mat1(row, 1) * mat2(1, col) + mat1(row, 2) * mat2(2, col) + mat1(row, 3) * mat2(3, col);
		}
	}
	mat1 = ret;
}

template<class T>
inline void operator*=(mat3x3<T>& mat, T t)
{
	for (size_t row = 0; row < 3; row++)
	{
		for (size_t col = 0; col < 3; col++)
		{
			mat(row, col) *= t;
		}
	}
}

template<class T>
inline void operator*=(mat4x4<T>& mat, T t)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			mat(row, col) *= t;
		}
	}
}

template<class T>
inline mat4x4<T> translate(T x, T y, T z, bool is_row_vector = true)
{
	mat4x4<T> mat = mat4x4<T>::identity;
	if (is_row_vector)
	{
		mat(3, 0) = x; mat(3, 1) = y; mat(3, 2) = z;
	}
	else
	{
		mat(0, 3) = x; mat(1, 3) = y; mat(2, 3) = z;
	}
	return mat;
}

template<class T>
inline mat4x4<T> translate(vec3<T> vec, bool is_row_vector = true)
{
	mat4x4<T> mat = mat4x4<T>::identity;
	if (is_row_vector)
	{
		mat(3, 0) = vec.x; mat(3, 1) = vec.y; mat(3, 2) = vec.z;
	}
	else
	{
		mat(0, 3) = vec.x; mat(1, 3) = vec.y; mat(2, 3) = vec.z;
	}
	return mat;
}

template<class T>
inline mat4x4<T> scale(T x, T y, T z)
{
	mat4x4<T> mat = mat4x4<T>::identity;
	mat(0, 0) = x; mat(1, 1) = y; mat(2, 2) = z;
	return mat;
}

template<class T>
inline mat4x4<T> scale(vec3<T> vec)
{
	mat4x4<T> mat = mat4x4<T>::identity;
	mat(0, 0) = vec.x; mat(1, 1) = vec.y; mat(2, 2) = vec.z;
	return mat;
}

template<class T>
inline mat4x4<T> rotate(T radian, vec3<T> axis, bool is_row_vector = true)
{
	T half_radian = radian * 0.5;
	T half_sin = std::sin(half_radian);
	T half_cos = std::cos(half_radian);

	axis.normalize();

	T x = axis.x * half_sin;
	T y = axis.y * half_sin;
	T z = axis.z * half_sin;
	T w = half_cos;

	T x2 = x * x; T y2 = y * y; T z2 = z * z;
	T xy = x * y; T xz = x * z; T yz = y * z;
	T xw = x * w; T yw = y * w; T zw = z * w;

	mat4x4<T> mat = mat4x4<T>::identity;
	if (is_row_vector)
	{
		mat(0, 0) = 1 - 2 * (y2 + z2);
		mat(0, 1) = 2 * (xy - zw);
		mat(0, 2) = 2 * (xz + yw);
		mat(0, 3) = 0.0f;

		mat(1, 0) = 2 * (xy + zw);
		mat(1, 1) = 1 - 2 * (x2 + z2);
		mat(1, 2) = 2 * (yz - xw);
		mat(1, 3) = 0.0f;

		mat(2, 0) = 2 * (xz - yw);
		mat(2, 1) = 2 * (yz + xw);
		mat(2, 2) = 1 - 2 * (x2 + y2);
		mat(2, 3) = 0.0f;

		mat(3, 0) = 0.0f;
		mat(3, 1) = 0.0f;
		mat(3, 2) = 0.0f;
		mat(3, 3) = 1.0f;
	}
	else
	{
		mat(0, 0) = 1 - 2 * (y2 + z2);
		mat(1, 0) = 2 * (xy - zw);
		mat(2, 0) = 2 * (xz + yw);
		mat(3, 0) = 0.0f;

		mat(0, 1) = 2 * (xy + zw);
		mat(1, 1) = 1 - 2 * (x2 + z2);
		mat(2, 1) = 2 * (yz - xw);
		mat(3, 1) = 0.0f;

		mat(0, 2) = 2 * (xz - yw);
		mat(1, 2) = 2 * (yz + xw);
		mat(2, 2) = 1 - 2 * (x2 + y2);
		mat(3, 2) = 0.0f;

		mat(0, 3) = 0.0f;
		mat(1, 3) = 0.0f;
		mat(2, 3) = 0.0f;
		mat(3, 3) = 1.0f;
	}
	return mat;
}

template<class T>
inline vec4<T> transform(vec4<T> vec, const mat4x4<T> mat, bool is_row_vector = true)
{
	vec4<T> ret;
	if (is_row_vector)
	{
		ret.x = vec.x * mat(0, 0) + vec.y * mat(1, 0) + vec.z * mat(2, 0) + vec.w(3, 0);
		ret.y = vec.x * mat(0, 1) + vec.y * mat(1, 1) + vec.z * mat(2, 1) + vec.w(3, 1);
		ret.z = vec.x * mat(0, 2) + vec.y * mat(1, 2) + vec.z * mat(2, 2) + vec.w(3, 2);
		ret.w = vec.x * mat(0, 3) + vec.y * mat(1, 3) + vec.z * mat(2, 3) + vec.w(3, 3);
	}
	else
	{
		ret.x = mat(0, 0) * vec.x + mat(0, 1)*vec.y + mat(0, 2)*vec.z + mat(0, 3)*vec.w;
		ret.y = mat(1, 0) * vec.x + mat(1, 1)*vec.y + mat(1, 2)*vec.z + mat(1, 3)*vec.w;
		ret.z = mat(2, 0) * vec.x + mat(2, 1)*vec.y + mat(2, 2)*vec.z + mat(2, 3)*vec.w;
		ret.w = mat(3, 0) * vec.x + mat(3, 1)*vec.y + mat(3, 2)*vec.z + mat(3, 3)*vec.w;
	}
	return ret;
}

#endif // !__MATRIX__
