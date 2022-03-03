/// @file common.cpp
/// @brief Implementation of auxiliary functions to implement the xml file parsing system.
#include <parser/common.hpp>

#include <tinyxml.h>

#include <logger.hpp>

#include <parser/parser_error_code.hpp>


namespace Engine {

std::error_code GetStringAttribute(TiXmlElement* element, const std::string& name, std::string& attribute) {
	if(!element || name.empty()) {
		const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
		lerr("Failed to get the attribute!", errorCode);
		return errorCode;
	}

	auto result{ element->QueryStringAttribute(name.c_str(), &attribute)};
	if(TIXML_SUCCESS != result) {
		const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
		lerr("Failed to get the \'" + name + "\' object's attribute!", errorCode);
		return errorCode;
	}

	return std::error_code{};
}


std::error_code GetIntAttribute(TiXmlElement* element, const std::string& name, int32_t& attribute) {
	if(!element || name.empty()) {
		const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
		lerr("Failed to get the attribute!", errorCode);
		return errorCode;
	}

	auto result{ element->QueryIntAttribute(name.c_str(), &attribute)};
	if(TIXML_SUCCESS != result) {
		const std::error_code errorCode{ ParserError::ParsingAttributesFailed };
		lerr("Failed to get the \'" + name + "\' object's attribute!", errorCode);
		return errorCode;
	}

	return std::error_code{};
}

} // namespace Engine
