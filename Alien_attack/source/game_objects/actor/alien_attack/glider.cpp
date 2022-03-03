/// @file glider.cpp
/// @brief Implementation of the actor of glider.
#include <game_objects/actor/alien_attack/glider.hpp>

#include <sound/sound_manager.hpp>


namespace AlienAttack {

namespace Actor {

Glider::Glider() : Engine::Actor::Enemy() {
	m_dyingTime = 25;
	m_health = 1;
	m_moveSpeed = 3;
	m_gap = 60;
}


void Glider::Update() {
	if(m_isDying) {
		m_velocity.SetX(0);
		m_velocity.SetY(0);
		DoDyingAnimation();
	} else {
		if(m_position.GetY() >= m_maxHeight) {
			m_velocity.SetY(-m_moveSpeed);
		} else if(m_position.GetY() <= m_minHeight) {
			m_velocity.SetY(m_moveSpeed);
		}
	}
	Enemy::Update();
}


void Glider::Load(const Engine::LoaderParams &params) {
	Enemy::Load(params);

	m_velocity.SetX(-m_moveSpeed);
	m_velocity.SetY(m_moveSpeed / 2);

	m_maxHeight = m_position.GetY() + m_gap;
	m_minHeight = m_position.GetY() - m_gap;
}


void Glider::Collision() {
	--m_health;
	if(0 != m_health) {
		return;
	}

	if(!m_isPlayedDeathSound) {
		Engine::SoundManager::Instance()->PlaySound("explode", 0);

		m_textureId = "explosion";
		m_currentFrame = 0;
		m_frameCount = 9;
		m_width = 40;
		m_height = 40;
		m_isDying = true;
	}
}

} // namespace Actor

} // namespace AlienAttack
