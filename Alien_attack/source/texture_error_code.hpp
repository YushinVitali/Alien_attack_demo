/// @file texture_error_code.hpp
/// @brief Description of basic texture loading and rendering system errors.
#pragma once

#ifndef __TEXTURE_ERROR_CODE_HPP__
#define __TEXTURE_ERROR_CODE_HPP__


#include <system_error>


namespace Engine {

/// @brief Errors in the texture loading and rendering system.
enum class TextureError {
	LoadingFailed						= 1,

	ConversionSurfaceToTextureFailed	= 10,

	RenderTextToSurface					= 20,

	InitTTFLibraryFailed				= 30
}; // enum class TextureError


std::error_code make_error_code(TextureError errorCode);

} // namespace Engine


namespace std {

template<>
struct is_error_code_enum<Engine::TextureError> : true_type {};

} // namespace std


#endif // !defined(__TEXTURE_ERROR_CODE_HPP__)
