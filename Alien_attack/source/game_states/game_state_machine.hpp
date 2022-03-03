/// @file game_state_machine.hpp
/// @brief Description of the game state management system.
#pragma once

#ifndef __GAME_STATE_MACHINE_HPP__
#define __GAME_STATE_MACHINE_HPP__


#include <stack>
#include <queue>
#include <system_error>
#include <memory>

#include <game_states/game_state.hpp>


namespace Engine {

/// @brief Game state management system.
class GameStateMachine {
public:
	GameStateMachine() = default;
	~GameStateMachine();

	void Update();
	void Render();

	std::error_code PushState(StateId state);
	std::error_code ChangeState(StateId state);
	std::error_code PopState();

private:
	GameState* CreateState(StateId state) const;
	void CleanStatesApplicantsForDeletion();

private:
	std::stack<std::unique_ptr<GameState>> m_gameStates;

	std::queue<std::unique_ptr<GameState>> m_queueDeleteStates;
}; // class GameStateMachine

} // namespace Engine


#endif // !defined(__GAME_STATE_MACHINE_HPP__)
