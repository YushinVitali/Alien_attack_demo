/// @file collision_manager.hpp
/// @brief Description of the collision handling system.
#pragma once

#ifndef __COLLISION_MANAGER_HPP__
#define __COLLISION_MANAGER_HPP__


#include <vector>
#include <memory>

#include <game_objects/actor/player.hpp>


namespace Engine {

class GameObject;
class TileLayer;

/// @brief Collision handling system.
class CollisionManager {
public:
	void CheckPlayerEnemyBulletCollision(const std::weak_ptr<Actor::Player>& player);
	void CheckPlayerEnemyCollision(const std::weak_ptr<Actor::Player>& player,
								   const std::vector<std::shared_ptr<GameObject>>& enemies);
	void CheckEnemyPlayerBulletCollision(const std::vector<std::shared_ptr<GameObject>>& objects);
	void CheckPlayerTileCollision(const std::weak_ptr<Actor::Player>& player,
								  const std::vector<std::weak_ptr<TileLayer>>& collisionLayers);
}; // class CollisionManager

} // namespace Engine


#endif // !defined(__COLLISION_MANAGER_HPP)
