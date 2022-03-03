/// @file scrolling_background.cpp
/// @brief Implementing of the moving background object.
#include <game_objects/scrolling_background.hpp>

#include <game.hpp>
#include <texture_manager.hpp>


namespace Engine {

ScrollingBackground::ScrollingBackground()
	: GameObject() {}


void ScrollingBackground::Update() {
	if(m_count != m_maxCount) {
		++m_count;
		return;
	}

	m_srcRectFirst.x += m_scrollSpeed;
	m_srcRectFirst.w -= m_scrollSpeed;
	m_destRectFirst.w -= m_scrollSpeed;

	m_srcRectSecond.w += m_scrollSpeed;
	m_destRectSecond.w += m_scrollSpeed;
	m_destRectSecond.x -= m_scrollSpeed;

	if(m_destRectSecond.w >= m_width) {
		m_srcRectFirst = { 0, 0,
						   m_width, m_height };
		m_destRectFirst = { static_cast<int32_t>(m_position.GetX()),
							static_cast<int32_t>(m_position.GetY()),
							m_width, m_height };

		m_srcRectSecond = { 0, 0,
							0, m_height };
		m_destRectSecond = { static_cast<int32_t>(m_position.GetX()) + m_width,
							 static_cast<int32_t>(m_position.GetY()),
							 0, m_height };
	}
	m_count = 0;
}


void ScrollingBackground::Draw() {
	SDL_RenderCopyEx(Game::Instance()->GetRenderer(),
					 TextureManager::Instance()->GetTexture(m_textureId),
					 &m_srcRectFirst, &m_destRectFirst, 0, 0, SDL_FLIP_NONE);
	SDL_RenderCopyEx(Game::Instance()->GetRenderer(),
					 TextureManager::Instance()->GetTexture(m_textureId),
					 &m_srcRectSecond, &m_destRectSecond, 0, 0, SDL_FLIP_NONE);
}


void ScrollingBackground::Clean() {

}


void ScrollingBackground::Load(const LoaderParams& params)
{
	GameObject::Load(params);

	m_scrollSpeed = params.GetAnimSpeed();

	m_srcRectFirst = { 0, 0, m_width, m_height };
	m_destRectFirst = { static_cast<int32_t>(m_position.GetX()),
						static_cast<int32_t>(m_position.GetY()),
						m_width, m_height };

	m_srcRectSecond = { 0, 0, 0, m_height };
	m_destRectSecond = {
		static_cast<int32_t>(m_position.GetX() + m_width),
		static_cast<int32_t>(m_position.GetY()),
		0, m_height
	};
}


void ScrollingBackground::Collision() {

}


std::string ScrollingBackground::Type() const {
	return "ScrollingBackground";
}

} // namespace Engine
