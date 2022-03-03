/// @file texture_manager.cpp
/// @brief Implementation of the texture loading and rendering system.
#include <texture_manager.hpp>

#include <SDL_image.h>
#include <SDL_ttf.h>

#include <logger.hpp>

#include <texture_error_code.hpp>


namespace Engine {

TextureManager* TextureManager::m_instance = nullptr;


TextureManager::~TextureManager() {
	for(auto& texture : m_textureMap) {
		SDL_DestroyTexture(texture.second);
	}
	m_textureMap.clear();
}


TextureManager* TextureManager::Instance() {
	if(!m_instance) {
		m_instance = new TextureManager();
	}
	return m_instance;
}


std::error_code TextureManager::Load(const std::string &filename, const std::string &id,
									 SDL_Renderer *renderer) {
	if(filename.empty() || id.empty()) {
		const std::error_code errorCode{ TextureError::LoadingFailed };
		lerr("Trying to load a texture with an empty name or ID!", errorCode);
		return errorCode;
	}

	lout(LOG_TYPE::INFO, "Loading " + filename + " file...");

	SDL_Surface* tempSurface{ IMG_Load(filename.c_str()) };
	if(!tempSurface) {
		const std::error_code errorCode{ TextureError::LoadingFailed };
		lerr(std::string{ IMG_GetError() }, errorCode);
		return errorCode;
	}

	SDL_Texture* texture{ SDL_CreateTextureFromSurface(renderer, tempSurface) };
	SDL_FreeSurface(tempSurface);

	if(!texture) {
		const std::error_code errorCode{ TextureError::ConversionSurfaceToTextureFailed };
		lerr(std::string{ SDL_GetError() }, errorCode);
		return errorCode;
	}

	m_textureMap[id] = texture;

	return std::error_code{};
}


std::error_code TextureManager::LoadText(const std::string fontFile, const std::string& id,
										 const std::string& message,
										 SDL_Color color, int32_t fontSize,
										 int32_t wrapLength,
										 SDL_Renderer* renderer) {
	if(fontFile.empty() || id.empty() || message.empty()) {
		const std::error_code errorCode{ TextureError::LoadingFailed };
		lerr("Trying to load a font with empty function arguments!", errorCode);
		return errorCode;
	}

	if (0 != TTF_Init()){
		const std::error_code errorCode{ TextureError::InitTTFLibraryFailed };
		lerr(std::string{ TTF_GetError() }, errorCode);
		return errorCode;
	}

	TTF_Font* font{ TTF_OpenFont(fontFile.c_str(), fontSize) };
	if(!font) {
		const std::error_code errorCode{ TextureError::LoadingFailed };
		lerr(std::string{ TTF_GetError() }, errorCode);
		return errorCode;
	}

	SDL_Surface* tempSurface{
		TTF_RenderText_Blended_Wrapped(font, message.c_str(), color, wrapLength)
	};
	TTF_CloseFont(font);

	if(!tempSurface) {
		const std::error_code errorCode{ TextureError::RenderTextToSurface };
		lerr(std::string{ TTF_GetError() }, errorCode);
		return errorCode;
	}

	SDL_Texture* texture{ SDL_CreateTextureFromSurface(renderer, tempSurface) };
	SDL_FreeSurface(tempSurface);

	if(!texture) {
		const std::error_code errorCode{ TextureError::ConversionSurfaceToTextureFailed };
		lerr(std::string{ SDL_GetError() }, errorCode);
		return errorCode;
	}

	m_textureMap[id] = texture;

	return std::error_code{};
}


void TextureManager::Draw(const std::string &id, int32_t x, int32_t y,
						  int32_t width, int32_t height,
						  SDL_Renderer* renderer,
						  SDL_RendererFlip flip /*= SDL_FLIP_NONE*/) {
	if(id.empty()) {
		return;
	}

	SDL_Rect srcRect{ 0, 0, width, height };
	SDL_Rect destRect{ x, y, width, height };

	SDL_RenderCopyEx(renderer, m_textureMap[id],
					 &srcRect, &destRect, 0, 0, flip);
}


void TextureManager::DrawFrame(const std::string &id, int32_t x, int32_t y,
							   int32_t width, int32_t height,
							   int32_t currentRow, int32_t currentFrame,
							   SDL_Renderer* renderer,
							   double angle, int32_t alpha,
							   SDL_RendererFlip flip /*= SDL_FLIP_NONE*/) {
	if(id.empty()) {
		return;
	}

	SDL_Rect srcRect{ width * currentFrame, height * currentRow,
					  width, height };
	SDL_Rect destRect{ x, y, width, height };

	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	SDL_RenderCopyEx(renderer, m_textureMap[id],
					 &srcRect, &destRect, angle, 0, flip);
}


void TextureManager::DrawTile(const std::string& id, int32_t margin, int32_t spacing,
							  int32_t x, int32_t y, int32_t width, int32_t height,
							  int32_t currentRow, int32_t currentFrame,
							  SDL_Renderer* renderer) {
	if(id.empty()) {
		return;
	}

	SDL_Rect srcRect{
		margin + (spacing + width) * currentFrame,
		 margin + (spacing + height) * currentRow,
		width, height
	};
	SDL_Rect destRect{ x, y, width, height };
	SDL_RenderCopyEx(renderer, m_textureMap[id],
					 &srcRect, &destRect, 0, 0,
					 SDL_FLIP_NONE);
}


void TextureManager::ClearFromTextureMap(const std::string& id) {
	if(id.empty()) {
		return;
	}

	SDL_DestroyTexture(m_textureMap[id]);
	m_textureMap.erase(id);
}


std::unordered_map<std::string, SDL_Texture*>& TextureManager::GetTextureMap() {
	return m_textureMap;
}


SDL_Texture* TextureManager::GetTexture(const std::string& id) {
	return m_textureMap[id];
}

} // namespace Engine
