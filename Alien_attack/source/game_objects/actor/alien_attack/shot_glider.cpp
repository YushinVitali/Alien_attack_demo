/// @file shot_glider.cpp
/// @brief Implementation of the actor of shoot glider.
#include <game_objects/actor/alien_attack/shot_glider.hpp>

#include <game_objects/actor/bullet_handler.hpp>

#include <game_objects/actor/shooter_object.hpp>

namespace AlienAttack {

namespace Actor {

ShotGlider::ShotGlider() : Glider() {
	m_bulletFiringSpeed = 35;
	m_moveSpeed = 2;
}


void ShotGlider::Update() {
	if(m_isDying) {
		m_velocity.SetX(0);
		DoDyingAnimation();
	} else {
		if(m_bulletCounter == m_bulletFiringSpeed) {
			Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
				m_position.GetX(), m_position.GetY() + 15,
						16, 16, "bullet2", 1, { -10, 0 });
			m_bulletCounter = 0;
		}
		++m_bulletCounter;
	}

	Glider::Update();
}

void ShotGlider::Load(const Engine::LoaderParams& params)
{
	Glider::Load(params);
	m_velocity.SetX(-m_moveSpeed);
}

} // namespace Actor

} // namespace AlienAttack
