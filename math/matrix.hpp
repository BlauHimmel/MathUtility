#pragma once

#ifndef __MATRIX__
#define __MATRIX__

#include "vector.hpp"

template<class T>
class matrix3x3;

template<class T>
class matrix4x4;

using matrix3x3f = matrix3x3<float>;
using matrix3x3d = matrix3x3<double>;
using matrix3x3ld = matrix3x3<long double>;

using matrix4x4f = matrix4x4<float>;
using matrix4x4d = matrix4x4<double>;
using matrix4x4ld = matrix4x4<long double>;

template<class T>
class matrix3x3
{
private:
	//[Row][Col] indexed
	std::array<std::array<T, 3>, 3> elements;

public:
	matrix3x3()
	{
		static_assert(std::is_floating_point<T>::value, "Type T of matrix3x3 must be a floating-point type!");
		elements[0] = { 1.0, 0.0, 0.0 };
		elements[1] = { 0.0, 1.0, 0.0 };
		elements[2] = { 0.0, 0.0, 1.0 };
	}

	matrix3x3(T* elements, bool is_input_row_major = true)
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

	matrix3x3(T e00, T e01, T e02, T e10, T e11, T e12, T e20, T e21, T e22)
	{
		elements[0] = { e00, e01, e02 };
		elements[1] = { e10, e11, e12 };
		elements[2] = { e20, e21, e22 };
	}

	matrix3x3(std::array<T, 3> subs0, std::array<T, 3> subs1, std::array<T, 3> subs2, bool is_input_row_major = true)
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
	std::unique_ptr<T[]> copy(bool is_output_row_major = true) const
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
		if (row_index >= 3 || col_index >= 3 || row_index < 0 || col_index < 0) { throw std::out_of_range("matrix3x3 index out of range!"); }
		return elements[row_index][col_index];
	}

	std::array<T, 3> row(size_t index) const
	{
		if (index >= 3 || index < 0) { throw std::out_of_range("matrix3x3 index out of range!"); }
		return elements[index];
	}

	std::array<T, 3> col(size_t index) const
	{
		if (index >= 3 || index < 0) { throw std::out_of_range("matrix3x3 index out of range!"); }
		return { elements[0][index], elements[1][index], elements[2][index] };
	}

	void set_row(size_t index, std::array<T, 3> rows)
	{
		if (index >= 3 || index < 0) { throw std::out_of_range("matrix3x3 index out of range!"); }
		elements[index] = rows;
	}

	void set_col(size_t index, std::array<T, 3> cols)
	{
		if (index >= 3 || index < 0) { throw std::out_of_range("matrix3x3 index out of range!"); }
		elements[0][index] = rows[0];
		elements[1][index] = rows[1];
		elements[2][index] = rows[2];
	}
};

template<class T>
class matrix4x4
{
private:
	//[Row][Col] indexed
	std::array<std::array<T, 4>, 4> elements;

public:
	matrix4x4()
	{
		static_assert(std::is_floating_point<T>::value, "Type T of matrix4x4 must be a floating-point type!");
		elements[0] = { 1.0, 0.0, 0.0, 0.0 };
		elements[1] = { 0.0, 1.0, 0.0, 0.0 };
		elements[2] = { 0.0, 0.0, 1.0, 0.0 };
		elements[3] = { 0.0, 0.0, 0.0, 1.0 };
	}

	matrix4x4(T* elements, bool is_input_row_major = true)
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

	matrix4x4(T e00, T e01, T e02, T e03, T e10, T e11, T e12, T e13, T e20, T e21, T e22, T e23, T e30, T e31, T e32, T e33)
	{
		elements[0] = { e00, e01, e02, e03 };
		elements[1] = { e10, e11, e12, e13 };
		elements[2] = { e20, e21, e22, e23 };
		elements[3] = { e30, e31, e32, e33 };
	}

	matrix4x4(std::array<T, 4> subs0, std::array<T, 4> subs1, std::array<T, 4> subs2, std::array<T, 4> subs3, bool is_input_row_major = true)
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
	std::unique_ptr<T[]> copy(bool is_output_row_major = true) const
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
		if (row_index >= 4 || col_index >= 4 || row_index < 0 || col_index < 0) { throw std::out_of_range("matrix4x4 index out of range!"); }
		return elements[row_index][col_index];
	}

	std::array<T, 4> row(size_t index) const
	{
		if (index >= 4 || index < 0) { throw std::out_of_range("matrix4x4 index out of range!"); }
		return elements[index];
	}

	std::array<T, 4> col(size_t index) const
	{
		if (index >= 4 || index < 0) { throw std::out_of_range("matrix4x4 index out of range!"); }
		return { elements[0][index], elements[1][index], elements[2][index], elements[3][index] };
	}

	void set_row(size_t index, std::array<T, 4> rows)
	{
		if (index >= 4 || index < 0) { throw std::out_of_range("matrix4x4 index out of range!"); }
		elements[index] = rows;
	}

	void set_col(size_t index, std::array<T, 4> cols)
	{
		if (index >= 4 || index < 0) { throw std::out_of_range("matrix4x4 index out of range!"); }
		elements[0][index] = rows[0];
		elements[1][index] = rows[1];
		elements[2][index] = rows[2];
		elements[3][index] = rows[3];
	}
};

#endif // !__MATRIX__
