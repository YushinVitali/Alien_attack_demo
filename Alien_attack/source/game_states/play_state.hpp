/// @file play_state.hpp
/// @brief Description of the state of game process.
#pragma once

#ifndef __PLAY_STATE_HPP__
#define __PLAY_STATE_HPP__


#include <memory>

#include <game_states/game_state.hpp>

#include <level/level.hpp>

#include <collision/collision_manager.hpp>


namespace Engine {

/// @brief State of game process.
class PlayState : public GameState {
public:
	PlayState() {
		m_stateId = StateId::Play;
	}
	virtual ~PlayState() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void Clean() override;

	virtual bool OnEnter() override;
	virtual bool OnExit() override;

private:
	std::unique_ptr<Level> BuildLevel();

private:
	CollisionManager m_collisionManager;

	std::unique_ptr<Level> level{ nullptr };
}; // class PlayState

} // namespace Engine


#endif // !defined(__PLAY_STATE_HPP__)
