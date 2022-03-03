/// @file collision.hpp
/// @brief Description of the collision calculation.
#pragma once

#ifndef __COLLISION_HPP__
#define __COLLISION_HPP__


#include <cstdint>

#include <SDL.h>


namespace Engine {

namespace { // anonymous namespace

/// @brief Rectangle size division factor to calculate a new hitbox.
/// @note 0.75 == 3/4.
constexpr float BUFFER = 0.75f;

} // namespace anonymous


/// @brief Check the collision of two rectangles with a reduced hitbox.
bool CheckCollision(const SDL_Rect& firstSrcRect,
					const SDL_Rect& secondSrcRect);

} // namespace Engine


#endif // !defined(__COLLISION_HPP__)
