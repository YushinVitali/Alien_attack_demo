/// @file game_state_error_code.cpp
/// @brief Implementation of errors in the game state control system
#include <game_states/game_state_error_code.hpp>

#include <string>


namespace Engine {

namespace { // anonymous namespace

struct GameStateErrorCategory : std::error_category {
	const char* name() const noexcept override;
	std::string message(int errorCode) const override;
}; // struct GameStateErrorCategory


const char* GameStateErrorCategory::name() const noexcept {
	return "GameStateError";
}


std::string GameStateErrorCategory::message(int errorCode) const {
	switch(static_cast<GameStateError>(errorCode)) {
		case GameStateError::StateStackIsEmpty:
			return "The game state stack is empty!";

		case GameStateError::StateEnterFailed:
			return "The game state stack is empty!";

		default:
			return "Unrecognized error!";
	}
}

} // anonymous namespace


const GameStateErrorCategory TheGameStateErrorCategory {};


std::error_code make_error_code(GameStateError errorCode) {
	return {
		static_cast<int>(errorCode),
		TheGameStateErrorCategory
	};
}

} // namespace Engine
