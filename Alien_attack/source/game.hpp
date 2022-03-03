/// @file game.hpp
/// @brief Description of the main class of the game.
#pragma once

#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <vector>
#include <memory>

#include <SDL.h>

#include <engine_error_code.hpp>
#include <event_filter.hpp>

#include <game_objects/game_object_factory.hpp>

#include <game_states/game_state_machine.hpp>

#include <common/common.hpp>
#include <common/game_constants.hpp>


namespace Engine {

/// @brief Heart of the engine and the game.
class Game {
public:
	~Game() = default;

	static Game* Instance();

	std::error_code Initialization(const std::string& title,
								   int32_t xPos, int32_t yPos,
								   int32_t width, int32_t height,
								   bool fullscreen);

	void Render();
	void Update();
	void HandleEvents();
	void Clean();
	void Quit();

	void ResetGame();
	void ResetLevel();

	void LoadTextures() const;

	std::vector<std::string> GetLevelFiles() const;

	SDL_Renderer* GetRenderer() const;

	SDL_Window* GetWindow() const;
	RectangleSize GetWindowSize() const noexcept;

	void SetScrollSpeed(float scrollSpeed);
	float GetScrollSpeed() const noexcept;

	const std::unique_ptr<GameStateMachine>& GetStateMachine();

	void SetCurrentLevel(size_t currentLevel);
	size_t GetCurrentLevel() const noexcept;
	size_t GetNumberLevel() const noexcept;

	void SetNextLevel(size_t nextLevel);
	size_t GetNextLevel() const noexcept;

	void SetPlayerLives(size_t playerLives);
	size_t GetPlayerLives() const noexcept;

	bool IsRunning() const noexcept;

	void SetLevelComplete(bool isLevelComplete);
	bool IsLevelComplete() const noexcept;

	void SetChangingState(bool isChangingState);
	bool IsChangingState() const noexcept;

private:
	friend class EventFilter;

	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void SetWindowSize(const RectangleSize& windowSize);

	void LoadMusic();

	/// @brief Register the types of game objects.
	void RegisterObjectTypes() const;

private:
	static Game* m_instance;

	std::vector<std::string> m_levelFiles;

	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };

	std::unique_ptr<GameStateMachine> m_gameStateMachine{ nullptr };

	RectangleSize m_windowSize;

	float m_scrollSpeed{ DEFAULT_SCROLL_SPEED };

	size_t m_currentLevel{ DEFAULT_LEVEL };
	size_t m_nextLevel{ m_currentLevel + 1 };

	size_t m_playerLives{ DEFAULT_LIVES };

	bool m_isRunning{ false };
	bool m_isChangingState{ false };
	bool m_isLevelComplete{ false };
}; // class Game

} // namespace Engine


#endif // !defined(__GAME_HPP__)
