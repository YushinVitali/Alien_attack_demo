/// @file game_winning_state.hpp
/// @brief Description of the state of winning game.
#pragma once

#ifndef __GAME_WINNING_STATE_HPP__
#define __GAME_WINNING_STATE_HPP__


#include <game_states/menu_state.hpp>


namespace Engine {

/// @brief Game winning state of game.
class GameWinningState : public MenuState {
public:
	GameWinningState() {
		m_stateId = StateId::GameWinning;
	}
	virtual ~GameWinningState() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void Clean() override;

	virtual bool OnEnter() override;
	virtual bool OnExit() override;

protected:
	virtual bool LoadStories(const std::string& fileStories) override;

private:
	static void OnClickButtonMenu();
}; // class BetweenPlayState

} // namespace Engine


#endif // !defined (__GAME_WINNING_STATE_HPP__)
