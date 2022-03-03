/// @file state_parser.cpp
/// @brief Implementation of the system for parsing xml files of game states.
#include <parser/state_parser.hpp>

#include <algorithm>

#include <logger.hpp>

#include <texture_manager.hpp>
#include <game.hpp>

#include <parser/parser_error_code.hpp>
#include <parser/common.hpp>

#include <game_objects/game_object_factory.hpp>

#include <filemanager/filemanager.hpp>


namespace Engine {

std::error_code StateParser::ParseState(const std::string& sourceFile, StateId stateId,
							 std::vector<std::unique_ptr<GameObject>> &objects,
							 std::vector<std::string>& textureIds) {
	if(sourceFile.empty()) {
		const std::error_code errorCode{ ParserError::LoadingFileFailed };
		lerr("The name of the game states file is empty!", errorCode);
		return errorCode;
	}

	lout(LOG_TYPE::INFO, "Parsing " + sourceFile + " file...");

	TiXmlDocument xmlDoc;
	if(!xmlDoc.LoadFile(sourceFile.c_str())) {
		const std::error_code errorCode{ ParserError::LoadingFileFailed };
		lerr(xmlDoc.ErrorDesc(), errorCode);
		return errorCode;
	}

	TiXmlElement* root{ xmlDoc.RootElement() };
	if(!root) {
		const std::error_code errorCode{ ParserError::GettingNodeFailed };
		lerr("Getting the root node failed!", errorCode);
		return errorCode;
	}

	TiXmlElement* stateRoot{ nullptr };

	const std::string stateName{ ToString(stateId) };
	for(TiXmlElement* element = root->FirstChildElement();
			element != nullptr; element = element->NextSiblingElement()) {
		if(stateName == element->Value()) {
			stateRoot = element;
		}
	}
	if(!stateRoot) {
		const std::error_code errorCode{ ParserError::GettingNodeFailed };
		lerr("\'" + stateName + "\' state not found!", errorCode);
		return errorCode;
	}

	const std::string texturesSectionName{ "textures" };
	TiXmlElement* textureRoot{ nullptr };
	for(TiXmlElement* element = stateRoot->FirstChildElement();
			element != nullptr; element = element->NextSiblingElement()) {
		if(element->Value() == texturesSectionName) {
			textureRoot = element;
		}
	}

	if(!textureRoot) {
		lout(LOG_TYPE::WARNING, "\'" + texturesSectionName + "\' element not found!",
			 ParserError::GettingNodeFailed);
	}

	std::error_code errorCode{ ParseTexture(textureRoot, textureIds) };
	if(errorCode) {
		return errorCode;
	}

	const std::string objectsSectionName{ "objects" };
	TiXmlElement* objectRoot{ nullptr };
	for(TiXmlElement* element = stateRoot->FirstChildElement();
			element != nullptr; element = element->NextSiblingElement()) {
		if(element->Value() == objectsSectionName) {
			objectRoot = element;
		}
	}

	if(!objectRoot) {
		lout(LOG_TYPE::WARNING, "\'" + objectsSectionName + "\' element not found!",
			 ParserError::GettingNodeFailed);
		return std::error_code{};
	}

	return ParseObjects(objectRoot, objects);
}


std::error_code StateParser::ParseTexture(TiXmlElement *stateRoot, std::vector<std::string>& textureIds) {
	std::error_code errorCode{};
	for(TiXmlElement* element = stateRoot->FirstChildElement();
			element != nullptr; element = element->NextSiblingElement()) {
		std::string filenameAttribute;
		errorCode = GetStringAttribute(element, "filename", filenameAttribute);

		if(errorCode) {
			return errorCode;
		}

		std::string idAttribute;
		errorCode = GetStringAttribute(element, "id", idAttribute);
		if(errorCode) {
			return errorCode;
		}

		auto pathFile{ Filemanager::Instance()->FindFile(filenameAttribute) };
		if(pathFile) {
			errorCode = TextureManager::Instance()->Load(pathFile.value(), idAttribute,
														 Game::Instance()->GetRenderer());
			if(errorCode) {
				break;
			}
		}

		textureIds.emplace_back(idAttribute);
	}
	return errorCode;
}


std::error_code StateParser::ParseObjects(TiXmlElement* stateRoot,
										  std::vector<std::unique_ptr<GameObject>>& objects) {
	if(!stateRoot) {
		const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
		lerr("Root node state is null!", errorCode);
		return errorCode;
	}

	std::unordered_map<std::string, int32_t> objectAttributes{
		{ "x",          0 },
		{ "y",          0 },
		{ "width",      0 },
		{ "height",     0 },
		{ "frameCount", 0 },
		{ "callbackId", 0 },
		{ "animSpeed",  1 }
	};

	const std::vector<std::string> optionalAttributes {
		"callbackId", "animSpeed"
	};

	for(TiXmlElement* element = stateRoot->FirstChildElement();
			element != nullptr; element = element->NextSiblingElement()) {

		std::string textureId;
		auto errorCode{ GetStringAttribute(element, "textureId", textureId) };
		if(errorCode) {
			return errorCode;
		}

		int32_t result;
		for(auto& attribute : objectAttributes) {
			result = element->QueryIntAttribute(attribute.first, &attribute.second);
			if(TIXML_SUCCESS != result) {
				bool isOptionalAttribute{ optionalAttributes.end() != std::find(optionalAttributes.cbegin(),
																				optionalAttributes.cend(),
																				attribute.first) };
				if(isOptionalAttribute) {
					loutd("Failed to get \'" + attribute.first +
						  "\' object attribute not required!");
					continue;
				}
				const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
				lerr("Failed to get the \'" + attribute.first + "\' object's attribute!", errorCode);
				return errorCode;
			}
		}

		std::unique_ptr<GameObject> gameObject{
			GameObjectFactory::Instance()->Create(element->Attribute("type"))
		};
		gameObject->Load({ objectAttributes["x"], objectAttributes["y"],
						   objectAttributes["width"], objectAttributes["height"],
						   objectAttributes["frameCount"], textureId,
						   objectAttributes["callbackId"], objectAttributes["animSpeed"] });
		objects.emplace_back(std::move(gameObject));
	}

	return std::error_code{};
}

} // namespace Engine
