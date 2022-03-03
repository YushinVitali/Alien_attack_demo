/// @file controller_error_code.cpp
/// @brief Implementation of controller errors.

#include <controllers/controller_error_code.hpp>

#include <string>


namespace Engine {

namespace { // anonymous namespace

struct ControllerErrorCategory : std::error_category {
	const char* name() const noexcept override;
	std::string message(int errorCode) const override;
};


const char* ControllerErrorCategory::name() const noexcept {
	return "ControllerError";
}


std::string ControllerErrorCategory::message(int errorCode) const {
	switch(static_cast<ControllerError>(errorCode)) {
		case ControllerError::JoystickNotSuitable:
			return "During initialization the wrong joystick was detected!";
		case ControllerError::JoystickInitFailed:
			return "Joystick initialization failed!";

		default:
			return "Unrecognized error!";
	}
}

} // anonymous namespace


const ControllerErrorCategory TheControllerErrorCategory {};


std::error_code make_error_code(ControllerError errorCode) {
	return {
			static_cast<int>(errorCode),
			TheControllerErrorCategory
		};
}

} // namespace Engine
