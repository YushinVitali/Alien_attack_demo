/// @file game_over_state.hpp
/// @brief Description of the state of loss in the game.
#pragma once

#ifndef __GAME_OVER_STATE_HPP__
#define __GAME_OVER_STATE_HPP__


#include <system_error>
#include <string>
#include <vector>

#include <game_states/menu_state.hpp>

#include <game_objects/game_object.hpp>


namespace Engine {

/// @brief Losing states in the game.
class GameOverState : public MenuState {
public:
	GameOverState() {
		m_stateId = StateId::GameOver;
	}
	virtual ~GameOverState() override;

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
}; // class GameOverState

} // namespace Engine

#endif // !defined(__GAME_OVER_STATE_HPP__)
