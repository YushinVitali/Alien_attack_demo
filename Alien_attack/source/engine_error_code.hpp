/// @file engine_error_code.hpp
/// @brief Description of basic engine errors.
#pragma once

#ifndef __ENGINE_ERROR_CODE_HPP__
#define __ENGINE_ERROR_CODE_HPP__


#include <system_error>


namespace Engine {

/// @brief Basic engine errors.
enum class CoreError {
	SdlInitFailed			= 1,
	SdlInitSubSystemFailed	= 2,

	WindowInitFailed		= 10,
	RendererInitFailed		= 11,
}; // enum class EngineErrorCode


std::error_code make_error_code(CoreError errorCode);

} // namespace Engine


namespace std {

template<>
struct is_error_code_enum<Engine::CoreError> : true_type {};

} // namespace std


#endif // !defined(__ENGINE_ERROR_CODE_HPP__)
