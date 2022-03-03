/// @file input_handler.hpp
/// @brief Implementation of the input processing system.
#include <controllers/input_handler.hpp>

#include <string>

#include <SDL.h>

#include <logger.hpp>

#include <game.hpp>
#include <engine_error_code.hpp>
#include <controllers/controller_error_code.hpp>


namespace Engine {

InputHandler* InputHandler::m_instance{ nullptr };


InputHandler* InputHandler::Instance() {
	if(!m_instance) {
		m_instance = new InputHandler();
	}
	return m_instance;
}


void InputHandler::Update() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: {
				Game::Instance()->Quit();
				continue;
			}
		}
	}
}


void InputHandler::Clean() {
	lout(LOG_TYPE::INFO, "Clean input handler...");

	CleanJoysticks();
}


void InputHandler::InitialiseJoysticks() {
	if(SDL_WasInit(SDL_INIT_GAMECONTROLLER) == 0) {
		if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) != 0) {
			lerr(std::string{ SDL_GetError() }, CoreError::SdlInitSubSystemFailed);
			return;
		}
	}

	int32_t numberJoysticks{ SDL_NumJoysticks() };
	if(0 >= numberJoysticks) {
		m_isJoystickInitialised = false;
		return;
	}

	for(int32_t joystickIndex = 0; joystickIndex < numberJoysticks; ++joystickIndex) {
		if(!SDL_IsGameController(joystickIndex)) {
			lerr(std::string{ SDL_GetError() }, ControllerError::JoystickNotSuitable);
			continue;
		}

		SDL_GameController* joystick{ SDL_GameControllerOpen(joystickIndex) };
		if(!joystick) {
			lerr(std::string{ SDL_GetError() }, ControllerError::JoystickInitFailed);
			continue;
		}

		m_joysticks.emplace_back(joystick);
		lout(LOG_TYPE::INFO,
			 std::string{ SDL_GameControllerName(joystick) } +
			 " device initialized successfully!");
	}

	SDL_JoystickEventState(SDL_ENABLE);
	m_isJoystickInitialised = true;

	lout(LOG_TYPE::INFO, std::string{ "Initialize " } +
		 std::to_string(m_joysticks.size()) +
		 std::string{ " joystick(s)." });
}


bool InputHandler::IsJoysticksInitialised() const noexcept {
	return m_isJoystickInitialised;
}


bool InputHandler::IsJoystickButtonPush(int32_t index, SDL_GameControllerButton button) const {
	return (static_cast<bool>(
			SDL_GameControllerGetButton(m_joysticks[index], button)));
}


int32_t InputHandler::GetAxisValue(int32_t index, SDL_GameControllerAxis axis) const {
	return SDL_GameControllerGetAxis(m_joysticks[index], axis);
}


bool InputHandler::IsMouseButtonPush(uint8_t button) const {
	return (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button));
}


SDL_Point InputHandler::GetMousePosition() const {
	int32_t x{ 0 };
	int32_t y{ 0 };
	SDL_GetMouseState(&x, &y);
	return { x, y };
}


bool InputHandler::IsKeyDown(SDL_Scancode key) const {
	return (static_cast<bool>(
			SDL_GetKeyboardState(nullptr)[key]));
}


InputHandler::~InputHandler() {
	Clean();
}


void InputHandler::CleanJoysticks() {
	if(!m_isJoystickInitialised) {
		return;
	}

	lout(LOG_TYPE::INFO, "Cleaning joystick(s)...");
	for(auto& joystick : m_joysticks) {
		lout(LOG_TYPE::INFO, std::string{ "Cleaning "} +
			 std::string{ SDL_GameControllerName(joystick) } + "...");
		SDL_GameControllerClose(joystick);
	}
	m_joysticks.clear();
}

} // namespace Engine
