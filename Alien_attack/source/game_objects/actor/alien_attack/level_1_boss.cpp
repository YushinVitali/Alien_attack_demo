/// @file level_1_boss.cpp
/// @brief Implementation of the actor of level boss.
#include <game_objects/actor/alien_attack/level_1_boss.hpp>

#include <game.hpp>

#include <game_objects/actor/bullet_handler.hpp>

#include <sound/sound_manager.hpp>


namespace AlienAttack {

namespace Actor {

Level1Boss::Level1Boss() : Engine::Actor::Enemy() {
	m_health = 30;
	m_dyingTime = 100;
	m_bulletFiringSpeed = 100;

	m_moveSpeed = 2;

	m_isEntered = false;
}


void Level1Boss::Update() {
	if(!m_isEntered) {
		Scroll(Engine::Game::Instance()->GetScrollSpeed());

		const int32_t mapPositionX{ Engine::Game::Instance()->GetWindowSize().width - (m_width + 20) };
		if(mapPositionX > m_position.GetX()) {
			m_isEntered = true;
		}
		return;
	}

	if(m_isDying) {
		Scroll(Engine::Game::Instance()->GetScrollSpeed());

		m_currentFrame = static_cast<int32_t>((SDL_GetTicks() / (1000 / 3)) % m_frameCount);
		if(m_dyingCounter == m_dyingTime) {
			m_isDead = true;
			Engine::Game::Instance()->SetLevelComplete(true);
		}
		++m_dyingCounter;
		return;
	}

	/// @todo There will probably be a clash with the Map Collision!
	if(m_position.GetY() + m_height >=
			Engine::Game::Instance()->GetWindowSize().height) {
		m_velocity.SetY(-m_moveSpeed);
	} else if(0 >= m_position.GetY()) {
		m_velocity.SetY(m_moveSpeed);
	}

	if(m_bulletCounter == m_bulletFiringSpeed) {
		Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
					m_position.GetX(), m_position.GetY() + 15, 16, 16,
					"bullet2", 1, { -10, 0 });
		Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
					m_position.GetX(), m_position.GetY() + 25, 16, 16,
					"bullet2", 1, { -10, 0 });

		Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
					m_position.GetX(), m_position.GetY() + 200, 16, 16,
					"bullet2", 1, { -10, 0 });
		Engine::Actor::BulletHandler::Instance()->AddEnemyBullet(
					m_position.GetX(), m_position.GetY() + 215, 16, 16,
					"bullet2", 1, { -10, 0 });

		m_bulletCounter = 0;
	}
	++m_bulletCounter;

	Enemy::Update();
}


void Level1Boss::Load(const Engine::LoaderParams& params) {
	Enemy::Load(params);
	m_velocity.SetY(-m_moveSpeed);
}


void Level1Boss::Collision() {
	if(!m_isEntered) {
		return;
	}

	--m_health;

	if(0 != m_health) {
		return;
	}

	if(!m_isPlayedDeathSound) {
		m_position.SetX(m_position.GetX() + 30);
		m_position.SetX(m_position.GetY() + 70);

		Engine::SoundManager::Instance()->PlaySound("explode", 0);

		m_textureId = "boss_explosion";
		m_currentFrame = 0;
		m_frameCount = 9;
		m_width = 180;
		m_height = 180;
		m_isDying = true;
	}
}

} // namespace Actor

} // namespace AlienAttack
