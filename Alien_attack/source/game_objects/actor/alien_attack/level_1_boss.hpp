/// @file level_1_boss.hpp
/// @brief Description of the actor of level boss.
#pragma once

#ifndef __LEVEL_1_BOSS_HPP__
#define __LEVEL_1_BOSS_HPP__


#include <game_objects/game_object.hpp>
#include <game_objects/game_object_factory.hpp>
#include <game_objects/actor/enemy.hpp>


namespace AlienAttack {

namespace Actor {

/// @brief Level boss actor.
class Level1Boss : public Engine::Actor::Enemy {
public:
	Level1Boss();
	virtual ~Level1Boss() override = default;

	virtual void Update() override;

	virtual void Load(const Engine::LoaderParams& params) override;

	virtual void Collision() override;

private:
	bool m_isEntered;
}; // class Level1Boss


class Level1BossCreator : public Engine::BaseCreator {
	virtual Engine::GameObject* CreateGameObject() const override {
		return new Level1Boss();
	}
};

} // namespace Actor

} // AlienAttack


#endif // !defined(__LEVEL_1_BOSS_HPP__)
