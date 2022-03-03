/// @file turret.hpp
/// @brief Description of the actor of turret.
#pragma once

#ifndef __TURRET_HPP__
#define __TURRET_HPP__


#include <game_objects/game_object.hpp>
#include <game_objects/game_object_factory.hpp>
#include <game_objects/actor/enemy.hpp>


namespace AlienAttack {

namespace Actor {

/// @brief Turret actor.
class Turret : public Engine::Actor::Enemy {
public:
	Turret();
	virtual ~Turret() override = default;

	virtual void Update() override;

	virtual void Collision() override;
}; // class Turret


class TurretCreator : public Engine::BaseCreator {
	virtual Engine::GameObject* CreateGameObject() const override {
		return new Turret();
	}
}; // class TurretCreator

} // namespace Actor

} // namespace AlienAttack


#endif // !defined(__TURRET_HPP__)
