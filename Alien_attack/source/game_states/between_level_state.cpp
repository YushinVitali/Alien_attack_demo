/// @file between_level_state.cpp
/// @brief Implementing of the interlevel state of game.
#include <game_states/between_level_state.hpp>

#include <logger.hpp>

#include <game.hpp>
#include <texture_manager.hpp>

#include <filemanager/filemanager.hpp>

#include <game_objects/interface/button.hpp>

#include <sound/sound_manager.hpp>


namespace Engine {

BetweenLevelState::~BetweenLevelState() {
	BetweenLevelState::Clean();
}


void BetweenLevelState::Update() {
	if(m_isLoadingComplete && !m_isExiting) {
		UpdateObjects(m_gameObjects);
	}
}


void BetweenLevelState::Render() {
	if(m_isExiting) {
		return;
	}

	SDL_RenderClear(Game::Instance()->GetRenderer());

	if(m_isLoadingComplete) {
		RenderObjects(m_gameObjects);
	}
}


void BetweenLevelState::Clean() {
	CleanObjects(m_gameObjects);

	for(const auto& texture : m_textureIdList) {
		TextureManager::Instance()->ClearFromTextureMap(texture);
	}
}


bool BetweenLevelState::OnEnter() {
	loutd("Entering to between level state...");

	if(!LoadState(GAME_STATES_FILE) || !LoadStories(GAME_STORIES_FILE)) {
		return false;
	}

	m_callbacks.emplace_back(nullptr);
	m_callbacks.emplace_back(OnClickButtonNext);

	SetCallbacks(m_callbacks);

	m_isLoadingComplete = true;

	loutd("Entered to between level state...");
	return true;
}


bool BetweenLevelState::OnExit() {
	loutd("Exiting to between level state...");

	m_isExiting = true;

	loutd("Exited to between level state...");

	return true;
}


void BetweenLevelState::OnClickButtonNext() {
	Game::Instance()->GetStateMachine()->ChangeState(StateId::Play);
}

} // namespace Engine
