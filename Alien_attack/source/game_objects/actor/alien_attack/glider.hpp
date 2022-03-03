/// @file glider.hpp
/// @brief /// @brief Description of the actor of glider.
#pragma once

#ifndef __GLIDER_HPP__
#define __GLIDER_HPP__


#include <game_objects/game_object.hpp>
#include <game_objects/game_object_factory.hpp>
#include <game_objects/actor/enemy.hpp>


namespace AlienAttack {

namespace Actor {

/// @brief Glider actor.
class Glider : public Engine::Actor::Enemy {
public:
	Glider();
	virtual ~Glider() override = default;

	virtual void Update() override;

	virtual void Load(const Engine::LoaderParams& params) override;

	virtual void Collision() override;

private:
	int32_t m_maxHeight;
	int32_t m_minHeight;

	int32_t m_gap;
}; // class Glider


class GliderCreator : public Engine::BaseCreator {
	virtual Engine::GameObject* CreateGameObject() const override {
		return new Glider();
	}
};

} // namespace Actor

} // namespace AlienAttack


#endif // !defined(__GLIDER_HPP__)
