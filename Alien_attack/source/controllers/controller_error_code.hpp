/// @file controller_error_code.hpp
/// @brief Description of controller errors.
#pragma once

#ifndef __CONTROLLER_ERROR_CODE_HPP__
#define __CONTROLLER_ERROR_CODE_HPP__


#include <system_error>


namespace Engine {

/// @brief Error controllers.
enum class ControllerError {
	JoystickNotSuitable	= 1,
	JoystickInitFailed	= 2
}; // enum class ControllerError


std::error_code make_error_code(ControllerError errorCode);

} // namespace Engine


namespace std {

template<>
struct is_error_code_enum<Engine::ControllerError> : true_type {};

} // namespace std


#endif // !defined(__CONTROLLER_ERROR_CODE_HPP__)
