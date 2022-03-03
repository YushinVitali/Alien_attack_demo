/// @file bullet_hanler.hpp
/// @brief Description of the bullet actor processing system.
#pragma once

#ifndef __BULLET_HANDLER_HPP__
#define __BULLET_HANDLER_HPP__


#include <cstdint>
#include <vector>
#include <memory>

#include <math/vector_2d.hpp>

#include <game_objects/actor/bullet.hpp>


namespace Engine {

namespace Actor {

/// @brief Bullet actor processing system
class BulletHandler {
public:
	~BulletHandler() = default;

	static BulletHandler* Instance();

	void UpdateBullets();
	void DrawBullets();
	void ClearBullets();

	void AddPlayerBullet(int32_t x, int32_t y,
						 int32_t width, int32_t height,
						 const std::string& textureId,
						 int32_t frameCount, Vector2D heading);
	void AddEnemyBullet(int32_t x, int32_t y,
						int32_t width, int32_t height,
						const std::string& textureId,
						int32_t frameCount, Vector2D heading);
public:
	const std::vector<std::unique_ptr<PlayerBullet>>& GetPlayerBullets() const;
	const std::vector<std::unique_ptr<EnemyBullet>>& GetEnemyBullets() const;

private:
	BulletHandler() = default;
	BulletHandler(const BulletHandler&) = default;
	BulletHandler& operator=(const BulletHandler&) = default;

private:
	static BulletHandler* m_instance;

	std::vector<std::unique_ptr<PlayerBullet>> m_playerBullets;
	std::vector<std::unique_ptr<EnemyBullet>> m_enemyBullets;
}; // class BulletHandler

} // namespace Actor

} // namespace Engine


#endif // !defined(__BULLET_HANDLER_HPP__)
