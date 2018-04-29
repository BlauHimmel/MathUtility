#pragma once

#ifndef __VECTOR__
#define __VECTOR__

#include <type_traits>
#include <stdexcept>
#include <exception>
#include <cmath>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>

template<class T>
class vec2;

template<class T>
class vec3;

template<class T>
class vec4;

using vec2f = vec2<float>;
using vec2d = vec2<double>;
using vec2ld = vec2<long double>;

using vec3f = vec3<float>;
using vec3d = vec3<double>;
using vec3ld = vec3<long double>;

using vec4f = vec4<float>;
using vec4d = vec4<double>;
using vec4ld = vec4<long double>;

#define FLOATING_POINT_EQUAL_THRESHOLD 0.000001

template<class T>
class vec2
{
public:
	T x, y;
	static vec2<T> zero;
	static vec2<T> one;

public:
	vec2()
	{
		static_assert(std::is_floating_point<T>::value, "Type T of vec2 must be a floating-point type!");
		x = 0.0; y = 0.0;
	}

	explicit vec2(T value)
	{
		static_assert(std::is_floating_point<T>::value, "Type T of vec2 must be a floating-point type!");
		x = value; y = value;
	}

	vec2(T x, T y)
	{
		static_assert(std::is_floating_point<T>::value, "Type T of vec2 must be a floating-point type!");
		this->x = x; this->y = y;
	}

public:
	T& operator[](size_t index)
	{
		if (index >= 2) { throw std::out_of_range("vec2 index out of range!"); }
		return *(&x + index);
	}

public:
	T* ptr()
	{
		return &x;
	}

	T length() const
	{
		return sqrt(x * x + y * y);
	}

	T sqr_length() const
	{
		return x * x + y * y;
	}

	vec2<T> normal() const
	{
		T length = this->length();
		return vec2<T>(x / length, y / length);
	}

	void normalize()
	{
		T length = this->length();
		this->x /= length;
		this->y /= length;
	}

	bool is_normal() const
	{
		return equal(this->length(), static_cast<T>(1.0));
	}

	T dot(vec2<T> vec) const
	{
		return vec.x * this->x + vec.y * this->y;
	}

public:
	std::string to_string() const
	{
		char buffer[256];
		sprintf_s(buffer, 256, "vec2(%.2lf, %.2lf)", x, y);
		return std::string(buffer);
	}

	template<class T>
	friend std::ostream& operator<<(std::ostream& out, vec2<T>& vec);
	
	template<class T>
	friend std::istream& operator>>(std::istream& in, vec2<T>& vec);
};

template<class T>
class vec3
{
public:
	T x, y, z;
	static vec3<T> zero;
	static vec3<T> one;

public:
	vec3()
	{
		static_assert(std::is_floating_point<T>::value, "Type T of vec3 must be a floating-point type!");
		x = 0.0; y = 0.0; z = 0.0;
	}

	explicit vec3(T value)
	{
		static_assert(std::is_floating_point<T>::value, "Type T of vec3 must be a floating-point type!");
		x = value; y = value; z = value;
	}

	vec3(T x, T y, T z)
	{
		static_assert(std::is_floating_point<T>::value, "Type T of vec3 must be a floating-point type!");
		this->x = x; this->y = y; this->z = z;
	}

public:
	T& operator[](size_t index)
	{
		if (index >= 3) { throw std::out_of_range("vec3 index out of range!"); }
		return *(&x + index);
	}

public:
	T* ptr()
	{
		return &x;
	}

	T length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	T sqr_length() const
	{
		return x * x + y * y + z * z;
	}

	vec3<T> normal() const
	{
		T length = this->length();
		return vec3<T>(x / length, y / length, z / length);
	}

	void normalize()
	{
		T length = this->length();
		this->x /= length;
		this->y /= length;
		this->z /= length;
	}

	bool is_normal() const
	{
		return equal(this->length(), static_cast<T>(1.0));
	}

	T dot(vec3<T> vec) const
	{
		return vec.x * this->x + vec.y * this->y + vec.z * this->z;
	}

	vec3<T> cross(vec3<T> vec) const
	{
		return vec3<T>(this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x);
	}

public:
	std::string to_string() const
	{
		char buffer[256];
		sprintf_s(buffer, 256, "vec3(%.2lf, %.2lf, %.2lf)", x, y, z);
		return std::string(buffer);
	}

	template<class T>
	friend std::ostream& operator<<(std::ostream& out, vec3<T>& vec);
	
	template<class T>
	friend std::istream& operator>>(std::istream& in, vec3<T>& vec);
};

template<class T>
class vec4
{
public:
	T x, y, z, w;
	static vec4<T> zero;
	static vec4<T> one;

public:
	vec4()
	{
		static_assert(std::is_floating_point<T>::value, "Type T of vec4 must be a floating-point type!");
		x = 0.0; y = 0.0; z = 0.0; w = 0.0;
	}

	explicit vec4(T value)
	{
		static_assert(std::is_floating_point<T>::value, "Type T of vec4 must be a floating-point type!");
		x = value; y = value; z = value; w = value;
	}

	vec4(T x, T y, T z, T w)
	{
		static_assert(std::is_floating_point<T>::value, "Type T of vec4 must be a floating-point type!");
		this->x = x; this->y = y; this->z = z; this->w = w;
	}

public:
	T& operator[](size_t index)
	{
		if (index >= 4) { throw std::out_of_range("vec4 index out of range!"); }
		return *(&x + index);
	}

public:
	T* ptr()
	{
		return &x;
	}

	T length() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	T sqr_length() const
	{
		return x * x + y * y + z * z + w * w;
	}

	vec4<T> normal() const
	{
		T length = this->length();
		return vec3<T>(x / length, y / length, z / length, w / length);
	}

	void normalize()
	{
		T length = this->length();
		this->x /= length;
		this->y /= length;
		this->z /= length;
		this->w /= length;
	}

	bool is_normal() const
	{
		return equal(this->length(), static_cast<T>(1.0));
	}

	T dot(vec4<T> vec) const
	{
		return vec.x * this->x + vec.y * this->y + vec.z * this->z + vec.w * this->w;
	}

public:
	std::string to_string() const
	{
		char buffer[256];
		sprintf_s(buffer, 256, "vec4(%.2lf, %.2lf, %.2lf, %.2lf)", x, y, z, w);
		return std::string(buffer);
	}

	template<class T>
	friend std::ostream& operator<<(std::ostream& out, vec4<T>& vec);
	
	template<class T>
	friend std::istream& operator>>(std::istream& in, vec4<T>& vec);
};

template<class T>
vec2<T> vec2<T>::zero = vec2<T>(0.0, 0.0);

template<class T>
vec2<T> vec2<T>::one = vec2<T>(1.0, 1.0);

template<class T>
vec3<T> vec3<T>::zero = vec3<T>(0.0, 0.0, 0.0);

template<class T>
vec3<T> vec3<T>::one = vec3<T>(1.0, 1.0, 1.0);

template<class T>
vec4<T> vec4<T>::zero = vec4<T>(0.0, 0.0, 0.0, 0.0);

template<class T>
vec4<T> vec4<T>::one = vec4<T>(1.0, 1.0, 1.0, 1.0);

template<class T>
inline T length(vec2<T> vec)
{
	return vec.length();
}

template<class T>
inline T length(vec3<T> vec)
{
	return vec.length();
}

template<class T>
inline T length(vec4<T> vec)
{
	return vec.length();
}

template<class T>
inline T sqr_length(vec2<T> vec)
{
	return vec.sqr_length();
}

template<class T>
inline T sqr_length(vec3<T> vec)
{
	return vec.sqr_length();
}

template<class T>
inline T sqr_length(vec4<T> vec)
{
	return vec.sqr_length();
}

template<class T>
inline T normalize(vec2<T> vec)
{
	return vec.normalize();
}

template<class T>
inline T normalize(vec3<T> vec)
{
	return vec.normalize();
}

template<class T>
inline T normalize(vec4<T> vec)
{
	return vec.normalize();
}

template<class T>
inline bool is_normal(vec2<T> vec)
{
	return vec.is_normal();
}

template<class T>
inline bool is_normal(vec3<T> vec)
{
	return vec.is_normal();
}

template<class T>
inline bool is_normal(vec4<T> vec)
{
	return vec.is_normal();
}

template<class T>
inline T dot(vec2<T> vec1, vec2<T> vec2)
{
	return vec1.dot(vec2);
}

template<class T>
inline T dot(vec3<T> vec1, vec3<T> vec2)
{
	return vec1.dot(vec2);
}

template<class T>
inline T dot(vec4<T> vec1, vec4<T> vec2)
{
	return vec1.dot(vec2);
}

template<class T>
inline T cross(vec3<T> vec1, vec3<T> vec2)
{
	return vec1.cross(vec2);
}

template<class T>
inline bool operator==(vec2<T> vec1, vec2<T> vec2)
{
	return equal(vec1.x, vec2.x) && equal(vec1.y, vec2.y);
}

template<class T>
inline bool operator==(vec3<T> vec1, vec3<T> vec2)
{
	return equal(vec1.x, vec2.x) && equal(vec1.y, vec2.y) && equal(vec1.z, vec2.z);
}

template<class T>
inline bool operator==(vec4<T> vec1, vec4<T> vec2)
{
	return equal(vec1.x, vec2.x) && equal(vec1.y, vec2.y) && equal(vec1.z, vec2.z) && equal(vec1.w, vec2.w);
}

template<class T>
inline bool operator!=(vec2<T> vec1, vec2<T> vec2)
{
	return !(vec1 == vec2);
}

template<class T>
inline bool operator!=(vec3<T> vec1, vec3<T> vec2)
{
	return !(vec1 == vec2);
}

template<class T>
inline bool operator!=(vec4<T> vec1, vec4<T> vec2)
{
	return !(vec1 == vec2);
}

template<class T>
inline vec2<T> operator-(vec2<T> vec)
{
	return vec2<T>(-vec.x, -vec.y);
}

template<class T>
inline vec3<T> operator-(vec3<T> vec)
{
	return vec3<T>(-vec.x, -vec.y, -vec.z);
}

template<class T>
inline vec4<T> operator-(vec4<T> vec)
{
	return vec4<T>(-vec.x, -vec.y, -vec.z, -vec.w);
}

template<class T>
inline vec2<T> operator+(vec2<T> vec1, vec2<T> vec2)
{
	return vec2<T>(vec1.x + vec2.x, vec1.y + vec2.y);
}

template<class T>
inline vec3<T> operator+(vec3<T> vec1, vec3<T> vec2)
{
	return vec3<T>(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

template<class T>
inline vec4<T> operator+(vec4<T> vec1, vec4<T> vec2)
{
	return vec4<T>(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
}

template<class T>
inline vec2<T> operator+(vec2<T> vec, T t)
{
	return vec2<T>(vec.x + t, vec.y + t);
}

template<class T>
inline vec3<T> operator+(vec3<T> vec, T t)
{
	return vec3<T>(vec.x + t, vec.y + t, vec.z + t);
}

template<class T>
inline vec4<T> operator+(vec4<T> vec, T t)
{
	return vec4<T>(vec.x + t, vec.y + t, vec.z + t, vec.w + t);
}

template<class T>
inline vec2<T> operator+(T t, vec2<T> vec)
{
	return vec2<T>(vec.x + t, vec.y + t);
}

template<class T>
inline vec3<T> operator+(T t, vec3<T> vec)
{
	return vec3<T>(vec.x + t, vec.y + t, vec.z + t);
}

template<class T>
inline vec4<T> operator+(T t, vec4<T> vec)
{
	return vec4<T>(vec.x + t, vec.y + t, vec.z + t, vec.w + t);
}

template<class T>
inline void operator+=(vec2<T>& vec1, vec2<T> vec2)
{
	vec1.x += vec2.x; vec1.y += vec2.y;
}

template<class T>
inline void operator+=(vec3<T>& vec1, vec3<T> vec2)
{
	vec1.x += vec2.x; vec1.y += vec2.y; vec1.z += vec2.z;
}

template<class T>
inline void operator+=(vec4<T>& vec1, vec4<T> vec2)
{
	vec1.x += vec2.x; vec1.y += vec2.y; vec1.z += vec2.z; vec1.w += vec2.w;
}

template<class T>
inline vec3<T> operator+=(vec2<T>& vec, T t)
{
	vec.x += t; vec.y += t;
}

template<class T>
inline vec3<T> operator+=(vec3<T>& vec, T t)
{
	vec.x += t; vec.y += t; vec.z += t;
}

template<class T>
inline vec4<T> operator+=(vec4<T>& vec, T t)
{
	vec.x += t; vec.y += t; vec.z += t; vec.w += t;
}

template<class T>
inline vec3<T> operator+=(T t, vec2<T>& vec)
{
	vec.x += t; vec.y += t;
}

template<class T>
inline vec3<T> operator+=(T t, vec3<T>& vec)
{
	vec.x += t; vec.y += t; vec.z += t;
}

template<class T>
inline vec4<T> operator+=(T t, vec4<T>& vec)
{
	vec.x += t; vec.y += t; vec.z += t; vec.w += t;
}

template<class T>
inline vec2<T> operator-(vec2<T> vec1, vec2<T> vec2)
{
	return vec2<T>(vec1.x - vec2.x, vec1.y - vec2.y);
}

template<class T>
inline vec3<T> operator-(vec3<T> vec1, vec3<T> vec2)
{
	return vec3<T>(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

template<class T>
inline vec4<T> operator-(vec4<T> vec1, vec4<T> vec2)
{
	return vec4<T>(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
}

template<class T>
inline vec2<T> operator-(vec2<T> vec, T t)
{
	return vec2<T>(vec.x - t, vec.y - t);
}

template<class T>
inline vec3<T> operator-(vec3<T> vec, T t)
{
	return vec3<T>(vec.x - t, vec.y - t, vec.z - t);
}

template<class T>
inline vec4<T> operator-(vec4<T> vec, T t)
{
	return vec4<T>(vec.x - t, vec.y - t, vec.z - t, vec.w - t);
}

template<class T>
inline vec2<T> operator-(T t, vec2<T> vec)
{
	return vec2<T>(vec.x - t, vec.y - t);
}

template<class T>
inline vec3<T> operator-(T t, vec3<T> vec)
{
	return vec3<T>(vec.x - t, vec.y - t, vec.z - t);
}

template<class T>
inline vec4<T> operator-(T t, vec4<T> vec)
{
	return vec4<T>(vec.x - t, vec.y - t, vec.z - t, vec.w - t);
}

template<class T>
inline void operator-=(vec2<T>& vec1, vec2<T> vec2)
{
	vec1.x -= vec2.x; vec1.y -= vec2.y;
}

template<class T>
inline void operator-=(vec3<T>& vec1, vec3<T> vec2)
{
	vec1.x -= vec2.x; vec1.y -= vec2.y; vec1.z -= vec2.z;
}

template<class T>
inline void operator-=(vec4<T>& vec1, vec4<T> vec2)
{
	vec1.x -= vec2.x; vec1.y -= vec2.y; vec1.z -= vec2.z; vec1.w -= vec2.w;
}

template<class T>
inline vec3<T> operator-=(vec2<T>& vec, T t)
{
	vec.x -= t; vec.y -= t;
}

template<class T>
inline vec3<T> operator-=(vec3<T>& vec, T t)
{
	vec.x -= t; vec.y -= t; vec.z -= t;
}

template<class T>
inline vec4<T> operator-=(vec4<T>& vec, T t)
{
	vec.x -= t; vec.y -= t; vec.z -= t; vec.w -= t;
}

template<class T>
inline vec3<T> operator-=(T t, vec2<T>& vec)
{
	vec.x -= t; vec.y -= t;
}

template<class T>
inline vec3<T> operator-=(T t, vec3<T>& vec)
{
	vec.x -= t; vec.y -= t; vec.z -= t;
}

template<class T>
inline vec4<T> operator-=(T t, vec4<T>& vec)
{
	vec.x -= t; vec.y -= t; vec.z -= t; vec.w -= t;
}

template<class T>
inline vec2<T> operator*(vec2<T> vec1, vec2<T> vec2)
{
	return vec2<T>(vec1.x * vec2.x, vec1.y * vec2.y);
}

template<class T>
inline vec3<T> operator*(vec3<T> vec1, vec3<T> vec2)
{
	return vec3<T>(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}

template<class T>
inline vec4<T> operator*(vec4<T> vec1, vec4<T> vec2)
{
	return vec4<T>(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
}

template<class T>
inline vec2<T> operator*(vec2<T> vec, T t)
{
	return vec2<T>(vec.x * t, vec.y * t);
}

template<class T>
inline vec3<T> operator*(vec3<T> vec, T t)
{
	return vec3<T>(vec.x * t, vec.y * t, vec.z * t);
}

template<class T>
inline vec4<T> operator*(vec4<T> vec, T t)
{
	return vec4<T>(vec.x * t, vec.y * t, vec.z * t, vec.w * t);
}

template<class T>
inline vec2<T> operator*(T t, vec2<T> vec)
{
	return vec2<T>(vec.x * t, vec.y * t);
}

template<class T>
inline vec3<T> operator*(T t, vec3<T> vec)
{
	return vec3<T>(vec.x * t, vec.y * t, vec.z * t);
}

template<class T>
inline vec4<T> operator*(T t, vec4<T> vec)
{
	return vec4<T>(vec.x * t, vec.y * t, vec.z * t, vec.w * t);
}

template<class T>
inline void operator*=(vec2<T>& vec1, vec2<T> vec2)
{
	vec1.x *= vec2.x; vec1.y *= vec2.y;
}

template<class T>
inline void operator*=(vec3<T>& vec1, vec3<T> vec2)
{
	vec1.x *= vec2.x; vec1.y *= vec2.y; vec1.z *= vec2.z;
}

template<class T>
inline void operator*=(vec4<T>& vec1, vec4<T> vec2)
{
	vec1.x *= vec2.x; vec1.y *= vec2.y; vec1.z *= vec2.z; vec1.w *= vec2.w;
}

template<class T>
inline vec3<T> operator*=(vec2<T>& vec, T t)
{
	vec.x *= t; vec.y *= t;
}

template<class T>
inline vec3<T> operator*=(vec3<T>& vec, T t)
{
	vec.x *= t; vec.y *= t; vec.z *= t;
}

template<class T>
inline vec4<T> operator*=(vec4<T>& vec, T t)
{
	vec.x *= t; vec.y *= t; vec.z *= t; vec.w *= t;
}

template<class T>
inline vec3<T> operator*=(T t, vec2<T>& vec)
{
	vec.x *= t; vec.y *= t;
}

template<class T>
inline vec3<T> operator*=(T t, vec3<T>& vec)
{
	vec.x *= t; vec.y *= t; vec.z *= t;
}

template<class T>
inline vec4<T> operator*=(T t, vec4<T>& vec)
{
	vec.x *= t; vec.y *= t; vec.z *= t; vec.w *= t;
}

template<class T>
inline vec2<T> operator/(vec2<T> vec1, vec2<T> vec2)
{
	return vec2<T>(vec1.x / vec2.x, vec1.y / vec2.y);
}

template<class T>
inline vec3<T> operator/(vec3<T> vec1, vec3<T> vec2)
{
	return vec3<T>(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
}

template<class T>
inline vec4<T> operator/(vec4<T> vec1, vec4<T> vec2)
{
	return vec4<T>(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
}

template<class T>
inline vec2<T> operator/(vec2<T> vec, T t)
{
	return vec2<T>(vec.x / t, vec.y / t);
}

template<class T>
inline vec3<T> operator/(vec3<T> vec, T t)
{
	return vec3<T>(vec.x / t, vec.y / t, vec.z / t);
}

template<class T>
inline vec4<T> operator/(vec4<T> vec, T t)
{
	return vec4<T>(vec.x / t, vec.y / t, vec.z / t, vec.w / t);
}

template<class T>
inline vec2<T> operator/(T t, vec2<T> vec)
{
	return vec2<T>(vec.x / t, vec.y / t);
}

template<class T>
inline vec3<T> operator/(T t, vec3<T> vec)
{
	return vec3<T>(vec.x / t, vec.y / t, vec.z / t);
}

template<class T>
inline vec4<T> operator/(T t, vec4<T> vec)
{
	return vec4<T>(vec.x / t, vec.y / t, vec.z / t, vec.w / t);
}

template<class T>
inline void operator/=(vec2<T>& vec1, vec2<T> vec2)
{
	vec1.x /= vec2.x; vec1.y /= vec2.y;
}

template<class T>
inline void operator/=(vec3<T>& vec1, vec3<T> vec2)
{
	vec1.x /= vec2.x; vec1.y /= vec2.y; vec1.z /= vec2.z;
}

template<class T>
inline void operator/=(vec4<T>& vec1, vec4<T> vec2)
{
	vec1.x /= vec2.x; vec1.y /= vec2.y; vec1.z /= vec2.z; vec1.w /= vec2.w;
}

template<class T>
inline vec3<T> operator/=(vec2<T>& vec, T t)
{
	vec.x /= t; vec.y /= t;
}

template<class T>
inline vec3<T> operator/=(vec3<T>& vec, T t)
{
	vec.x /= t; vec.y /= t; vec.z /= t;
}

template<class T>
inline vec4<T> operator/=(vec4<T>& vec, T t)
{
	vec.x /= t; vec.y /= t; vec.z /= t; vec.w /= t;
}

template<class T>
inline vec3<T> operator/=(T t, vec2<T>& vec)
{
	vec.x /= t; vec.y /= t;
}

template<class T>
inline vec3<T> operator/=(T t, vec3<T>& vec)
{
	vec.x /= t; vec.y /= t; vec.z /= t;
}

template<class T>
inline vec4<T> operator/=(T t, vec4<T>& vec)
{
	vec.x /= t; vec.y /= t; vec.z /= t; vec.w /= t;
}

template<class T>
inline T max(T t1, T t2)
{
	return t1 >= t2 ? t1 : t2;
}

template<class T>
inline vec2<T> max(vec2<T> vec1, vec2<T> vec2)
{
	return vec2<T>(max(vec1.x, vec2.x), max(vec1.y, vec2.y));
}

template<class T>
inline vec3<T> max(vec3<T> vec1, vec3<T> vec2)
{
	return vec3<T>(max(vec1.x, vec2.x), max(vec1.y, vec2.y), max(vec1.z, vec2.z));
}

template<class T>
inline vec4<T> max(vec4<T> vec1, vec4<T> vec2)
{
	return vec4<T>(max(vec1.x, vec2.x), max(vec1.y, vec2.y), max(vec1.z, vec2.z), max(vec1.w, vec2.w));
}

template<class T>
inline T min(T t1, T t2)
{
	return t1 <= t2 ? t1 : t2;
}

template<class T>
inline vec2<T> min(vec2<T> vec1, vec2<T> vec2)
{
	return vec2<T>(min(vec1.x, vec2.x), min(vec1.y, vec2.y));
}

template<class T>
inline vec3<T> min(vec3<T> vec1, vec3<T> vec2)
{
	return vec3<T>(min(vec1.x, vec2.x), min(vec1.y, vec2.y), min(vec1.z, vec2.z));
}

template<class T>
inline vec4<T> min(vec4<T> vec1, vec4<T> vec2)
{
	return vec4<T>(min(vec1.x, vec2.x), min(vec1.y, vec2.y), min(vec1.z, vec2.z), min(vec1.w, vec2.w));
}

template<class T>
inline T abs(T t)
{
	return t >= 0 ? t : -t;
}

template<class T>
inline vec2<T> abs(vec2<T> vec)
{
	return vec2<T>(abs(vec.x), abs(vec.y));
}

template<class T>
inline vec3<T> abs(vec3<T> vec)
{
	return vec3<T>(abs(vec.x), abs(vec.y), abs(vec.z));
}

template<class T>
inline vec4<T> abs(vec4<T> vec)
{
	return vec4<T>(abs(vec.x), abs(vec.y), abs(vec.z), abs(vec.w));
}

template<class T>
inline T lerp(T a, T b, T t)
{
	return a + t * (b - a);
}

template<class T>
inline vec2<T> lerp(vec2<T> vec1, vec2<T> vec2, T t)
{
	return vec2<T>(lerp(vec1.x, vec2.x, t), lerp(vec1.y, vec2.y, t));
}

template<class T>
inline vec3<T> lerp(vec3<T> vec1, vec3<T> vec2, T t)
{
	return vec3<T>(lerp(vec1.x, vec2.x, t), lerp(vec1.y, vec2.y, t), lerp(vec1.z, vec2.z, t));
}

template<class T>
inline vec4<T> lerp(vec4<T> vec1, vec4<T> vec2, T t)
{
	return vec4<T>(lerp(vec1.x, vec2.x, t), lerp(vec1.y, vec2.y, t), lerp(vec1.z, vec2.z, t), lerp(vec1.w, vec2.w, t));
}

template<class T>
inline T clamp(T t, T min, T max)
{
	return t < min ? min : (t > max ? max : t);
}

template<class T>
inline vec2<T> clamp(vec2<T> vec, T min, T max)
{
	return vec2<T>(clamp(vec.x, min, max), clamp(vec.y, min, max));
}

template<class T>
inline vec3<T> clamp(vec3<T> vec, T min, T max)
{
	return vec3<T>(clamp(vec.x, min, max), clamp(vec.y, min, max), clamp(vec.z, min, max));
}

template<class T>
inline vec4<T> clamp(vec4<T> vec, T min, T max)
{
	return vec4<T>(clamp(vec.x, min, max), clamp(vec.y, min, max), clamp(vec.z, min, max), clamp(vec.w, min, max));
}

template<class T>
inline T floor(T t)
{
	return std::floor(t);
}

template<class T>
inline vec2<T> floor(vec2<T> vec)
{
	return vec2<T>(floor(vec.x), floor(vec.y));
}

template<class T>
inline vec3<T> floor(vec3<T> vec)
{
	return vec3<T>(floor(vec.x), floor(vec.y), floor(vec.z));
}

template<class T>
inline vec4<T> floor(vec4<T> vec)
{
	return vec4<T>(floor(vec.x), floor(vec.y), floor(vec.z), floor(vec.w));
}

template<class T>
inline T ceil(T t)
{
	return std::ceil(t);
}

template<class T>
inline vec2<T> ceil(vec2<T> vec)
{
	return vec2<T>(ceil(vec.x), ceil(vec.y));
}

template<class T>
inline vec3<T> ceil(vec3<T> vec)
{
	return vec3<T>(ceil(vec.x), ceil(vec.y), ceil(vec.z));
}

template<class T>
inline vec4<T> ceil(vec4<T> vec)
{
	return vec4<T>(ceil(vec.x), ceil(vec.y), ceil(vec.z), ceil(vec.w));
}

template<class T>
inline T frac(T t)
{
	return t - floor(t);;
}

template<class T>
inline vec2<T> frac(vec2<T> vec)
{
	return vec2<T>(frac(vec.x), frac(vec.y));
}

template<class T>
inline vec3<T> frac(vec3<T> vec)
{
	return vec3<T>(frac(vec.x), frac(vec.y), frac(vec.z));
}

template<class T>
inline vec4<T> frac(vec4<T> vec)
{
	return vec4<T>(frac(vec.x), frac(vec.y), frac(vec.z), frac(vec.w));
}

template<class T>
inline T mod(T t1, T t2)
{
	return std::fmod(t1, t2);
}

template<class T>
inline vec2<T> mod(vec2<T> vec1, vec2<T> vec2)
{
	return vec2<T>(mod(vec1.x, vec2.x), mod(vec1.y, vec2.y));
}

template<class T>
inline vec3<T> mod(vec3<T> vec1, vec3<T> vec2)
{
	return vec3<T>(mod(vec1.x, vec2.x), mod(vec1.y, vec2.y), mod(vec1.z, vec2.z));
}

template<class T>
inline vec4<T> mod(vec4<T> vec1, vec4<T> vec2)
{
	return vec4<T>(mod(vec1.x, vec2.x), mod(vec1.y, vec2.y), mod(vec1.z, vec2.z), mod(vec1.w, vec2.w));
}

/*
	smooth_interpolation
	- returns 0 if t < a
	- returns 1 if t > b
	- otherwise returns smooth interpolation between 0 and 1 based on the relative position of t between a and b 
*/
template<class T>
inline T smooth_interpolation(T a, T b, T t)
{
	t = clamp((t - a) / (b - a), 0.0, 1.0);
	return t * t * (3.0 - 2.0 * t);
}

/*
	smooth_interpolation
	- returns 0 if t < a
	- returns 1 if t > b
	- otherwise returns smooth interpolation between 0 and 1 based on the relative position of t between a and b
*/
template<class T>
inline vec2<T> smooth_interpolation(vec2<T> vec1, vec2<T> vec2, T t)
{
	return vec2<T>(smooth_interpolation(vec1.x, vec2.x, t), smooth_interpolation(vec1.y, vec2.y, t));
}

/*
	smooth_interpolation
	- returns 0 if t < a
	- returns 1 if t > b
	- otherwise returns smooth interpolation between 0 and 1 based on the relative position of t between a and b
*/
template<class T>
inline vec3<T> smooth_interpolation(vec3<T> vec1, vec3<T> vec2, T t)
{
	return vec3<T>(smooth_interpolation(vec1.x, vec2.x, t), smooth_interpolation(vec1.y, vec2.y, t), smooth_interpolation(vec1.z, vec2.z, t));
}

/*
	smooth_interpolation
	- returns 0 if t < a
	- returns 1 if t > b
	- otherwise returns smooth interpolation between 0 and 1 based on the relative position of t between a and b
*/
template<class T>
inline vec4<T> smooth_interpolation(vec4<T> vec1, vec4<T> vec2, T t)
{
	return vec4<T>(smooth_interpolation(vec1.x, vec2.x, t), smooth_interpolation(vec1.y, vec2.y, t), smooth_interpolation(vec1.z, vec2.z, t), smooth_interpolation(vec1.w, vec2.w, t));
}

template<class T>
inline bool equal(T t1, T t2, T threshold = FLOATING_POINT_EQUAL_THRESHOLD)
{
	static_assert(std::is_floating_point<T>::value, "Type T of function equal(T t1, T t2, T threshold = 0.0001) must be a floating-point type!");
	return abs(t1 - t2) <= threshold;
}

template<class T>
inline std::string to_string(vec2<T> vec)
{
	return vec.to_string();
}

template<class T>
inline std::string to_string(vec3<T> vec)
{
	return vec.to_string();
}

template<class T>
inline std::string to_string(vec4<T> vec)
{
	return vec.to_string();
}

inline vec2<float> parse_vec2f(std::string text)
{
	std::stringstream stream(text);
	vec2<float> vec;
	stream >> vec.x >> vec.y;
	return vec;
}

inline vec3<float> parse_vec3f(std::string text)
{
	std::stringstream stream(text);
	vec3<float> vec;
	stream >> vec.x >> vec.y >> vec.z;
	return vec;
}

inline vec4<float> parse_vec4f(std::string text)
{
	std::stringstream stream(text);
	vec4<float> vec;
	stream >> vec.x >> vec.y >> vec.z >> vec.w;
	return vec;
}

inline vec2<double> parse_vec2d(std::string text)
{
	std::stringstream stream(text);
	vec2<double> vec;
	stream >> vec.x >> vec.y;
	return vec;
}

inline vec3<double> parse_vec3d(std::string text)
{
	std::stringstream stream(text);
	vec3<double> vec;
	stream >> vec.x >> vec.y >> vec.z;
	return vec;
}

inline vec4<double> parse_vec4d(std::string text)
{
	std::stringstream stream(text);
	vec4<double> vec;
	stream >> vec.x >> vec.y >> vec.z >> vec.w;
	return vec;
}

inline vec2<long double> parse_vec2ld(std::string text)
{
	std::stringstream stream(text);
	vec2<long double> vec;
	stream >> vec.x >> vec.y;
	return vec;
}

inline vec3<long double> parse_vec3ld(std::string text)
{
	std::stringstream stream(text);
	vec3<long double> vec;
	stream >> vec.x >> vec.y >> vec.z;
	return vec;
}

inline vec4<long double> parse_vec4ld(std::string text)
{
	std::stringstream stream(text);
	vec4<long double> vec;
	stream >> vec.x >> vec.y >> vec.z >> vec.w;
	return vec;
}

template<class T>
inline std::ostream& operator<<(std::ostream& out, vec2<T>& vec)
{
	out.setf(std::ios::fixed);
	out << std::ios::fixed << std::setprecision(2) << "vec4(" << vec.x << ", " << vec.y << ")";
	return out;
}

template<class T>
inline std::istream& operator>>(std::istream& in, vec2<T>& vec)
{
	in >> vec.x >> vec.y;
	return in;
}

template<class T>
inline std::ostream& operator<<(std::ostream& out, vec3<T>& vec)
{
	out.setf(std::ios::fixed);
	out << std::ios::fixed << std::setprecision(2) << "vec4(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return out;
}

template<class T>
inline std::istream& operator>>(std::istream& in, vec3<T>& vec)
{
	in >> vec.x >> vec.y >> vec.z;
	return in;
}

template<class T>
inline std::ostream& operator<<(std::ostream& out, vec4<T>& vec)
{
	out.setf(std::ios::fixed);
	out << std::ios::fixed << std::setprecision(2) << "vec4(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
	return out;
}

template<class T>
inline std::istream& operator>>(std::istream& in, vec4<T>& vec)
{
	in >> vec.x >> vec.y >> vec.z >> vec.w;
	return in;
}

#endif // !__VECTOR__
