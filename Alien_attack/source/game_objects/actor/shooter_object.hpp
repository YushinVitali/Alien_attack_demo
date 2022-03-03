/// @file shooter_object.hpp
/// @file Description of a basic actor with the ability to shoot.
#pragma once

#ifndef __SDL_GAME_OBJECT_HPP__
#define __SDL_GAME_OBJECT_HPP__


#include <loader_params.hpp>

#include <game_objects/actor/actor_object.hpp>

#include <math/vector_2d.hpp>


namespace Engine {

namespace Actor {

/// @brief Basic actor with the ability to shoot.
class ShooterObject: public ActorObject {
public:
	virtual ~ShooterObject() override = default;

	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	virtual void Load(const LoaderParams& params) override;

	virtual void Collision() override;

	virtual std::string Type() const override;

protected:
	ShooterObject();

	void DoDyingAnimation();

protected:
	int32_t m_bulletFiringSpeed{ 0 };
	int32_t m_bulletCounter{ 0 };

	int32_t m_moveSpeed{ 0 };

	int32_t m_dyingTime{ 0 };
	int32_t m_dyingCounter{ 0 };

	bool m_isPlayedDeathSound{ false };
}; // class SdlGameObject

} // namespace Actor

} // namespace Engine


#endif // !defined(__SDL_GAME_OBJECT_HPP__)
