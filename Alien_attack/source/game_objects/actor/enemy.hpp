/// @file enemy.hpp
/// @brief Description of the base actor of the enemy.
#pragma once

#ifndef __ENEMY_HPP__
#define __ENEMY_HPP__


#include <SDL.h>

#include <loader_params.hpp>
#include <game_objects/actor/shooter_object.hpp>
#include <game_objects/game_object_factory.hpp>


namespace Engine {

namespace Actor {

/// @brief Enemy actor.
class Enemy : public ShooterObject {
public:
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	virtual void Load(const LoaderParams& params) override;

	virtual std::string Type() const override final;

protected:
	Enemy();
	virtual ~Enemy() override = default;

protected:
	int32_t m_health;
}; // class Enemy

} // namespace Actor

} // namespace Engine


#endif // !defined(__ENEMY_HPP__)
