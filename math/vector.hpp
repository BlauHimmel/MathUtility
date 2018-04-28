#pragma once

#ifndef __VECTOR__
#define __VECTOR__

#include <type_traits>
#include <stdexcept>
#include <cmath>

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
		static_assert(std::is_floating_point<T>::value, "T must be a floating-point type!");
		x = 0.0; y = 0.0;
	}

	explicit vec2(T value)
	{
		static_assert(std::is_floating_point<T>::value, "T must be a floating-point type!");
		x = value; y = value;
	}

	vec2(T x, T y)
	{
		static_assert(std::is_floating_point<T>::value, "T must be a floating-point type!");
		this->x = x; this->y = y;
	}

public:
	T operator[](size_t index) const
	{
		if (index >= 2) { throw std::out_of_range("vec2 index out of range!"); }
		return *(&x + index);
	}

public:
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
		return this->length() == 1.0;
	}

	T dot(vec2<T> vec)
	{
		return vec.x * this->x + vec.y * this->y;
	}
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
		static_assert(std::is_floating_point<T>::value, "T must be a floating-point type!");
		x = 0.0; y = 0.0; z = 0.0;
	}

	explicit vec3(T value)
	{
		static_assert(std::is_floating_point<T>::value, "T must be a floating-point type!");
		x = value; y = value; z = value;
	}

	vec3(T x, T y, T z)
	{
		static_assert(std::is_floating_point<T>::value, "T must be a floating-point type!");
		this->x = x; this->y = y; this->z = z;
	}

public:
	T operator[](size_t index) const
	{
		if (index >= 3) { throw std::out_of_range("vec3 index out of range!"); }
		return *(&x + index);
	}

public:
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
		return this->length() == 1.0;
	}

	T dot(vec3<T> vec)
	{
		return vec.x * this->x + vec.y * this->y + vec.z * this->z;
	}

	vec3<T> cross(vec3<T> vec)
	{
		return vec3<T>(this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x);
	}
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
		static_assert(std::is_floating_point<T>::value, "T must be a floating-point type!");
		x = 0.0; y = 0.0; z = 0.0; w = 0.0;
	}

	explicit vec4(T value)
	{
		static_assert(std::is_floating_point<T>::value, "T must be a floating-point type!");
		x = value; y = value; z = value; w = value;
	}

	vec4(T x, T y, T z, T w)
	{
		static_assert(std::is_floating_point<T>::value, "T must be a floating-point type!");
		this->x = x; this->y = y; this->z = z; this->w = w;
	}

public:
	T operator[](size_t index) const
	{
		if (index >= 4) { throw std::out_of_range("vec4 index out of range!"); }
		return *(&x + index);
	}

public:
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
		return this->length() == 1.0;
	}

	T dot(vec4<T> vec)
	{
		return vec.x * this->x + vec.y * this->y + vec.z * this->z + vec.w * this->w;
	}
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
	return vec1.x == vec2.x && vec1.y == vec2.y;
}

template<class T>
inline bool operator==(vec3<T> vec1, vec3<T> vec2)
{
	return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
}

template<class T>
inline bool operator==(vec4<T> vec1, vec4<T> vec2)
{
	return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z && vec1.w == vec2.w;
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

#endif // !__VECTOR__
