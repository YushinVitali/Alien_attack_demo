/// @file interface_object.cpp
/// @brief Description of the basic interface object.
#include <game_objects/interface/interface_object.hpp>

#include <game.hpp>
#include <texture_manager.hpp>

namespace Engine {

namespace Interface {

InterfaceObject::InterfaceObject()
	: Engine::GameObject() {}


void InterfaceObject::Draw() {
	Engine::TextureManager::Instance()->DrawFrame(m_textureId,
										  static_cast<int32_t>(m_position.GetX()),
										  static_cast<int32_t>(m_position.GetY()),
										  m_width, m_height,
										  m_currentRow, m_currentFrame,
										  Engine::Game::Instance()->GetRenderer(),
										  m_angle, m_alpha, SDL_FLIP_NONE);
}


void InterfaceObject::Update() {

}


void InterfaceObject::Clean() {

}


void InterfaceObject::Load(const Engine::LoaderParams& params) {
	GameObject::Load(params);
}



void InterfaceObject::Collision() {

}



std::string InterfaceObject::Type() const {
	return "InterfaceObject";
}

} // namespace Interface

} // namespace Engine
