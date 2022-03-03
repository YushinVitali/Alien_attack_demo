/// @file game_winning_state.cpp
/// @brief Implementing of the state of winning game.
#include <game_states/game_winning_state.hpp>

#include <logger.hpp>

#include <game.hpp>
#include <texture_manager.hpp>

#include <filemanager/filemanager.hpp>

#include <game_objects/interface/button.hpp>

#include <parser/story_parser.hpp>


namespace Engine {


GameWinningState::~GameWinningState() {
	GameWinningState::Clean();
}


void GameWinningState::Update() {
	if(m_isLoadingComplete && !m_isExiting) {
		UpdateObjects(m_gameObjects);
	}
}


void GameWinningState::Render() {
	if(m_isExiting) {
		return;
	}

	SDL_RenderClear(Game::Instance()->GetRenderer());

	if(m_isLoadingComplete) {
		RenderObjects(m_gameObjects);
	}
}


void GameWinningState::Clean() {
	CleanObjects(m_gameObjects);

	for(auto& texture : m_textureIdList) {
		TextureManager::Instance()->ClearFromTextureMap(texture);
	}
}


bool GameWinningState::OnEnter() {
	loutd("Entering to between level state...");

	if(!LoadState(GAME_STATES_FILE) || !LoadStories(GAME_STORIES_FILE)) {
		return false;
	}

	m_callbacks.emplace_back(nullptr);
	m_callbacks.emplace_back(OnClickButtonMenu);

	SetCallbacks(m_callbacks);

	m_isLoadingComplete = true;

	loutd("Entered to between level state...");
	return true;
}


bool GameWinningState::OnExit() {
	loutd("Exiting to pause state...");

	m_isExiting = true;

	loutd("Exited to pause state...");

	return true;
}


bool GameWinningState::LoadStories(const std::string& fileStories) {
	const auto filePath = Filemanager::Instance()->FindObjectDescription("stories.xml");
	if(!filePath) {
		lout(LOG_TYPE::ERROR, "Stories information file not found!");
		return false;
	}

	StoryParser storyParser;
	const auto errorCode{
		storyParser.ParseStories(filePath.value(),
								 Game::Instance()->GetLevelFiles().size(),
								 m_gameObjects, m_textureIdList)
	};
	if(errorCode) {
		lout(LOG_TYPE::ERROR,
			 "An error occurred while entering the " + ToString(m_stateId) + " state!");
		return false;
	}

	return true;
}

void GameWinningState::OnClickButtonMenu() {
	Game::Instance()->GetStateMachine()->ChangeState(StateId::Menu);
}

} // namespace Engine
