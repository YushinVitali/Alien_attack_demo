/// @file game_state_machine.cpp
/// @brief Implementing of the game state management system.
#include <game_states/game_state_machine.hpp>

#include <logger.hpp>

#include <game_states/game_state_error_code.hpp>

#include <game_states/main_menu_state.hpp>
#include <game_states/play_state.hpp>
#include <game_states/pause_state.hpp>
#include <game_states/game_over_state.hpp>
#include <game_states/between_level_state.hpp>
#include <game_states/game_winning_state.hpp>


namespace Engine {

GameStateMachine::~GameStateMachine() {
	CleanStatesApplicantsForDeletion();
	while(!m_gameStates.empty()) {
		m_gameStates.top()->OnExit();
		m_gameStates.pop();
	}
}


void GameStateMachine::Update() {
	if(m_gameStates.empty()) {
		loutd("Attempting to update game state when the state stack is empty!");
		return;
	}

	m_gameStates.top()->Update();
}


void GameStateMachine::Render() {
	if(m_gameStates.empty()) {
		loutd("Attempting to render game state when the state stack is empty!");
		return;
	}

	m_gameStates.top()->Render();
}


std::error_code GameStateMachine::PushState(StateId stateId) {
	std::unique_ptr<GameState> state{ CreateState(stateId) };
	if(!state) {
		return std::error_code{};
	}

	CleanStatesApplicantsForDeletion();

	if(!state->OnEnter()) {
		const std::error_code errorCode{ GameStateError::StateEnterFailed };
		lerr("Game state change to" + ToString(stateId) + " failed!", errorCode);
		return errorCode;
	}

	m_gameStates.push(std::move(state));
	return std::error_code{};
}


std::error_code GameStateMachine::ChangeState(StateId stateId) {
	std::unique_ptr<GameState> state{ CreateState(stateId) };
	if(!state) {
		return std::error_code{};
	}

	CleanStatesApplicantsForDeletion();

	if(!m_gameStates.empty()) {
		if(m_gameStates.top()->GetStateId() == state->GetStateId() && state->GetStateId() != StateId::Play) {
			loutd("There was an attempt to change the game state to an identical one!");
			return std::error_code{};
		}

		while(!m_gameStates.empty()) {
			if(m_gameStates.top()->OnExit()) {
				m_queueDeleteStates.push(std::move(m_gameStates.top()));
				m_gameStates.pop();
			}
		}
	}

	if(!state->OnEnter()) {
		const std::error_code errorCode{ GameStateError::StateEnterFailed };
		lerr("Game state change to" + ToString(stateId) + " failed!", errorCode);
		return errorCode;
	}

	m_gameStates.push(std::move(state));
	return std::error_code{};
}


std::error_code GameStateMachine::PopState() {
	CleanStatesApplicantsForDeletion();

	if(m_gameStates.empty()) {
		const std::error_code errorCode{ GameStateError::StateStackIsEmpty };
		lerr("There was an error when deleting the state!", errorCode);
		return errorCode;
	}

	if(m_gameStates.top()->OnExit()) {
		m_queueDeleteStates.push(std::move(m_gameStates.top()));
		m_gameStates.pop();
	}

	return std::error_code{};
}


GameState* GameStateMachine::CreateState(StateId state) const {
	switch(state) {
		case StateId::Menu:
			return new MainMenuState();
		case StateId::Play:
			return new PlayState();
		case StateId::Pause:
			return new PauseState();
		case StateId::GameOver:
			return new GameOverState();
		case StateId::BetweenLevel:
			return new BetweenLevelState();
		case StateId::GameWinning:
			return new GameWinningState();

		default:
			return nullptr;
	}
}


void GameStateMachine::CleanStatesApplicantsForDeletion() {
	while(!m_queueDeleteStates.empty()) {
		m_queueDeleteStates.front()->OnExit();
		m_queueDeleteStates.pop();
	}
}

} // namespace Engine
