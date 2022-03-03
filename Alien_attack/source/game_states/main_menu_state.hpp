/// @file main_menu_state.hpp
/// @brief Description of the main menu state of game.
#pragma once

#ifndef __MAIN_MENU_STATE_HPP__
#define __MAIN_MENU_STATE_HPP__


#include <game_states/menu_state.hpp>


namespace Engine {

/// @brief  Main menu state of game.
class MainMenuState : public MenuState {
public:
	MainMenuState() {
		m_stateId =  StateId::Menu;
	}
	virtual ~MainMenuState() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void Clean() override;

	virtual bool OnEnter() override;
	virtual bool OnExit() override;

private:
	virtual void SetCallbacks(const std::vector<Callback>& callbacks) override;

	static void OnClickButtonPlay();
	static void OnClickButtonExit();
}; // class MainMenuState

} // namespace Engine


#endif // !defined(__MAIN_MENU_STATE_HPP__)
