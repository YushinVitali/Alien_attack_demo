/// @file game_state.cpp
/// @brief Implementing of the basic game state.
#include <game_states/game_state.hpp>

#include <unordered_map>

#include <logger.hpp>

#include <game.hpp>
#include <texture_manager.hpp>

#include <filemanager/filemanager.hpp>

#include <parser/state_parser.hpp>
#include <parser/story_parser.hpp>


namespace Engine {

void GameState::Resume() {

}

StateId GameState::GetStateId() const {
	return m_stateId;
}


std::error_code GameState::LoadObjects(const std::vector<std::pair<std::string, std::string> >& infoOfObjects) {
	for(const auto& infoOfObject : infoOfObjects) {
		const std::error_code errorCode{
			TextureManager::Instance()->Load(ROOT_DIR_TEXTURE + infoOfObject.first,
											 infoOfObject.second,
											 Game::Instance()->GetRenderer()) };
	if(errorCode) {
			return errorCode;
		}
	}
	return std::error_code{};
}


bool GameState::LoadState(const std::string& fileState) {
	const auto filePath{ Filemanager::Instance()->FindObjectDescription(fileState) };
	if(!filePath) {
		lout(LOG_TYPE::ERROR, ToString(m_stateId) + " status information file not found!");
		return false;
	}

	StateParser stateParser;
	const auto errorCode{
		stateParser.ParseState(filePath.value(), m_stateId, m_gameObjects, m_textureIdList)
	};
	if(errorCode) {
		lout(LOG_TYPE::ERROR,
			 "An error occurred while entering the " + ToString(m_stateId) + " state!");
		return false;
	}

	return true;
}


bool GameState::LoadStories(const std::string& fileStories) {
	const auto filePath = Filemanager::Instance()->FindObjectDescription("stories.xml");
	if(!filePath) {
		lout(LOG_TYPE::ERROR, "Stories information file not found!");
		return false;
	}

	StoryParser storyParser;
	const auto errorCode{
		storyParser.ParseStories(filePath.value(),
								 Game::Instance()->GetCurrentLevel(),
								 m_gameObjects, m_textureIdList)
	};
	if(errorCode) {
		lout(LOG_TYPE::ERROR,
			 "An error occurred while entering the " + ToString(m_stateId) + " state!");
		return false;
	}

	return true;
}


std::string ToString(StateId stateId) {
	const std::unordered_map<StateId, std::string> stateIdToString{
		{ StateId::Menu, "menu" },
		{ StateId::Play, "play" },
		{ StateId::Pause, "pause" },
		{ StateId::GameOver, "game_over" },
		{ StateId::BetweenLevel, "between_level" },
		{ StateId::GameWinning, "game_winning" }
	};

	const auto element{ stateIdToString.find(stateId) };
	return element != stateIdToString.end() ? element->second : "NONE";
}


void UpdateObjects(std::vector<std::unique_ptr<GameObject>>& objects) {
	for(auto& object : objects) {
		object->Update();
	}
}


void RenderObjects(std::vector<std::unique_ptr<GameObject>>& objects) {
	for(auto& object : objects) {
		object->Draw();
	}
}


void CleanObjects(std::vector<std::unique_ptr<GameObject>>& objects) {
	objects.clear();
}

} // namespace Engine
