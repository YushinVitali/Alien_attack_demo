/// @file collision.cpp
/// @brief Implementation of the collision calculation.
#include <collision/collision.hpp>


namespace Engine {

bool CheckCollision(const SDL_Rect& firstSrcRect,
					const SDL_Rect& secondSrcRect) {
	SDL_Rect firstModifyRect{
		firstSrcRect.x, firstSrcRect.y,
		static_cast<int32_t>(firstSrcRect.w * BUFFER),
		static_cast<int32_t>(firstSrcRect.h * BUFFER)
	};

	SDL_Rect secondModifyRect{
		secondSrcRect.x, secondSrcRect.y,
		static_cast<int32_t>(secondSrcRect.w * BUFFER),
		static_cast<int32_t>(secondSrcRect.h * BUFFER)
	};

	return SDL_HasIntersection(&firstModifyRect,
							   &secondModifyRect);
}

} // namespace Engine
