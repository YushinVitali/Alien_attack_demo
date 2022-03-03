/// @file game_object.hpp
/// @brief Description of the base game object.
#pragma once

#ifndef __GAME_OBJECT_HPP__
#define __GAME_OBJECT_HPP__


#include <SDL.h>

#include <string>

#include <loader_params.hpp>

#include <math/vector_2d.hpp>


namespace Engine {

/// @brief Base game object.
class GameObject {
public:
	virtual ~GameObject() = default;

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Clean() = 0;

	virtual void Load(const LoaderParams& params);

	virtual void Collision() = 0;

	virtual std::string Type() const = 0;

	/// @brief Scroll the object together with the tile.
	virtual void Scroll(float scrollSpeed);

	SDL_Rect GetRect() const;

	Vector2D& GetPosition();
	Vector2D GetVeclocity() const noexcept;

	int32_t GetWidth() const noexcept;
	int32_t GetHeight() const noexcept;

	void SetUpdating(bool isUpdating);
	bool isUpdating() const noexcept;

	bool isDead() const noexcept;
	bool isDying() const noexcept;

protected:
	GameObject() = default;

protected:
	std::string m_textureId;

	Vector2D m_position{ 0, 0 };
	Vector2D m_velocity{ 0, 0 };
	Vector2D m_acceleration{ 0, 0 };

	float m_angle{ 0 };

	int32_t m_width{ 0 };
	int32_t m_height{ 0 };

	int32_t m_currentRow{ 0 };
	int32_t m_currentFrame{ 0 };

	int32_t m_frameCount{ 1 };

	int32_t m_alpha{ 255 };

	bool m_isUpdating{ false };
	bool m_isDead{ false };
	bool m_isDying{ false };
}; // class GameObject

} // namespace Engine

#endif // !defined(__GAME_OBJECT_HPP__)
