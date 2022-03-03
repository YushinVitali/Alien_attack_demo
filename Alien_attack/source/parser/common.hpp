/// @file common.hpp
/// @brief Description of auxiliary functions to implement the xml file parsing system.
#pragma once

#ifndef __PARSER_COMMON_HPP__
#define __PARSER_COMMON_HPP__


#include <string>
#include <system_error>

#include <tinyxml.h>


namespace Engine {

std::error_code GetStringAttribute(TiXmlElement* element,
								   const std::string& name,
								   std::string& attribute);

std::error_code GetIntAttribute(TiXmlElement* element,
								const std::string& name,
								int32_t& attribute);

} // namespace Engine


#endif // !defined(__PARSER_COMMON_HPP__)
