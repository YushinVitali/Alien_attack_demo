/// @file bullet_handler.cpp
/// @brief Implementation of the bullet actor processing system.
#include <game_objects/actor/bullet_handler.hpp>

#include <SDL.h>

#include <game.hpp>


namespace Engine {

namespace Actor {

BulletHandler* BulletHandler::m_instance{ nullptr };


BulletHandler* BulletHandler::Instance() {
	if(!m_instance) {
		m_instance = new BulletHandler();
	}
	return m_instance;
}


void BulletHandler::UpdateBullets() {
	const SDL_Rect windowRect{
		0, 0,
		Game::Instance()->GetWindowSize().width,
		Game::Instance()->GetWindowSize().height
	};

	for(std::vector<std::unique_ptr<PlayerBullet>>::iterator playerBullet = m_playerBullets.begin();
			playerBullet != m_playerBullets.end(); ) {

		SDL_Point bulletPosition{ static_cast<int32_t>((*playerBullet)->GetPosition().GetX()),
								  static_cast<int32_t>((*playerBullet)->GetPosition().GetY()) };
		if(!SDL_PointInRect(&bulletPosition, &windowRect)) {
			playerBullet = m_playerBullets.erase(playerBullet);
		} else {
			(*playerBullet)->Update();
			++playerBullet;
		}
	}

	for(std::vector<std::unique_ptr<EnemyBullet>>::iterator enemyBullet = m_enemyBullets.begin();
			enemyBullet != m_enemyBullets.end(); ) {

		SDL_Point bulletPosition{ static_cast<int32_t>((*enemyBullet)->GetPosition().GetX()),
								  static_cast<int32_t>((*enemyBullet)->GetPosition().GetY()) };
		if(!SDL_PointInRect(&bulletPosition, &windowRect)) {
			enemyBullet = m_enemyBullets.erase(enemyBullet);
		} else {
			(*enemyBullet)->Update();
			++enemyBullet;
		}
	}
}


void BulletHandler::DrawBullets() {
	for(auto& playerBullet : m_playerBullets) {
		playerBullet->Draw();
	}

	for(auto& enemyBullet : m_enemyBullets) {
		enemyBullet->Draw();
	}

	SDL_RenderPresent(Game::Instance()->GetRenderer());
}


void BulletHandler::ClearBullets() {
	m_playerBullets.clear();
	m_enemyBullets.clear();
}

void BulletHandler::AddPlayerBullet(int32_t x, int32_t y,
									int32_t width, int32_t height,
									const std::string& textureId,
									int32_t frameCount, Vector2D heading) {
	std::unique_ptr<PlayerBullet> playerBullet{ std::make_unique<PlayerBullet>() };
	playerBullet->Load({ x, y, width, height, frameCount, textureId }, heading);

	m_playerBullets.emplace_back(std::move(playerBullet));
}


void BulletHandler::AddEnemyBullet(int32_t x, int32_t y,
								   int32_t width, int32_t height,
								   const std::string& textureId,
								   int32_t frameCount, Vector2D heading) {
	std::unique_ptr<EnemyBullet> enemyBullet{ std::make_unique<EnemyBullet>() };
	enemyBullet->Load({ x, y, width, height, frameCount, textureId }, heading);

	m_enemyBullets.emplace_back(std::move(enemyBullet));
}


const std::vector<std::unique_ptr<PlayerBullet>>& BulletHandler::GetPlayerBullets() const {
	return m_playerBullets;
}


const std::vector<std::unique_ptr<EnemyBullet>>& BulletHandler::GetEnemyBullets() const {
	return m_enemyBullets;
}

} // namespace Actor

} // namespace Engine
