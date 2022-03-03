/// @file game_over_state.cpp
/// @brief Implementing of the state of loss in the game.
#include <game_states/game_over_state.hpp>

#include <logger.hpp>

#include <game.hpp>
#include <texture_manager.hpp>

#include <game_objects/interface/button.hpp>

#include <filemanager/filemanager.hpp>


namespace Engine {


GameOverState::~GameOverState() {
	GameOverState::Clean();
}


void GameOverState::Update() {
	if(m_isLoadingComplete && !m_isExiting) {
		UpdateObjects(m_gameObjects);
	}
}


void GameOverState::Render() {
	if(m_isExiting) {
		return;
	}

	if(!m_isRender) {
		TextureManager::Instance()->Draw("clouds2", 0, 0,
										 Game::Instance()->GetWindowSize().width,
										 Game::Instance()->GetWindowSize().height,
										 Game::Instance()->GetRenderer());
		SDL_SetRenderDrawBlendMode(Game::Instance()->GetRenderer(), SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 0, 0, 255);
		SDL_Rect rect{ Game::Instance()->GetWindowSize().width / 4 - 20, 0,
					   Game::Instance()->GetWindowSize().width / 2,
					   Game::Instance()->GetWindowSize().height };
		SDL_RenderFillRect(Game::Instance()->GetRenderer(), &rect);

		m_isRender = true;
	}

	if(m_isLoadingComplete) {
		RenderObjects(m_gameObjects);
	}
}


void GameOverState::Clean() {
	CleanObjects(m_gameObjects);

	for(auto& texture : m_textureIdList) {
		TextureManager::Instance()->ClearFromTextureMap(texture);
	}
}


bool GameOverState::OnEnter() {
	loutd("Entering to game over state...");

	if(!LoadState(GAME_STATES_FILE)) {
		return false;
	}

	m_callbacks.emplace_back(nullptr);
	m_callbacks.emplace_back(OnClickButtonResume);
	m_callbacks.emplace_back(OnClickButtonMenu);

	SetCallbacks(m_callbacks);

	m_isLoadingComplete = true;

	loutd("Entered to game over state...");
	return true;
}


bool GameOverState::OnExit() {
	loutd("Exiting to game over state...");

	m_isExiting = true;

	loutd("Exited to game over state...");
	return true;
}


void GameOverState::OnClickButtonMenu() {
	Game::Instance()->GetStateMachine()->ChangeState(StateId::Menu);
}


void GameOverState::OnClickButtonResume() {
	Game::Instance()->ResetLevel();
	Game::Instance()->GetStateMachine()->ChangeState(StateId::Play);
}

} // namespace Engine
