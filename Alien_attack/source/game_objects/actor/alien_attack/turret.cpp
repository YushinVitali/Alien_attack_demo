/// @file turret.cpp
/// @brief Implementation of the actor of turret.
#include <game_objects/actor/alien_attack/turret.hpp>

#include <game.hpp>
#include <game_objects/actor/bullet_handler.hpp>
#include <sound/sound_manager.hpp>

#include <texture_manager.hpp>


namespace AlienAttack {

namespace Actor {

Turret::Turret() : Engine::Actor::Enemy() {
	m_dyingTime = 1000;
	m_health = 8;
	m_bulletFiringSpeed = 60;
}


void Turret::Update() {
	Scroll(Engine::Game::Instance()->GetScrollSpeed());

	if(m_isDying) {
		DoDyingAnimation();
	} else {
		if(m_bulletCounter == m_bulletFiringSpeed) {
			Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
				m_position.GetX(), m_position.GetY(), 16, 16,
				"bullet2", 1, { -3, -3 });
			Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
				m_position.GetX() + 20, m_position.GetY(), 16, 16,
				"bullet2", 1, { 0, -3 });
			Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
				m_position.GetX() + 40, m_position.GetY(), 16, 16,
				"bullet2", 1, { 3, -3 });
			m_bulletCounter = 0;
		}
		++m_bulletCounter;
	}
}


void Turret::Collision() {
	--m_health;

	if(0 != m_health) {
		return;
	}

	if(!m_isPlayedDeathSound) {
		Engine::SoundManager::Instance()->PlaySound("explode", 0);

		m_textureId = "large_explosion";
		m_currentFrame = 0;
		m_frameCount = 9;
		m_width = 60;
		m_height = 60;
		m_isDying = true;
	}
}

} // namespace Actor

} // namespace AlienAttack

