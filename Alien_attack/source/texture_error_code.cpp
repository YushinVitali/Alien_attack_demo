/// @file texture_error_code.cpp
/// @brief Implementation of basic texture loading and rendering system errors.

#include <texture_error_code.hpp>

#include <string>


namespace Engine {

namespace { // anonymous namespace

struct TextureErrorCategory : std::error_category {
	const char* name() const noexcept override;
	std::string message(int errorCode) const override;
};


const char* TextureErrorCategory::name() const noexcept {
	return "TextureError";
}


std::string TextureErrorCategory::message(int errorCode) const {
	switch(static_cast<TextureError>(errorCode)) {
		case TextureError::LoadingFailed:
			return "Failed to load file!";

		case TextureError::ConversionSurfaceToTextureFailed:
			return "Failed conversion Surface to Texture!";

		case TextureError::RenderTextToSurface:
			return "Failed to render Text into the Surface!";

		case TextureError::InitTTFLibraryFailed:
			return "TTF library initialization failed!";

		default:
			return "Unrecognized error!";
	}
}

} // anonymous namespace


const TextureErrorCategory TheTextureErrorCategory {};


std::error_code make_error_code(TextureError errorCode) {
	return {
			static_cast<int>(errorCode),
			TheTextureErrorCategory
		};
}

} // namespace Engine
