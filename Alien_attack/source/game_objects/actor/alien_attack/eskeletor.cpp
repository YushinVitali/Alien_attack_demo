/// @file eskeletor.cpp
/// @brief Implementation of the actor of eskeletor.
#include <game_objects/actor/alien_attack/eskeletor.hpp>

#include <game.hpp>

#include <math/vector_2d.hpp>

#include <game_objects/actor/bullet_handler.hpp>

#include <sound/sound_manager.hpp>


namespace AlienAttack {

namespace Actor {

Eskeletor::Eskeletor()
	: Enemy() {
	m_dyingTime = 50;
	m_health = 3;
	m_moveSpeed = 3;
	m_bulletFiringSpeed = 50;
}


void Eskeletor::Update() {
	if(m_isDying) {
		m_velocity.SetY(0);
		DoDyingAnimation();
	} else {
		Scroll(Engine::Game::Instance()->GetScrollSpeed());
		m_velocity.SetY(m_moveSpeed);

		if(m_bulletCounter == m_bulletFiringSpeed) {
			Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
						m_position.GetX(), m_position.GetY(), 16, 16, "bullet1", 1, { -3, 0 });
			Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
						m_position.GetX(), m_position.GetY(), 16, 16, "bullet1", 1, { 3, 0 });
			m_bulletCounter = 0;
		}
		++m_bulletCounter;
	}
	Enemy::Update();
}


void Eskeletor::Collision() {
	--m_health;
	if(0 == m_health) {
		if(m_isPlayedDeathSound) {
			return;
		}
		Engine::SoundManager::Instance()->PlaySound("explode", 0);

		m_textureId = "largeexplosion";
		m_currentFrame = 0;
		m_frameCount = 9;
		m_width = 60;
		m_height = 60;
		m_isDying = true;
	}
}

} // namespace Actor

} // namespace AlienAttack
