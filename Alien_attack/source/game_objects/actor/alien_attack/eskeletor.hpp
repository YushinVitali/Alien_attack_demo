/// @file eskeletor.hpp
/// @brief Description of the actor of eskeletor.
#pragma once

#ifndef __ESKELETOR_HPP__
#define __ESKELETOR_HPP__


#include <game_objects/game_object.hpp>
#include <game_objects/game_object_factory.hpp>
#include <game_objects/actor/enemy.hpp>


namespace AlienAttack {

namespace Actor {

/// @brief Eskeletor actor.
class Eskeletor : public Engine::Actor::Enemy {
public:
	Eskeletor();
	virtual ~Eskeletor() = default;

	virtual void Update() override;

	virtual void Collision() override;
}; // class Eskeletor


class EskeletorCreator : public Engine::BaseCreator {
	virtual Engine::GameObject* CreateGameObject() const override {
		return new Eskeletor();
	}
};

} // namespace Actor

} // AlienAttack


#endif // !defined(__ESKELETOR_HPP__)
