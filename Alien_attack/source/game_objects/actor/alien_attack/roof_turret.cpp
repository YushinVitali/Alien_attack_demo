/// @file roof_turret.cpp
/// @brief Implementation of the actor of roof turret.
#include <game_objects/actor/alien_attack/roof_turret.hpp>

#include <game.hpp>

#include <game_objects/actor/bullet_handler.hpp>

#include <texture_manager.hpp>


namespace AlienAttack {

namespace Actor {

void RoofTurret::Update() {
	Scroll(Engine::Game::Instance()->GetScrollSpeed());
	if(m_isDying) {
		DoDyingAnimation();
	} else {
		if(m_bulletCounter == m_bulletFiringSpeed) {
			Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
				m_position.GetX(), m_position.GetY() + 20, 16, 16,
				"bullet2", 1, { -3, 3 });
			Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
				m_position.GetX() + 20, m_position.GetY() + 20, 16, 16,
				"bullet2", 1, { 0, 3 });
			Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
				m_position.GetX() + 40, m_position.GetY() + 20, 16, 16,
				"bullet2", 1, { 3, 3 });
			m_bulletCounter = 0;
		}
		++m_bulletCounter;
	}
}


void RoofTurret::Draw() {
	Engine::TextureManager::Instance()->DrawFrame(m_textureId,
												  m_position.GetX(), m_position.GetY(),
												  m_width, m_height,
												  m_currentRow, m_currentFrame,
												  Engine::Game::Instance()->GetRenderer(),
												  m_angle, m_alpha, SDL_FLIP_VERTICAL);
}

} // namespace Actor

} // namespace AlienAttack
