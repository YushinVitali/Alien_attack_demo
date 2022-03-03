/// @file common.hpp
/// @brief
#pragma once

#ifndef __MATH_COMMON_HPP__
#define __MATH_COMMON_HPP__


namespace Engine {

template<typename T>
bool IsValueInRange(T sourceValue, T lowerBoundy, T upperBoundy) {
	return lowerBoundy <= sourceValue && sourceValue <= upperBoundy;
}

} // namespace Engine

#endif // !defined(__MATH_COMMON_HPP__)
