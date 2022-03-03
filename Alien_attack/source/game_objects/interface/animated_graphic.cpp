/// @file animated_graphic.cpp
/// @brief Implementing of the animated interface graphics.
#include <game_objects/interface/animated_graphic.hpp>

#include <SDL.h>


namespace Engine {

namespace Interface {

AnimatedGraphic::AnimatedGraphic()
	: InterfaceObject() {}


void AnimatedGraphic::Draw() {
	InterfaceObject::Draw();
}


void AnimatedGraphic::Update() {
	m_currentFrame = static_cast<int32_t>(SDL_GetTicks() / (1000 / m_animSpeed) % m_frameCount);
}


void AnimatedGraphic::Clean() {
	InterfaceObject::Clean();
}


void AnimatedGraphic::Load(const Engine::LoaderParams &params) {
	InterfaceObject::Load(params);
	m_animSpeed = params.GetAnimSpeed();
}


std::string AnimatedGraphic::Type() const {
	return "AnimatedGraphic";
}

} // namespace Interface

} // namespace Engine
