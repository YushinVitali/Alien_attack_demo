/// @file play_state.cpp
/// @brief Implementation of the state of game process.
#include <game_states/play_state.hpp>

#include <logger.hpp>

#include <game.hpp>
#include <texture_manager.hpp>

#include <controllers/input_handler.hpp>

#include <parser/level_parser.hpp>

#include <level/level.hpp>

#include <filemanager/filemanager.hpp>

#include <game_objects/actor/bullet_handler.hpp>

#include <sound/sound_manager.hpp>


namespace Engine {

PlayState::~PlayState() {
	PlayState::Clean();
}


void PlayState::Update() {
	if(m_isLoadingComplete && !m_isExiting) {
		if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE)) {
			Game::Instance()->GetStateMachine()->PushState(StateId::Pause);
		}

		Actor::BulletHandler::Instance()->UpdateBullets();

		if(0 == Game::Instance()->GetPlayerLives()) {
			Game::Instance()->GetStateMachine()->ChangeState(StateId::GameOver);
		}

		if(level) {
			level->Update();
		}
	}
}


void PlayState::Render() {
	SDL_RenderClear(Game::Instance()->GetRenderer());

	if(m_isLoadingComplete) {
		if(level) {
			level->Render();
		}

		for(size_t i = 0; i < Game::Instance()->GetPlayerLives(); ++i) {
			TextureManager::Instance()->DrawFrame("lives", i * 30, 0, 32, 30, 0, 0,
												  Game::Instance()->GetRenderer(), 0.0, 255);
		}

		Actor::BulletHandler::Instance()->DrawBullets();
	}
}


void PlayState::Clean() {
	loutd("Clean play state...");

	CleanObjects(m_gameObjects);

	Actor::BulletHandler::Instance()->ClearBullets();

	for(auto& texture : m_textureIdList) {
		TextureManager::Instance()->ClearFromTextureMap(texture);
	}
}


bool PlayState::OnEnter() {
	loutd("Entering to play state");

	SoundManager::Instance()->PlayMusic("gameMusic", -1);

	level = BuildLevel();
	if(!level || !LoadState(GAME_STATES_FILE)) {
		return false;
	}

	m_isLoadingComplete = true;
	return true;
}


bool PlayState::OnExit() {
	loutd("Exiting to play state...");

	m_isExiting = true;

	Actor::BulletHandler::Instance()->ClearBullets();

	loutd("Exited to play state...");

	return true;
}


std::unique_ptr<Level> PlayState::BuildLevel() {
	LevelParser levelParser;
	const size_t currentLevel{ Game::Instance()->GetCurrentLevel() };
	return levelParser.ParseLevel(Game::Instance()->GetLevelFiles()[currentLevel], m_textureIdList);
}

} // namespace Engine
