/// @file menu_state.hpp
/// @brief Implementation of the base menu state.
#include <game_states/menu_state.hpp>

#include <game_objects/interface/button.hpp>


namespace Engine {

void MenuState::SetCallbacks(const std::vector<Callback>& callbacks) {
	for(auto& object : m_gameObjects) {
		const auto button{ dynamic_cast<Interface::Button*>(object.get()) };
		if(button) {
			button->SetCallback(callbacks[button->GetCallbackId()]);
		}
	}
}

} // namespace Engine
