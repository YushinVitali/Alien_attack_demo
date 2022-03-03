/// @file button.cpp
/// @brief Implementing of the interface button.
#include <game_objects/interface/button.hpp>

#include <math/vector_2d.hpp>

#include <controllers/input_handler.hpp>


namespace Engine {

namespace Interface {

namespace { // anonymous namespace

/// @brief Possible states for button object.
enum class ButtonState {
	Unselected	= 0,
	Selected	= 1,
	Pressed		= 2
}; // enum class ButtonState

} // anonymous namespace


Button::Button()
	: InterfaceObject() {
	m_currentFrame = static_cast<int32_t>(ButtonState::Unselected);
}


void Button::Draw() {
	InterfaceObject::Draw();
}


void Button::Update() {
	SDL_Point mousePosition{
		Engine::InputHandler::Instance()->GetMousePosition() };
	SDL_Rect rectButton{ GetRect() };

	if(!SDL_PointInRect(&mousePosition, &rectButton)) {
		m_currentFrame = static_cast<int32_t>(ButtonState::Unselected);
	} else {
		const bool isButtonClicked{
			Engine::InputHandler::Instance()->IsMouseButtonPush(SDL_BUTTON_LEFT) };
		if(m_isReleased && isButtonClicked) {
			m_currentFrame = static_cast<int32_t>(ButtonState::Pressed);
			m_OnClick();
			m_isReleased = false;
		} else if(!isButtonClicked) {
			m_isReleased = true;
			m_currentFrame = static_cast<int32_t>(ButtonState::Selected);
		}
	}
}


void Button::Clean() {
	InterfaceObject::Clean();
}


void Button::Load(const Engine::LoaderParams &params) {
	InterfaceObject::Load(params);
	m_callbackId = params.GetCallbackId();
}


std::string Button::Type() const {
	return "Button";
}


void Button::SetCallback(void (*callback)()) {
	m_OnClick = callback;
}


int32_t Button::GetCallbackId() {
	return m_callbackId;
}

} // namespace Interface

} // namespace Engine
