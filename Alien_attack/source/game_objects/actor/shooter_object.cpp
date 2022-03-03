/// @file shooter_object.cpp
/// @brief Implementation of a basic actor with the ability to shoot.
#include <game_objects/actor/shooter_object.hpp>

#include <algorithm>

#include <SDL.h>

#include <texture_manager.hpp>
#include <game.hpp>


namespace Engine {

namespace Actor {

ShooterObject::ShooterObject()
	: ActorObject() {}


void ShooterObject::Draw() {
	ActorObject::Draw();
}


void ShooterObject::Update() {
	ActorObject::Update();
}


void ShooterObject::Clean() {

}


void ShooterObject::Collision() {

}


std::string ShooterObject::Type() const {
	return "ShooterObject";
}


void ShooterObject::Load(const LoaderParams &params) {
	ActorObject::Load(params);
}


void ShooterObject::DoDyingAnimation() {
	Scroll(Game::Instance()->GetScrollSpeed());

	m_currentFrame = static_cast<int32_t>((SDL_GetTicks() / (1000 / 3)) % m_frameCount);

	if(m_dyingCounter == m_dyingTime) {
		m_isDead = true;
	}
	++m_dyingCounter;
}

} // namespace Actor

} // namespace Engine
