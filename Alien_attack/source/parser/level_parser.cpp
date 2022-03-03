/// @file level_parser.cpp
/// @brief Description of the system for parsing xml files of game levels.
#include <parser/level_parser.hpp>

#include <zlib.h>

#include <base64.h>

#include <logger.hpp>

#include <game.hpp>
#include <texture_manager.hpp>

#include <parser/parser_error_code.hpp>
#include <parser/common.hpp>

#include <level/object_layer.hpp>

#include <filemanager/filemanager.hpp>

#include <game_objects/game_object.hpp>
#include <game_objects/game_object_factory.hpp>
#include <game_objects/actor/player.hpp>


namespace Engine {

std::unique_ptr<Level> LevelParser::ParseLevel(const std::string& levelFile,
											   std::vector<std::string>& textureIds) {
	std::error_code errorCode{};
	if(levelFile.empty()) {
		lerr("The name of the level file is empty!", ParserError::LoadingFileFailed);
		return nullptr;
	}

	loutd("Parsing \'" + levelFile + "\' level...");

	TiXmlDocument levelDoc;
	if(!levelDoc.LoadFile(levelFile)) {
		lerr(levelDoc.ErrorDesc(), ParserError::LoadingFileFailed);
		return nullptr;
	}

	TiXmlElement* root = levelDoc.RootElement();
	if(!root) {
		lerr("Getting the root node failed!",  ParserError::GettingNodeFailed);
		return nullptr;
	}

	std::unordered_map<std::string, int32_t*> docAttributes {
		{ "tilewidth", &m_tileSize },
		{ "width",     &m_width },
		{ "height",    &m_height }
	};

	int32_t result{ 0 };
	for(auto& attribute : docAttributes) {
		result += root->QueryIntAttribute(attribute.first, attribute.second);
	}
	if(TIXML_SUCCESS != result) {
		lerr("Failed to read attributes of the \'" + root->ValueStr() + "\' node.",
			 ParserError::ParsingAttributesFailed);
		return nullptr;
	}

	std::unique_ptr<Level> level = std::unique_ptr<Level>(new Level());

	for(TiXmlElement* element = root->FirstChildElement();
			element != nullptr; element = element->NextSiblingElement()) {
		const std::string elementValue{ element->ValueStr() };
		if(std::string{ "tileset" } == elementValue) {
			errorCode = ParseTilesets(element, level->GetTilesets(), textureIds);
			if(errorCode) {
				return nullptr;
			}
		}

		if(std::string{ "layer" } == elementValue) {
			errorCode = ParseTileLayer(element,
									   level->GetLayers(),
									   level->GetCollisionLayers(),
									   level->GetTilesets());
			if(errorCode) {
				return nullptr;
			}
		}

		if(std::string{ "objectgroup" } == elementValue) {
			errorCode = ParseObjectLayer(element, level->GetLayers(),
										 level, textureIds);
			if(errorCode) {
				return nullptr;
			}
		}

		if(std::string{ "property" } == elementValue) {
			errorCode = ParseTextures(element);
			if(errorCode) {
				return nullptr;
			}
		}
	}

	return level;
}


std::error_code LevelParser::ParseTilesets(TiXmlElement* tilesetRoot,
										   std::vector<Tileset>& tilesets,
										   std::vector<std::string>& textureIds) {
	loutd("Parsing tileset node...");

	std::string tilesetFile;

	std::error_code errorCode{ GetStringAttribute(tilesetRoot, "source", tilesetFile)};
	if(errorCode) {
		return errorCode;
	}

	Tileset tileset;
	errorCode = GetIntAttribute(tilesetRoot, "firstgid", tileset.firstGridId);
	if(errorCode) {
		return errorCode;
	}

	auto filePath = Filemanager::Instance()->FindMapContent(tilesetFile);
	if(!filePath) {
		errorCode = ParserError::FileNotFound;
		lerr("\'" + tilesetFile + "\'tileset file was not found!", errorCode);
		return errorCode;
	}

	errorCode = ParseTilesetFile(filePath.value(), tileset, textureIds);
	if(errorCode) {
		return errorCode;
	}

	tilesets.emplace_back(tileset);

	return std::error_code{};
}


std::error_code LevelParser::ParseTilesetFile(const std::string& tilesetFile,
											  Tileset& tileset,
											  std::vector<std::string>& textureIds) {
	loutd("Parsing \'" + tilesetFile + "\' tileset file...");

	TiXmlDocument tilesetDoc;
	if(!tilesetDoc.LoadFile(tilesetFile)) {
		const std::error_code errorCode{ ParserError::LoadingFileFailed };
		lerr(tilesetDoc.ErrorDesc(), errorCode);
		return errorCode;
	}

	TiXmlElement* root = tilesetDoc.RootElement();
	if(!root) {
		const std::error_code errorCode{ ParserError::GettingNodeFailed };
		lerr("Getting the root node failed!", errorCode);
		return errorCode;
	}

	std::error_code errorCode{ GetStringAttribute(root, "name", tileset.name)};
	if(errorCode) {
		return errorCode;
	}

	std::unordered_map<std::string, int32_t*> imageAttribute{
		{ "width",  &tileset.width },
		{ "height", &tileset.height }
	};


	if(!root->FirstChildElement()){
		const std::error_code errorCode{ ParserError::GettingNodeFailed };
		lerr("Getting a child of the root node has failed!", errorCode);
		return errorCode;
	}

	int32_t result{ 0 };
	for(auto& attribute : imageAttribute) {
		result += root->FirstChildElement()->QueryIntAttribute(attribute.first, attribute.second);
	}
	if(TIXML_SUCCESS != result) {
		const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
		lerr("Failed to read attributes of the \'" + root->ValueStr() + "\' node.", errorCode);
		return errorCode;
	}

	std::string imageFile;
	errorCode = GetStringAttribute(root->FirstChildElement(), "source", imageFile);
	if(errorCode) {
		return errorCode;
	}

	auto filePath = Filemanager::Instance()->FindFile(imageFile);
	if(!filePath) {
		errorCode = ParserError::FileNotFound;
		lerr("The image file of the \'" + imageFile + "\' tileset was not found!",
			 errorCode);
		return errorCode;
	}
	errorCode = TextureManager::Instance()->Load(filePath.value(), tileset.name,
												 Game::Instance()->GetRenderer());
	if(errorCode) {
		return errorCode;
	}

	std::unordered_map<std::string, int32_t*> tilesetAttributes{
		{ "tilewidth",  &tileset.tileWidth },
		{ "tileheight", &tileset.tileHeight },
		{ "columns",    &tileset.numberColumns },
		{ "spacing",    &tileset.spacing },
		{ "margin",     &tileset.margin }
	};
	result = 0;
	for(auto& attribute : tilesetAttributes) {
		result += root->QueryIntAttribute(attribute.first, attribute.second);
	}
	if(TIXML_SUCCESS != result) {
		const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
		lerr("Failed to read attributes of the \'" + root->ValueStr() + "\' node.", errorCode);
		return errorCode;
	}

	textureIds.emplace_back(tileset.name);

	return std::error_code{};
}


std::error_code LevelParser::ParseTileLayer(TiXmlElement* tileElement,
											std::vector<std::shared_ptr<Layer>>& layers,
											std::vector<std::weak_ptr<TileLayer>>& collisionLayers,
											const std::vector<Tileset>& tilesets) {
	loutd("Parsing tile layer...");

	std::unordered_map<std::string, std::string> propertyAttributes;

	TiXmlElement* dataNode{ nullptr };
	for(TiXmlElement* element = tileElement->FirstChildElement();
			element != nullptr; element = element->NextSiblingElement()) {
		const std::string elementValue{ element->ValueStr() };
		if(std::string{ "properties" } == elementValue) {
			const std::error_code errorCode{ ParseElementProperties(element, propertyAttributes) };
			if(errorCode) {
				return errorCode;
			}
		}

		if(std::string("data") == elementValue) {
			dataNode = element;
		}
	}

	if(!dataNode) {
		const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
		lerr("Failed to find the 'data' node when parsing the tile layer!",
			 errorCode);
		return errorCode;
	}

	std::string decodedIds{ base64_decode(dataNode->GetText()) };

	uLongf numberGids = m_width * m_height * sizeof(int32_t);
	std::vector<unsigned> gids(numberGids);
	uncompress(reinterpret_cast<Bytef*>(&gids[0]), &numberGids,
			   reinterpret_cast<const Bytef*>(decodedIds.c_str()),
			   decodedIds.size());

	std::vector<std::vector<int32_t>> data;
	std::vector<int32_t> layerRow(m_width);
	for(int64_t i = 0; i < m_height; ++i) {
		data.emplace_back(layerRow);
	}

	for(int64_t rows = 0; rows < m_height; ++rows) {
		for(int64_t cols = 0; cols < m_width; ++cols) {
			data[rows][cols] = gids[rows * m_width + cols];
		}
	}

	std::shared_ptr<TileLayer> tileLayer = std::make_unique<TileLayer>(m_tileSize, tilesets);
	tileLayer->SetTileIds(std::move(data));

	tileLayer->SetMapWidth(m_width);
	tileLayer->SetMapHeight(m_height);

	if(propertyAttributes.find("collidable") != propertyAttributes.end()) {
		collisionLayers.emplace_back(tileLayer);
	}

	layers.emplace_back(std::move(tileLayer));

	return std::error_code{};
}


std::error_code LevelParser::ParseTextures(TiXmlElement* textureRoot) {
	loutd("Parsing texture...");

	std::unordered_map<std::string, std::string> textureAttributes{
		{ "name",  "" },
		{ "value", "" }
	};
	int32_t result{ 0 };
	for(auto& attribute : textureAttributes) {
		result += textureRoot->QueryStringAttribute(attribute.first.c_str(), &attribute.second);
	}
	if(TIXML_SUCCESS != result) {
		const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
		lerr("Failed to read attributes of the \'" + textureRoot->ValueStr() + "\' node.",
			 errorCode);
		return errorCode;
	}
	return std::error_code{};
}


std::error_code LevelParser::ParseObjectLayer(TiXmlElement* objectElement,
											  std::vector<std::shared_ptr<Layer>>& layers,
											  std::unique_ptr<Level>& level,
											  std::vector<std::string>& textureIds) {
	loutd("Parsing object layer...");

	//ObjectLayer* objectLayer{ new ObjectLayer() };
	std::shared_ptr<ObjectLayer> objectLayer = std::make_unique<ObjectLayer>();

	std::unordered_map<std::string, int32_t> objectAttributes{
		{ "x", 0 },
		{ "y", 0 }
	};

	std::unordered_map<std::string, std::string> propertyAttributes{
		{ "frameCount",    "1" },
		{ "textureHeight", "0" },
		{ "textureWidth",  "0" },
		{ "textureId",     "0" },
		{ "callbackId",    "0" },
		{ "animSpeed",     "0" }
	};

	for(TiXmlElement* element = objectElement->FirstChildElement();
			element != nullptr; element = element->NextSiblingElement()) {

		if(std::string{ "object" } != element->ValueStr()) {
			continue;
		}

		std::string objectType;
		int32_t result{ 0 };
		for(auto& attribute : objectAttributes) {
			result += element->QueryIntAttribute(attribute.first, &attribute.second);
		}
		result += element->QueryStringAttribute("type", &objectType);
		if(TIXML_SUCCESS != result) {
			const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
			lerr("Failed to read attributes of the \'" + element->ValueStr() + "\' node.",
				 errorCode);
			return errorCode;
		}

		std::shared_ptr<GameObject> gameObject{
			std::shared_ptr<GameObject>(GameObjectFactory::Instance()->Create(objectType))
		};

		for(TiXmlElement* properties = element->FirstChildElement();
				properties != nullptr; properties = properties->NextSiblingElement()) {

			if(std::string{ "properties" } != properties->ValueStr()) {
				continue;
			}

			const std::error_code errorCode{
				ParseElementProperties(properties, propertyAttributes)
			};
			if(errorCode) {
				return errorCode;
			}

			break;
		}

		LoaderParams loaderParams{
			objectAttributes["x"], objectAttributes["y"],
			std::stoi(propertyAttributes["textureWidth"]),
			std::stoi(propertyAttributes["textureHeight"]),
			std::stoi(propertyAttributes["frameCount"]),
			propertyAttributes["textureId"],
			std::stoi(propertyAttributes["callbackId"]),
			std::stoi(propertyAttributes["animSpeed"])
		};

		gameObject->Load(loaderParams);
		if(std::string{ "Player"} == objectType) {
			level->SetPlayer(std::dynamic_pointer_cast<Actor::Player>(gameObject));
		}
		objectLayer->GetGameObject().emplace_back(gameObject);

		const auto textureMap = TextureManager::Instance()->GetTextureMap();
		const bool isNotLoadedTexture{
			textureMap.find(propertyAttributes["textureId"]) == textureMap.end()
		};
		if(isNotLoadedTexture) {
			const std::string& filename{ propertyAttributes["filename"] };
			auto filePath = Filemanager::Instance()->FindFile(filename);
			if(!filePath) {
				const std::error_code errorCode{ ParserError::FileNotFound };
				lerr("The image file of the \'" + filename + "\' tileset was not found!",
					 errorCode);
				return errorCode;
			}
			std::error_code errorCode{
				TextureManager::Instance()->Load(filePath.value(),
												 propertyAttributes["textureId"],
												 Game::Instance()->GetRenderer())
			};
			if(errorCode) {
				return errorCode;
			}
			textureIds.emplace_back(propertyAttributes["textureId"]);
		}
	}

	layers.emplace_back(std::move(objectLayer));

	return std::error_code{};
}


std::error_code LevelParser::ParseElementProperties(TiXmlElement* properties,
													std::unordered_map<std::string, std::string>& propertyAttributes) const {
	std::error_code errorCode;
	for(TiXmlElement* property = properties->FirstChildElement();
			property != nullptr; property = property->NextSiblingElement()) {

		if(std::string{ "property" } != property->ValueStr()) {
			continue;
		}

		std::string propertyName;
		errorCode = GetStringAttribute(property, "name", propertyName);
		if(errorCode) {
			return errorCode;
		}

		errorCode = GetStringAttribute(property, "value", propertyAttributes[propertyName]);
		if(errorCode) {
			return errorCode;
		}
	}

	return errorCode;
}

} // namespace Engine
