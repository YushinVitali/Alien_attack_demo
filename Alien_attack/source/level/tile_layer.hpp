/// @file tile_layer.hpp
/// @brief Description of the tile display layer.
#pragma once

#ifndef __TILE_LAYER_HPP__
#define __TILE_LAYER_HPP__


#include <cstdint>
#include <vector>

#include <SDL.h>

#include <level/level.hpp>
#include <level/layer.hpp>
#include <level/tileset.hpp>

#include <math/vector_2d.hpp>


namespace Engine {

/// @brief Layer of tiles.
class TileLayer : public Layer {
public:
	TileLayer(int32_t tileSize, const std::vector<Tileset>& tilesets);
	virtual ~TileLayer() override;

	virtual void Update(Level* level) override;
	virtual void Render() override;

	void SetTileIds(const std::vector<std::vector<int32_t>>& data);
	void SetTileIds(std::vector<std::vector<int32_t>>&& data);

	void SetTileSize(int32_t tileSize);

	void SetMapWidth(int32_t mapWidth);
	void SetMapHeight(int32_t mapHeight);

	Tileset GetTilesetById(int32_t tileId) const;

	const std::vector<std::vector<int32_t>>& GetTileIds() const;

	Vector2D GetPosition() const;
	SDL_Rect GetRect() const;
	int32_t GetTileSize() const;

private:
	const std::vector<Tileset>& m_tilesets;
	std::vector<std::vector<int32_t>> m_tileIds;

	Vector2D m_position;
	Vector2D m_velocity;

	int32_t m_numberColumns;
	int32_t m_numberRows;
	int32_t m_tileSize;

	int32_t m_mapWidth;
	int32_t m_mapHeight;
}; // class TileLayer

} // namespace Engine


#endif // !defined(__TILE_LAYER_HPP__)
