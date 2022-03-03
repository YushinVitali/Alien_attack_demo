/// @file parser_error_code.hpp
/// @brief Description of errors in the xml file parsing system.
#pragma once

#ifndef __PARSER_ERROR_CODE_HPP__
#define __PARSER_ERROR_CODE_HPP__


#include <system_error>


namespace Engine {

/// @brief Errors in the xml file parsing system
enum class ParserError {
	LoadingFileFailed	= 1,

	GettingNodeFailed		= 10,

	ParsingAttributesFailed	= 20,

	FileNotFound			= 30
}; // enum class StateParserError


std::error_code make_error_code(ParserError errorCode);

} // namespace Engine


namespace std {

template<>
struct is_error_code_enum<Engine::ParserError> : true_type {};

}


#endif // !defined(PARSER_ERROR_CODE_HPP__)
