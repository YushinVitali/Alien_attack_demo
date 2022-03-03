/// @file game_object.cpp
/// @brief Implementing of the base game object.
#include <game_objects/game_object.hpp>

#include <game.hpp>


namespace Engine {

void GameObject::Load(const LoaderParams& params) {
	m_textureId = params.GetTextureId();
	m_position = { params.GetX(), params.GetY() };

	m_width = params.GetWidth();
	m_height = params.GetHeight();
	m_frameCount = params.GetFrameCount();
}


void GameObject::Scroll(float scrollSpeed) {
	m_position.SetX(m_position.GetX() - scrollSpeed);
}


SDL_Rect GameObject::GetRect() const {
	return {
		static_cast<int32_t>(m_position.GetX()),
		static_cast<int32_t>(m_position.GetY()),
		m_width, m_height
	};
}


Vector2D& GameObject::GetPosition() {
	return m_position;
}


Vector2D GameObject::GetVeclocity() const noexcept {
	return m_velocity;
}


int32_t GameObject::GetWidth() const noexcept {
	return m_width;
}


int32_t GameObject::GetHeight() const noexcept {
	return m_height;
}


void GameObject::SetUpdating(bool isUpdating) {
	m_isUpdating = isUpdating;
}


bool GameObject::isUpdating() const noexcept {
	return m_isUpdating;
}


bool GameObject::isDead() const noexcept {
	return m_isDead;
}


bool GameObject::isDying() const noexcept {
	return m_isDying;
}

} // namespace Engine
