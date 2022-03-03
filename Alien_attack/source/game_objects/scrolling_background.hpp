/// @file scrolling_background.hpp
/// @brief Description of the moving background object.
#pragma once

#ifndef __SCROLLING_BACKGROUND_HPP__
#define __SCROLLING_BACKGROUND_HPP__


#include <string>
#include <cstdint>

#include <SDL.h>

#include <game_objects/game_object.hpp>
#include <game_objects/game_object_factory.hpp>


namespace Engine {

/// @brief Moving background.
class ScrollingBackground : public GameObject {
public:
	ScrollingBackground();
	virtual ~ScrollingBackground() override = default;

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Clean() override;

	virtual void Load(const LoaderParams& params) override;

	virtual void Collision() override;

	virtual std::string Type() const override;

private:
	int32_t m_scrollSpeed;

	int32_t m_count{ 0 };
	int32_t m_maxCount{ 2 };

	SDL_Rect m_srcRectFirst;
	SDL_Rect m_srcRectSecond;

	SDL_Rect m_destRectFirst;
	SDL_Rect m_destRectSecond;
}; // class ScrollingBackground


class ScrollBackgroundCreator : public BaseCreator {
public:
	virtual GameObject* CreateGameObject() const {
		return new ScrollingBackground();
	}
};

} // namespace Engine


#endif // !defined(__SCROLLING_BACKGROUND_HPP__)
