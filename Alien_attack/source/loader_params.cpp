/// @file loader_params.cpp
/// @brief Implementing texture loading parameters
#include <loader_params.hpp>


namespace Engine {

LoaderParams::LoaderParams(int32_t x, int32_t y, int32_t width, int32_t height,
						   int32_t frameCount, const std::string& textureId,
						   int32_t callbackId /* = 0 */, int32_t animSpeed /* = 0 */)
						   : m_textureId(textureId),
							 m_x(x), m_y(y),
							 m_width(width), m_height(height),
							 m_frameCount(frameCount),
							 m_callbackId(callbackId),
							 m_animSpeed(animSpeed) {};

LoaderParams::LoaderParams(int32_t x, int32_t y, int32_t width, int32_t height,
						   int32_t frameCount, std::string&& textureId,
						   int32_t callbackId /* = 0 */, int32_t animSpeed /* = 0 */)
						   : m_x(x), m_y(y),
							 m_width(width), m_height(height),
							 m_frameCount(frameCount),
							 m_callbackId(callbackId),
							 m_animSpeed(animSpeed) {
	std::swap(m_textureId, textureId);
}


int32_t LoaderParams::GetX() const noexcept {
	return m_x;
}


int32_t LoaderParams::GetY() const noexcept {
	return m_y;
}


int32_t LoaderParams::GetWidth() const noexcept {
	return m_width;
}


int32_t LoaderParams::GetHeight() const noexcept {
	return m_height;
}


int32_t LoaderParams::GetFrameCount() const noexcept {
	return m_frameCount;
}


std::string LoaderParams::GetTextureId() const noexcept {
	return m_textureId;
}


int32_t LoaderParams::GetCallbackId() const noexcept {
	return m_callbackId;
}


int32_t LoaderParams::GetAnimSpeed() const noexcept {
	return m_animSpeed;
}

} // namespace Engine
