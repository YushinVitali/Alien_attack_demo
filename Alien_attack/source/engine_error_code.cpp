/// @file engine_error_code.cpp
/// @brief Implementation of basic engine errors.

#include <engine_error_code.hpp>

#include <string>


namespace Engine {

namespace { // anonymous namespace

struct CoreErrorCategory : std::error_category {
	const char* name() const noexcept override;
	std::string message(int errorCode) const override;
};


const char* CoreErrorCategory::name() const noexcept {
	return "CoreError";
}


std::string CoreErrorCategory::message(int errorCode) const {
	switch(static_cast<CoreError>(errorCode)) {
		case CoreError::SdlInitFailed:
			return "Failed to initialize SDL library!";
		case CoreError::SdlInitSubSystemFailed:
			return "Failed to initialize SDL sub system!";

		case CoreError::WindowInitFailed:
			return "Failed to initialize window!";
		case CoreError::RendererInitFailed:
			return "Failed to initialize render!";

		default:
			return "Unrecognized error!";
	}
}

} // anonymous namespace


const CoreErrorCategory TheCoreErrorCategory {};


std::error_code make_error_code(CoreError errorCode) {
	return {
		static_cast<int>(errorCode),
		TheCoreErrorCategory
	};
}

} // namespace Engine
