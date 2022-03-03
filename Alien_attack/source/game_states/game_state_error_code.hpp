/// @file game_state_error_code.hpp
/// @brief Description of errors in the game state control system
#pragma once

#ifndef __GAME_STATE_ERROR_CODE_HPP__
#define __GAME_STATE_ERROR_CODE_HPP__


#include <system_error>


namespace Engine {

/// @brief Errors in the game state control system.
enum class GameStateError {
	StateStackIsEmpty	= 1,

	StateEnterFailed	= 10
}; // enum class GameStateError


std::error_code make_error_code(GameStateError errorCode);

} // namespace Engine


namespace std {

template<>
struct is_error_code_enum<Engine::GameStateError> : true_type {};

} // namespace std


#endif // !defined(__GAME_STATE_ERROR_CODE_HPP__)
