/// @file game_state.hpp
/// @brief Description of the basic game state.
#pragma once

#ifndef __GAME_STATE_HPP__
#define __GAME_STATE_HPP__


#include <string>
#include <vector>
#include <system_error>
#include <memory>

#include <game_objects/game_object.hpp>


namespace Engine {

/// @brief Lists the game states.
enum class StateId {
	None			= 0,
	Menu			= 1,
	Play			= 2,
	Pause			= 3,
	GameOver		= 4,
	BetweenLevel	= 5,
	GameWinning		= 6
}; // enum class StateId


/// @brief Basic description of the game state.
class GameState {
public:
	GameState() = default;
	virtual ~GameState() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;

	virtual void Resume();

	virtual bool OnEnter() = 0;
	virtual bool OnExit() = 0;

	StateId GetStateId() const;

protected:
	virtual std::error_code LoadObjects(const std::vector<std::pair<std::string, std::string>>& infoOfObjects);
	virtual bool LoadState(const std::string& fileState);
	virtual bool LoadStories(const std::string& fileStories);

protected:
	std::vector<std::string> m_textureIdList;
	std::vector<std::unique_ptr<GameObject>> m_gameObjects;

	StateId m_stateId{ StateId::None };

	bool m_isLoadingComplete{ false };
	bool m_isExiting{ false };
}; // class GameState


std::string ToString(StateId stateId);

void UpdateObjects(std::vector<std::unique_ptr<GameObject>>& objects);
void RenderObjects(std::vector<std::unique_ptr<GameObject>>& objects);
void CleanObjects(std::vector<std::unique_ptr<GameObject>>& objects);

} // namespace Engine

#endif // !defined(__GAME_STATE_HPP__)
