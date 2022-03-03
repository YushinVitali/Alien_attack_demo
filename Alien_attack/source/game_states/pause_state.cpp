/// @file pause_state.cpp
/// @brief Implementation of the pause state of game.
#include <game_states/pause_state.hpp>

#include <logger.hpp>

#include <game.hpp>
#include <texture_manager.hpp>

#include <game_objects/interface/button.hpp>

#include <game_states/game_state_machine.hpp>

#include <filemanager/filemanager.hpp>


namespace Engine {


PauseState::~PauseState() {
	PauseState::Clean();
}


void PauseState::Update() {
	if(m_isLoadingComplete && !m_isExiting) {
		UpdateObjects(m_gameObjects);
	}
}


void PauseState::Render() {
	if(m_isExiting) {
		return;
	}

	if(!m_isRender) {
		SDL_SetRenderDrawBlendMode(Game::Instance()->GetRenderer(), SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 150);
		SDL_Rect rect{ 0, 0,
					   Game::Instance()->GetWindowSize().width,
					   Game::Instance()->GetWindowSize().height };
		SDL_RenderFillRect(Game::Instance()->GetRenderer(), &rect);
		m_isRender = true;
	}

	if(m_isLoadingComplete) {
		RenderObjects(m_gameObjects);
	}
}


void PauseState::Clean() {
	CleanObjects(m_gameObjects);

	for(auto& texture : m_textureIdList) {
		TextureManager::Instance()->ClearFromTextureMap(texture);
	}
}


bool PauseState::OnEnter() {
	loutd("Entering to pause state...");

	if(!LoadState(GAME_STATES_FILE)) {
		return false;
	}

	m_callbacks.emplace_back(nullptr);
	m_callbacks.emplace_back(OnClickButtonResume);
	m_callbacks.emplace_back(OnClickButtonMenu);

	SetCallbacks(m_callbacks);

	m_isLoadingComplete = true;

	loutd("Entered to pause state...");
	return true;
}


bool PauseState::OnExit() {
	loutd("Exiting to pause state...");

	m_isExiting = true;

	loutd("Exited to pause state...");

	return true;
}


void PauseState::OnClickButtonMenu() {
	Game::Instance()->GetStateMachine()->ChangeState(StateId::Menu);
}


void PauseState::OnClickButtonResume() {
	Game::Instance()->GetStateMachine()->PopState();
}

} // namespace Engine
