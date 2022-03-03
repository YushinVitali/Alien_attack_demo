/// @file actor_object.cpp
/// @brief Implementation of the base actor.
#include <game_objects/actor/actor_object.hpp>

#include <game.hpp>
#include <texture_manager.hpp>


namespace Engine {

namespace Actor {

ActorObject::ActorObject()
	: GameObject() {}


void ActorObject::Draw() {
	const SDL_RendererFlip flip{
		(0 < m_velocity.GetX()) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
	};

	TextureManager::Instance()->DrawFrame(m_textureId,
										  static_cast<int32_t>(m_position.GetX()),
										  static_cast<int32_t>(m_position.GetY()),
										  m_width, m_height,
										  m_currentRow, m_currentFrame,
										  Game::Instance()->GetRenderer(),
										  m_angle, m_alpha, flip);
}


void ActorObject::Update() {
	// Probably not all actors move, there are also static ones!
	m_velocity += m_acceleration;
	m_position += m_velocity;
}


void ActorObject::Clean() {

}


void ActorObject::Load(const LoaderParams& params) {
	GameObject::Load(params);
}


void ActorObject::Collision() {

}


std::string  ActorObject::Type() const {
	return "ActorObject";
}

} // namespace Actor

} // namespace Engine
