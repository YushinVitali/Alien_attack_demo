/// @file parser_error_code.cpp
/// @brief Implementation of errors in the xml file parsing system.
#include <parser/parser_error_code.hpp>

#include <string>


namespace Engine {

namespace { // anonymouse namespace

struct ParserErrorCategory : std::error_category {
	const char* name() const noexcept override;
	std::string message(int errorCode) const override;
}; // struct StateParserErrorCategory


const char* ParserErrorCategory::name() const noexcept {
	return "ParserError";
}


std::string ParserErrorCategory::message(int errorCode) const {
	switch(static_cast<ParserError>(errorCode)) {
		case ParserError::LoadingFileFailed:
			return "The parsing file download failed!";

		case ParserError::GettingNodeFailed:
			return "There was an error when I received the node!";

		case ParserError::ParsingAttributesFailed:
			return "There was an error when parsing attributes!";

		case ParserError::FileNotFound:
			return "File was not found!";

		default:
			return "Unrecognized error!";
	}
}

} // namespace anonymouse


const ParserErrorCategory TheParserErrorCategory {};


std::error_code make_error_code(ParserError errorCode) {
	return {
		static_cast<int>(errorCode),
		TheParserErrorCategory
	};
}

} // namespace Engine
