/// @file level_parser.hpp
/// @brief Implementation of the system for parsing xml files of game levels.
#pragma once

#ifndef __LEVEL_PARSER_HPP__
#define __LEVEL_PARSER_HPP__


#include <vector>
#include <cstdint>
#include <system_error>
#include <string>
#include <unordered_map>
#include <memory>

#include <tinyxml.h>

#include <level/level.hpp>
#include <level/tileset.hpp>
#include <level/tile_layer.hpp>


namespace Engine {

class TileLayer;
class Level;


/// @brief System for parsing xml files of game levels
/// @warning System is case sensitive!
class LevelParser {
public:
	std::unique_ptr<Level> ParseLevel(const std::string& levelFile, std::vector<std::string>& textureIds);

private:
	std::error_code ParseTilesets(TiXmlElement* tilesetRoot,
								  std::vector<Tileset>& tilesets,
								  std::vector<std::string>& textureIds);
	std::error_code ParseTilesetFile(const std::string& tilesetFile,
									 Tileset& tilesets,
									 std::vector<std::string>& textureIds);

	std::error_code ParseTileLayer(TiXmlElement* tileElement,
								   std::vector<std::shared_ptr<Layer>>& layers,
								   std::vector<std::weak_ptr<TileLayer>>& collisionLayers,
								   const std::vector<Tileset>& tilesets);

	std::error_code ParseTextures(TiXmlElement* textureRoot);

	std::error_code ParseObjectLayer(TiXmlElement* objectElement,
									 std::vector<std::shared_ptr<Layer>>& layers,
									 std::unique_ptr<Level>& level,
									 std::vector<std::string>& textureIds);

	std::error_code ParseElementProperties(TiXmlElement* propertiesElement,
										   std::unordered_map<std::string, std::string>& propertiesAttributes) const;
private:
	int32_t m_tileSize;
	int32_t m_width;
	int32_t m_height;
};

} // namespace Engine


#endif // !defined(__LEVEL_PARSER_HPP__)
