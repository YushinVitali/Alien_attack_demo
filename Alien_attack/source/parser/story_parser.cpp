/// @file story_parser.cpp
/// @brief Implementation of the system for parsing xml files of game stories.
#include <parser/story_parser.hpp>

#include <unordered_map>

#include <logger.hpp>

#include <parser/parser_error_code.hpp>

#include <game.hpp>
#include <texture_manager.hpp>

#include <filemanager/filemanager.hpp>


namespace Engine {

std::error_code StoryParser::ParseStories(const std::string& sourceFile,
										  int32_t numberLevel,
										  std::vector<std::unique_ptr<GameObject>>& texts,
										  std::vector<std::string>& textureIds) const {
	if(sourceFile.empty()) {
		const std::error_code errorCode{ ParserError::LoadingFileFailed };
		lerr("The stories file name is empty!", errorCode);
		return errorCode;
	}

	lout(LOG_TYPE::INFO, "Parsing " + sourceFile + " file...");

	TiXmlDocument storyDoc;
	if(!storyDoc.LoadFile(sourceFile.c_str())) {
		const std::error_code errorCode{ ParserError::LoadingFileFailed };
		lerr(storyDoc.ErrorDesc(), errorCode);
		return errorCode;
	}

	TiXmlElement* root{ storyDoc.RootElement() };
	if(!root) {
		const std::error_code errorCode{ ParserError::GettingNodeFailed };
		lerr("Getting the root node failed!", errorCode);
		return errorCode;
	}

	const std::string storiesMarker{ "stories" };
	if(storiesMarker != root->ValueStr()) {
		const std::error_code errorCode{ ParserError::GettingNodeFailed };
		lerr("\'" + storiesMarker + "\' marker not found!", errorCode);
		return errorCode;
	}

	std::unordered_map<std::string, std::string> storyAttributes{
		{ "level",     "" },
		{ "type",      "" },
		{ "textureId", "" },
		{ "font",      "" },
		{ "x",         "" },
		{ "y",         "" },
		{ "width",     "" },
		{ "fontSize",  "" }
	};

	const std::string storyMarker{ "story" };
	for(TiXmlElement* element = root->FirstChildElement();
			element != nullptr; element = element->NextSiblingElement()) {
		if(storyMarker != element->Value()) {
			continue;
		}

		for(auto& attribute : storyAttributes) {
			int32_t result = element->QueryStringAttribute(attribute.first.c_str(), &attribute.second);
			if(TIXML_SUCCESS != result) {
				const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
				lerr("\'" + attribute.first + "\' attribute not found!",
					 errorCode);
				return errorCode;
			}
		}

		if(numberLevel != std::stoi(storyAttributes["level"])) {
			continue;
		}

		const std::string fontFile{ storyAttributes["font"] };
		auto pathFile{ Filemanager::Instance()->FindFile(fontFile) };
		if(!pathFile) {
			std::error_code errorCode{ ParserError::FileNotFound };
			lerr("The \'" + fontFile + "\'font file could not be found!", errorCode);
			return errorCode;
		}

		const std::string textureId{ storyAttributes["textureId"] };

		const SDL_Color WhiteColor{ 255, 255, 255, 255 };
		std::error_code errorCode{
			TextureManager::Instance()->LoadText(pathFile.value(),
												 textureId,
												 element->GetText(),
												 WhiteColor,
												 std::stoi(storyAttributes["fontSize"]),
												 std::stoi(storyAttributes["width"]),
												 Game::Instance()->GetRenderer())
		};
		if(errorCode) {
			return errorCode;
		}

		textureIds.emplace_back(textureId);

		std::unique_ptr<GameObject> gameObject{
			GameObjectFactory::Instance()->Create(storyAttributes["type"])
		};

		SDL_Rect rectObject{ std::stoi(storyAttributes["x"]),
							 std::stoi(storyAttributes["y"]),
							 std::stoi(storyAttributes["width"]),
							 0 };
		SDL_QueryTexture(TextureManager::Instance()->GetTexture(textureId),
						 nullptr, nullptr, &rectObject.w, &rectObject.h);
		gameObject->Load({ rectObject.x, rectObject.y,
						 rectObject.w, rectObject.h,
						 1, textureId, 0, 0 });
		texts.emplace_back(std::move(gameObject));
	}

	return std::error_code{};
}

} // namespace Engine
