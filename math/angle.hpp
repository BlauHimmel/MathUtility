#pragma once

#ifndef __ANGLE__
#define __ANGLE__

#include <type_traits>

#define PI 3.14159

template<class T>
T radian_to_degree(T radian)
{
	static_assert(std::is_floating_point<T>::value, "Type T of the function must be a floating-point type!");
	return radian / PI * 180.0;
}

template<class T>
T degree_to_radian(T degree)
{
	static_assert(std::is_floating_point<T>::value, "Type T of the function must be a floating-point type!");
	return degree / 180.0 * PI;
}

#endif // !__ANGLE__
