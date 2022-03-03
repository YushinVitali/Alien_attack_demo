/// @file tileset.hpp
/// @brief Description of the tileset.
#pragma once

#ifndef __TILESET_HPP__
#define __TILESET_HPP__


#include <cstdint>
#include <string>


namespace Engine {

/// @brief Parameters of the tileset.
struct Tileset {
	std::string name;

	int32_t firstGridId;

	int32_t tileWidth;
	int32_t tileHeight;

	int32_t spacing;
	int32_t margin;

	int32_t width;
	int32_t height;

	int32_t numberColumns;
}; // struct Tileset

} // namespace Engine


#endif // !defined(__TILESET_HPP__)
