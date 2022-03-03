/// @file common.hpp
/// @brief Description of the main auxiliary engine design.
#pragma once

#ifndef __COMMON_HPP__
#define __COMMON_HPP__


#include <cstdint>


namespace Engine {

/// @brief Dimension generalization for rectangular objects.
struct RectangleSize {
	int32_t width;
	int32_t height;
}; // struct RectangleSize

} // namespace Engine


#endif // !defined(__COMMON_HPP__)
