/// @file loader_params.cpp
/// @brief Description of texture loading parameters.
#pragma once

#ifndef __LOADER_PARAMS_HPP__
#define __LOADER_PARAMS_HPP__


#include <cstdint>
#include <string>


namespace Engine {

/// @brief Texture loading parameters.
class LoaderParams {
public:
	LoaderParams(int32_t x, int32_t y, int32_t width, int32_t height,
				 int32_t frameCount, const std::string& textureId,
				 int32_t callbackId = 0, int32_t animSpeed = 0);
	LoaderParams(int32_t x, int32_t y, int32_t width, int32_t height,
				 int32_t frameCount, std::string&& textureId,
				 int32_t callbackId = 0, int32_t animSpeed = 0);

public:
	int32_t GetX() const noexcept;
	int32_t GetY() const noexcept;
	int32_t GetWidth() const noexcept;
	int32_t GetHeight() const noexcept;
	int32_t GetFrameCount() const noexcept;
	std::string GetTextureId() const noexcept;
	int32_t GetCallbackId() const noexcept;
	int32_t GetAnimSpeed() const noexcept;

private:
	std::string m_textureId;

	int32_t m_x;
	int32_t m_y;

	int32_t m_width;
	int32_t m_height;

	int32_t m_frameCount;

	int32_t m_callbackId;

	int32_t m_animSpeed;
}; // class LoaderParams

} // namespace Engine


#endif // !defined(__LOADER_PARAMS_HPP__)
