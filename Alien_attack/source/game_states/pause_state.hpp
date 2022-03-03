/// @file pause_state.hpp
/// @brief Description of the pause state of game.
#pragma once

#ifndef __PAUSE_STATE_HPP__
#define __PAUSE_STATE_HPP__


#include <game_states/menu_state.hpp>


namespace Engine {

/// @brief Pause state of game.
class PauseState : public MenuState {
public:
	PauseState() {
		m_stateId = StateId::Pause;
	};
	virtual ~PauseState() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void Clean() override;

	virtual bool OnEnter() override;
	virtual bool OnExit() override;

private:
	static void OnClickButtonMenu();
	static void OnClickButtonResume();

private:
	bool m_isRender{ false };
}; // class PauseState

} // namespace Engine


#endif // !defined(__PAUSE_STATE_HPP__)
