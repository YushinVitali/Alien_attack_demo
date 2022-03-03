/// @file roof_turret.hpp
/// @brief Description of the actor of roof turret.
#pragma once

#ifndef __ROOF_TURRET_HPP__
#define __ROOF_TURRET_HPP__


#include <game_objects/game_object.hpp>
#include <game_objects/game_object_factory.hpp>

#include <game_objects/actor/alien_attack/turret.hpp>


namespace AlienAttack {

namespace Actor {

/// @brief Roof turret actor.
class RoofTurret : public Turret {
public:
	RoofTurret() = default;
	virtual ~RoofTurret() override = default;

	virtual void Update() override;
	virtual void Draw() override;
}; // class RoofTurret


/// @brief
class RoofTurretCreator : public Engine::BaseCreator {
	virtual Engine::GameObject* CreateGameObject() const override {
		return new RoofTurret();
	}
};


} // namespace Actor

} // namespace AlienAttack


#endif // !defined(__ROOF_TURRET_HPP__)
