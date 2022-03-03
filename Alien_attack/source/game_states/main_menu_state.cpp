/// @file main_menu_state.cpp
/// @brief Implementation of the main menu state of game.
#include <game_states/main_menu_state.hpp>

#include <logger.hpp>

#include <game.hpp>
#include <texture_manager.hpp>

#include <game_objects/interface/button.hpp>

#include <filemanager/filemanager.hpp>

#include <sound/sound_manager.hpp>


namespace Engine {

MainMenuState::~MainMenuState() {
	MainMenuState::Clean();
}


void MainMenuState::Update() {
	if(m_isLoadingComplete && !m_isExiting) {
		UpdateObjects(m_gameObjects);
	}
}


void MainMenuState::Render() {
	if(m_isExiting) {
		return;
	}

	SDL_RenderClear(Game::Instance()->GetRenderer());

	if(m_isLoadingComplete) {
		RenderObjects(m_gameObjects);
	}
}


void MainMenuState::Clean() {
	loutd("Clean menu state...");

	CleanObjects(m_gameObjects);

	for(auto& texture : m_textureIdList) {
		TextureManager::Instance()->ClearFromTextureMap(texture);
	}
}


bool MainMenuState::OnEnter() {
	loutd("Entering to menu state...");

	if(!LoadState(GAME_STATES_FILE)) {
		return false;
	}

	m_callbacks.emplace_back(nullptr);
	m_callbacks.emplace_back(OnClickButtonPlay);
	m_callbacks.emplace_back(OnClickButtonExit);

	SetCallbacks(m_callbacks);

	m_isLoadingComplete = true;

	loutd("Entered to menu state...");

	SoundManager::Instance()->PlayMusic("announceMusic", -1);

	return true;
}


bool MainMenuState::OnExit() {
	loutd("Exiting to menu state...");

	m_isExiting = true;

	loutd("Exited to menu state...");

	return true;
}


void MainMenuState::OnClickButtonPlay() {
	Game::Instance()->ResetGame();
	Game::Instance()->GetStateMachine()->ChangeState(StateId::BetweenLevel);
}


void MainMenuState::OnClickButtonExit() {
	Game::Instance()->Quit();
}


void MainMenuState::SetCallbacks(const std::vector<Callback>& callbacks) {
	for(auto& object : m_gameObjects) {
		const auto button{ dynamic_cast<Interface::Button*>(object.get()) };
		if(button) {
			button->SetCallback(callbacks[button->GetCallbackId()]);
		}
	}
}

} // namespace Engine
