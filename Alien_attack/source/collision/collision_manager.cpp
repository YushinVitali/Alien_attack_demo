/// @file collision_manager.cpp
/// @brief Implementation of the collision handling system.
#include <collision/collision_manager.hpp>

#include <SDL.h>

#include <game_objects/actor/bullet_handler.hpp>

#include <game_objects/game_object.hpp>
#include <level/tile_layer.hpp>


#include <collision/collision.hpp>


namespace Engine {

void CollisionManager::CheckPlayerEnemyBulletCollision(const std::weak_ptr<Actor::Player>& player) {
	if (std::shared_ptr<Actor::Player> sPlayer = player.lock()) {
		SDL_Rect playerRect{ sPlayer->GetRect() };
		for(const auto& enemyBullet : Actor::BulletHandler::Instance()->GetEnemyBullets()) {
			if(CheckCollision(playerRect, enemyBullet->GetRect())) {
				if(sPlayer->isDying() || enemyBullet->isDying()) {
					continue;
				}
				enemyBullet->Collision();
				sPlayer->Collision();
			}
		}
	}
}


void CollisionManager::CheckPlayerEnemyCollision(const std::weak_ptr<Actor::Player>& player,
												 const std::vector<std::shared_ptr<GameObject>>& enemies) {
	if (std::shared_ptr<Actor::Player> sPlayer = player.lock()) {
		SDL_Rect playerRect{ sPlayer->GetRect() };
		for(const auto& enemy : enemies) {
			if(enemy->Type() != "Enemy" || !enemy->isUpdating()) {
				continue;
			}
			if(CheckCollision(playerRect, enemy->GetRect())) {
				if(enemy->isDead() || enemy->isDying()) {
					continue;
				}
				sPlayer->Collision();
			}
		}
	}
}


void CollisionManager::CheckEnemyPlayerBulletCollision(const std::vector<std::shared_ptr<GameObject>>& enemies) {
	for(const auto& enemy : enemies) {
		if(enemy->Type() != std::string{ "Enemy" } || !enemy->isUpdating()) {
			continue;
		}

		for(const auto& playerBullet : Actor::BulletHandler::Instance()->GetPlayerBullets()) {
			if(CheckCollision(enemy->GetRect(), playerBullet->GetRect())) {
				if(enemy->isDying() || playerBullet->isDying()) {
					continue;
				}
				playerBullet->Collision();
				enemy->Collision();
			}
		}
	}
}


void CollisionManager::CheckPlayerTileCollision(const std::weak_ptr<Actor::Player>& player,
												const std::vector<std::weak_ptr<TileLayer>>& collisionLayers) {
	std::shared_ptr<Actor::Player> sPlayer = player.lock();
	if (!sPlayer) {
		return;
	}
	for(const auto& layer : collisionLayers) {
		std::shared_ptr<TileLayer> sLayer = layer.lock();
		if (!sLayer) {
			return;
		}
		std::vector<std::vector<int32_t>> tiles{ sLayer->GetTileIds() };

		Vector2D layerPosition{ sLayer->GetPosition() };
		int32_t x{ static_cast<int32_t>(layerPosition.GetX()) / sLayer->GetTileSize() };
		int32_t y{ static_cast<int32_t>(layerPosition.GetY()) / sLayer->GetTileSize() };

		int32_t tileColumn, tileRow;
		int32_t tileId{ 0 };

		if(sPlayer->GetVeclocity().GetX() >= 0 || sPlayer->GetVeclocity().GetY() >= 0) {
			tileColumn = (sPlayer->GetPosition().GetX() + sPlayer->GetWidth()) / sLayer->GetTileSize();
			tileRow = (sPlayer->GetPosition().GetY() + sPlayer->GetHeight()) / sLayer->GetTileSize();
			tileId = tiles[tileRow + y][tileColumn +x];
		} else if(sPlayer->GetVeclocity().GetX() < 0 || sPlayer->GetVeclocity().GetY() < 0) {
			tileColumn = sPlayer->GetPosition().GetX() / sLayer->GetTileSize();
			tileRow = sPlayer->GetPosition().GetY() / sLayer->GetTileSize();
			tileId = tiles[tileRow + y][tileColumn +x];
		}

		if(0 != tileId) {
			sPlayer->Collision();
		}
	}
}

} // namespace Engine
