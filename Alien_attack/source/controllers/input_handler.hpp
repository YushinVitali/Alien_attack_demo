/// @file input_handler.hpp
/// @brief Description of the input processing system.
#pragma once

#ifndef __INPUT_HANDLER_HPP__
#define __INPUT_HANDLER_HPP__


#include <vector>

#include <SDL_events.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>

#include <math/vector_2d.hpp>


namespace Engine {

namespace { // anonymous namespace

/// @brief Dead zone of joystick stick movement.
constexpr uint32_t JOYSTICK_DEAD_ZONE{ 10'000 };

} // namespace anonymous


/// @brief Input processing system.
class InputHandler {
public:
	~InputHandler();

	static InputHandler* Instance();

	void Update();
	void Clean();

	void InitialiseJoysticks();

	bool IsJoysticksInitialised() const noexcept;
	bool IsJoystickButtonPush(int32_t index, SDL_GameControllerButton button) const;
	int32_t GetAxisValue(int32_t index, SDL_GameControllerAxis axis) const;

	bool IsMouseButtonPush(uint8_t button) const;
	SDL_Point GetMousePosition() const;

	bool IsKeyDown(SDL_Scancode key) const;

private:
	InputHandler() = default;

	void CleanJoysticks();

private:
	static InputHandler* m_instance;

	std::vector<SDL_GameController*> m_joysticks;

	bool m_isJoystickInitialised{ false };
}; // class InputHandler

} // namespace Engine


#endif // !defined(__INPUT_HANDLER_HPP__)
