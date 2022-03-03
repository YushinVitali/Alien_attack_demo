/// @file game.cpp
/// @brief Implementation of the main class of the game.
#include <game.hpp>

#include <unordered_map>

#include <SDL_image.h>

#include <logger.hpp>

#include <texture_manager.hpp>

#include <game_objects/actor/player.hpp>
#include <game_objects/actor/enemy.hpp>
#include <game_objects/interface/button.hpp>
#include <game_objects/interface/animated_graphic.hpp>
#include <game_objects/interface/text.hpp>

#include <game_objects/actor/alien_attack/eskeletor.hpp>
#include <game_objects/actor/alien_attack/glider.hpp>
#include <game_objects/actor/alien_attack/level_1_boss.hpp>
#include <game_objects/actor/alien_attack/roof_turret.hpp>
#include <game_objects/actor/alien_attack/shot_glider.hpp>
#include <game_objects/actor/alien_attack/turret.hpp>

#include <sound/sound_manager.hpp>

#include <game_objects/scrolling_background.hpp>

#include <controllers/input_handler.hpp>

#include <filemanager/filemanager.hpp>

#include <math/common.hpp>


namespace Engine {

Game* Game::m_instance = nullptr;


Game::Game()
{
	const std::vector<std::string> filenameLists{
		"alien_attack_level_1.tmx", "alien_attack_level_2.tmx"
	};
	for(const auto& filename : filenameLists) {
		auto pathFile{ Filemanager::Instance()->FindFile(filename) };
		if(pathFile) {
			m_levelFiles.emplace_back(pathFile.value());
		}
	}
}


Game* Game::Instance() {
	if(!m_instance) {
		m_instance = new Game();
	}
	return m_instance;
}


std::error_code Game::Initialization(const std::string& title,
									 int32_t xPos, int32_t yPos,
									 int32_t width, int32_t height,
									 bool fullscreen) {
	const int32_t flag = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		const std::error_code errorCode{ CoreError::SdlInitFailed };
		lerr(std::string{ SDL_GetError() }, errorCode);
		return errorCode;
	}
	lout(LOG_TYPE::INFO, "SDL init success.");

	m_windowSize = { width, height };

	m_window = SDL_CreateWindow(title.c_str(), xPos, yPos,
								m_windowSize.width, m_windowSize.height, flag);
	if(!m_window) {
		const std::error_code errorCode{ CoreError::WindowInitFailed };
		lerr(std::string{ SDL_GetError() }, errorCode);
		return errorCode;
	}
	lout(LOG_TYPE::INFO, "Window creation success.");

	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	if(!m_renderer) {
		const std::error_code errorCode{ CoreError::RendererInitFailed };
		lerr(std::string{ SDL_GetError() }, errorCode);
		return errorCode;
	}
	lout(LOG_TYPE::INFO, "Renderer creation success.");

	m_isRunning = true;
	lout(LOG_TYPE::INFO, "Init game success.");

	InputHandler::Instance()->InitialiseJoysticks();

	RegisterObjectTypes();

	LoadMusic();

	m_gameStateMachine = std::make_unique<GameStateMachine>();
	Game::Instance()->GetStateMachine()->ChangeState(StateId::Menu);

	return std::error_code{};
}


void Game::Render() {
	m_gameStateMachine->Render();

	SDL_RenderPresent(m_renderer);
}


void Game::Update() {
	m_gameStateMachine->Update();
}


void Game::HandleEvents() {
	InputHandler::Instance()->Update();
}


void Game::Clean() {
	lout(LOG_TYPE::INFO, "Clean game...");

	InputHandler::Instance()->Clean();

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);

	SDL_Quit();
}


void Game::Quit() {
	lout(LOG_TYPE::INFO, "Quit game...");
	m_isRunning = false;
}


void Game::ResetGame() {
	m_currentLevel = DEFAULT_LEVEL;
	m_nextLevel = m_currentLevel + 1;
	m_playerLives = DEFAULT_LIVES;
	m_isLevelComplete = false;
}


void Game::ResetLevel()
{
	m_playerLives = DEFAULT_LIVES;
	m_isLevelComplete = false;
}


void Game::RegisterObjectTypes() const {
	std::unordered_map<std::string, BaseCreator*> typeRegistrationTable {
		{ "AnimatedGraphic",     new Interface::AnimatedGraphicCreator() },
		{ "Button",              new Interface::ButtonCreator() },
		{ "Player",              new Actor::PlayerCreator() },
		{ "ScrollingBackground", new ScrollBackgroundCreator() },
		{ "Turret",              new AlienAttack::Actor::TurretCreator() },
		{ "RoofTurret",          new AlienAttack::Actor::RoofTurretCreator() },
		{ "Glider",              new AlienAttack::Actor::GliderCreator() },
		{ "ShotGlider",          new AlienAttack::Actor::ShotGliderCreator() },
		{ "Level1Boss",          new AlienAttack::Actor::Level1BossCreator() },
		{ "Eskeletor",           new AlienAttack::Actor::EskeletorCreator() },
		{ "Text",                new Interface::TextCreator() }
	};

	for(auto& objectType : typeRegistrationTable) {
		GameObjectFactory::Instance()->RegisterType(objectType.first, objectType.second);
	}
}


std::vector<std::string> Game::GetLevelFiles() const {
	return m_levelFiles;
}


SDL_Renderer* Game::GetRenderer() const {
	return m_renderer;
}


SDL_Window* Game::GetWindow() const {
	return m_window;
}


RectangleSize Game::GetWindowSize() const noexcept {
	return m_windowSize;
}


void Game::SetScrollSpeed(float scrollSpeed) {
	m_scrollSpeed = scrollSpeed;
}


float Game::GetScrollSpeed() const noexcept {
	return m_scrollSpeed;
}


const std::unique_ptr<GameStateMachine>& Game::GetStateMachine() {
	return m_gameStateMachine;
}


void Game::SetCurrentLevel(size_t currentLevel) {
	if(!IsValueInRange<size_t>(currentLevel, 0, m_levelFiles.size())) {
		return;
	}

	if(m_levelFiles.size() == currentLevel) {
		m_currentLevel = DEFAULT_LEVEL;
		m_isLevelComplete = false;
		m_gameStateMachine->ChangeState(StateId::GameWinning);
		return;
	}

	m_currentLevel = currentLevel;
	m_gameStateMachine->ChangeState(StateId::BetweenLevel);
	m_isLevelComplete = false;
}


size_t Game::GetCurrentLevel() const noexcept {
	return m_currentLevel;
}


size_t Game::GetNumberLevel() const noexcept {
	return m_levelFiles.size();
}


void Game::SetNextLevel(size_t nextLevel) {
	m_nextLevel = nextLevel;
}


size_t Game::GetNextLevel() const noexcept {
	return m_nextLevel;
}


void Game::SetPlayerLives(size_t playerLives) {
	m_playerLives = playerLives;
}


size_t Game::GetPlayerLives() const noexcept {
	return m_playerLives;
}


bool Game::IsRunning() const noexcept {
	return m_isRunning;
}


void Game::SetLevelComplete(bool isLevelComplete) {
	m_isLevelComplete = isLevelComplete;
}


bool Game::IsLevelComplete() const noexcept {
	return m_isLevelComplete;
}


void Game::SetChangingState(bool isChangingState) {
	m_isChangingState = isChangingState;
}


bool Game::IsChangingState() const noexcept {
	return m_isChangingState;
}


void Game::SetWindowSize(const RectangleSize& windowSize) {
	m_windowSize = windowSize;
}

void Game::LoadMusic() {
	const std::unordered_map<
			std::string,
			std::pair<SoundType, std::string>> soundTable{
		{ "gameMusic",     { SoundType::Music, "DST_ElectroRock.ogg" } },
		{ "announceMusic", { SoundType::Music, "DST_Announce.ogg" } },
		{ "explode",       { SoundType::Sfx, "boom.wav" } },
		{ "shoot",         { SoundType::Sfx, "phaser.wav" } }
	};
	for(const auto& sound : soundTable) {
		const auto filename{ sound.second.second };
		const auto filePath{ Filemanager::Instance()->FindFile(filename) };
		if(!filePath) {
			lout(LOG_TYPE::WARNING, filename + " audio file not found!");
			continue;
		}

		const auto id{ sound.first };
		const auto type{ sound.second.first };
		SoundManager::Instance()->Load(filePath.value(), id, type);
	}
}

} // namespace Engine
