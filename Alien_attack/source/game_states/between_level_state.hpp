/// @file between_level_state.hpp
/// @brief Description of the interlevel state of game.
#pragma once

#ifndef __BETWEEN_LEVEL_STATE_HPP__
#define __BETWEEN_LEVEL_STATE_HPP__


#include <vector>

#include <game_states/menu_state.hpp>

#include <game_objects/game_object.hpp>


namespace Engine {

/// @brief Interlevel game states.
class BetweenLevelState : public MenuState {
public:
	BetweenLevelState(){
		m_stateId = StateId::BetweenLevel;
	}
	virtual ~BetweenLevelState() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void Clean() override;

	virtual bool OnEnter() override;
	virtual bool OnExit() override;

private:
	static void OnClickButtonNext();
}; // class BetweenPlayState

} // namespace Engine


#endif // !defined (__BETWEEN_LEVEL_STATE_HPP__)
