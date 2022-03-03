/// @file texture_manager.hpp
/// @brief Description of the texture loading and rendering system.
#pragma once

#ifndef __TEXTURE_MANAGER_HPP__
#define __TEXTURE_MANAGER_HPP__


#include <system_error>
#include <string>
#include <unordered_map>

#include <SDL.h>


namespace Engine {

constexpr auto ROOT_DIR_TEXTURE{ "../image/" };


/// @brief Texture loading and drawing system.
class TextureManager {
public:
	~TextureManager();

	static TextureManager* Instance();

	std::error_code Load(const std::string& filename,
						 const std::string& id,
						 SDL_Renderer* renderer);

	std::error_code LoadText(const std::string filename,
							 const std::string& id,
							 const std::string& message,
							 SDL_Color color, int32_t fontSize,
							 int32_t wrapLength,
							 SDL_Renderer* renderer);

	void Draw(const std::string& id, int32_t x, int32_t y,
			  int32_t width, int32_t height, SDL_Renderer* renderer,
			  SDL_RendererFlip flip = SDL_FLIP_NONE);

	void DrawFrame(const std::string& id, int32_t x, int32_t y,
				   int32_t width, int32_t height,
				   int32_t currentRow, int32_t currentFrame,
				   SDL_Renderer* renderer,
				   double angle, int32_t alpha,
				   SDL_RendererFlip flip = SDL_FLIP_NONE);

	void DrawTile(const std::string& id, int32_t margin, int32_t spacing,
				  int32_t x, int32_t y, int32_t width, int32_t height,
				  int32_t currentRow, int32_t currentFrame,
				  SDL_Renderer* renderer);

	void ClearFromTextureMap(const std::string& id);

	std::unordered_map<std::string, SDL_Texture*>& GetTextureMap();
	SDL_Texture* GetTexture(const std::string& id);

private:
	TextureManager() = default;

private:
	static TextureManager* m_instance;

	std::unordered_map<std::string, SDL_Texture*> m_textureMap;
}; // class TextureManager

} // namespace Engine

#endif // !defined(__TEXTURE_MANAGER_HPP__)
