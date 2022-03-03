/// @file bullet.hpp
/// @brief Description of the bullet actor.
#pragma once

#ifndef __BULLET_HPP__
#define __BULLET_HPP__


#include <game_objects/actor/shooter_object.hpp>


namespace Engine {

namespace Actor {

/// @brief Player bullet actor.
class PlayerBullet : public ShooterObject {
public:
	PlayerBullet();
	virtual ~PlayerBullet() override = default;

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Clean() override;

	virtual void Load(const LoaderParams& params, Vector2D heading);

	virtual void Collision() override;

	virtual std::string Type() const override;

private:
	virtual void Load(const LoaderParams& params) override {};

private:
	Vector2D m_heading;
}; // class PlayerBullet


/// @brief Enemy bullet actor.
class EnemyBullet : public PlayerBullet {
public:
	EnemyBullet();

	virtual ~EnemyBullet() override = default;

	virtual std::string Type() const override;
}; // class EnemyBullet

} // namespace Actor

} // namespace Engine


#endif // !defined(__BULLET_HPP__)
