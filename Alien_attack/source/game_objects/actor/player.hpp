/// @file player.hpp
/// @brief Description of the player actor.
#pragma once

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__


#include <loader_params.hpp>
#include <game_objects/actor/shooter_object.hpp>
#include <game_objects/game_object_factory.hpp>


namespace Engine {

namespace Actor {

/// @brief Player actor.
class Player : public ShooterObject {
public:
	Player();
	virtual ~Player() override = default;

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	virtual void Load(const LoaderParams& params) override;

	virtual void Collision() override;

	virtual std::string Type() const override;

	virtual void Scroll(float scrollSpeed) override;
private:
	void HandleInput();

	void HandleAnimation();
	void HandleDyingAnimation();
	void HandleMovingAnimation();

	void Ressurect();
private:
	void OnKeyboard();
	void OnJoystick();
	void OnMouse();

private:
	int32_t m_invulnerableTime{ 200 };
	int32_t m_invulnerableCounter{ 0 };

	uint8_t m_joystickNumber{ 0 };

	bool m_invulnerable{ false };

	float m_baseVelocity{ 2.5f };
}; // class Player


class PlayerCreator : public BaseCreator {
	virtual GameObject* CreateGameObject() const override {
		return new Player();
	}
};

} // namespace Actor

} // namespace Engine


#endif // !defined(__PLAYER_HPP__)
