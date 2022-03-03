/// @file text.cpp
/// @brief Implementing of the text object.
#include <game_objects/interface/text.hpp>

#include <SDL.h>


namespace Engine {

namespace Interface {

Text::Text()
	: InterfaceObject() {}


void Text::Draw() {
	InterfaceObject::Draw();
}


void Text::Update() {

}


void Text::Clean() {
	InterfaceObject::Clean();
}


void Text::Load(const Engine::LoaderParams &params) {
	InterfaceObject::Load(params);
}


std::string Text::Type() const {
	return "Text";
}

} // namespace Interface

} // namespace Engine
