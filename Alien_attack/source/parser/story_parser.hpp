/// @file story_parser.hpp
/// @brief Description of the system for parsing xml files of game stories.
#pragma once

#ifndef __STORY_PARSER_HPP__
#define __STORY_PARSER_HPP__


#include <string>
#include <vector>
#include <system_error>
#include <memory>

#include <tinyxml.h>

#include <game_objects/game_object.hpp>


namespace Engine {

/// @brief System for parsing xml files of game stories.
class StoryParser {
public:
	std::error_code ParseStories(const std::string& sourceFile, int32_t numberLevel,
								 std::vector<std::unique_ptr<GameObject>>& texts,
								 std::vector<std::string>& textureIds) const;
}; // class TextParser

} // namespace Engine


#endif // !defined(__STORY_PARSER_HPP__)
