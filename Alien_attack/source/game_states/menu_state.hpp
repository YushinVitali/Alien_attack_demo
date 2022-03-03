/// @file menu_state.hpp
/// @brief Description of the base menu state.
#pragma once

#ifndef __MENU_STATE_HPP__
#define __MENU_STATE_HPP__


#include <vector>

#include <game_states/game_state.hpp>


namespace Engine {

/// @brief Base menu state of game.
class MenuState : public GameState {
public:
	virtual ~MenuState() override = default;

protected:
	typedef void(*Callback)();

	virtual void SetCallbacks(const std::vector<Callback>& callbacks);

protected:
	std::vector<Callback> m_callbacks;
}; // class MenuState

} // namespace Engine


#endif // !defined(__MENU_STATE_HPP__)
