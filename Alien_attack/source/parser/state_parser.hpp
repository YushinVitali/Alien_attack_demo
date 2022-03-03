/// @file state_parser.hpp
/// @brief Description of the system for parsing xml files of game states.
#pragma once

#ifndef __STATE_PARSER_HPP__
#define __STATE_PARSER_HPP__


#include <string>
#include <vector>
#include <system_error>

#include <tinyxml.h>

#include <game_states/game_state.hpp>

#include <game_objects/game_object.hpp>


namespace Engine {

/// @brief System for parsing xml files of game states.
class StateParser {
public:
	std::error_code ParseState(const std::string& sourceFile, StateId stateId,
							   std::vector<std::unique_ptr<GameObject>>& objects,
							   std::vector<std::string>& textureIds);

private:
	std::error_code ParseTexture(TiXmlElement* stateRoot,
								 std::vector<std::string>& textureIds);
	std::error_code ParseObjects(TiXmlElement* stateRoot,
								 std::vector<std::unique_ptr<GameObject>>& objects);
}; // class StateParser

} // namespace Engine


#endif // !defined(__STATE_PARSER_HPP__)
