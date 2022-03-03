/// @file shot_glider.hpp
/// @brief Description of the actor of shoot glider.
#pragma once

#ifndef __SHOT_GLIDER_HPP__
#define __SHOT_GLIDER_HPP__


#include <game_objects/actor/alien_attack/glider.hpp>


namespace AlienAttack {

namespace Actor {

/// @brief Shot glider actor.
class ShotGlider : public Glider {
public:
	ShotGlider();
	virtual ~ShotGlider() override = default;

	virtual void Update() override;
	virtual void Load(const Engine::LoaderParams& params) override;
}; // class ShotGlider


class ShotGliderCreator : public Engine::BaseCreator {
	virtual Engine::GameObject* CreateGameObject() const override {
		return new ShotGlider();
	}
}; // class ShotGliderCreator


} // namespace Actor

} // namespace AlienAttack


#endif // !defined(__SHOT_GLIDER_HPP__)
