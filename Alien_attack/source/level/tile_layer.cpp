/// @file tile_layer.cpp
/// @brief Implementation of the tile display layer.
#include <level/tile_layer.hpp>

#include <algorithm>

#include <SDL.h>

#include <logger.hpp>

#include <game.hpp>
#include <texture_manager.hpp>


namespace Engine {

TileLayer::TileLayer(int32_t tileSize, const std::vector<Tileset>& tilesets)
					: m_tilesets(tilesets), m_tileSize(tileSize) {
	m_numberColumns = Game::Instance()->GetWindowSize().width / tileSize + 1;
	m_numberRows = Game::Instance()->GetWindowSize().height / m_tileSize;
}


TileLayer::~TileLayer() {
	for(const auto& tileset : m_tilesets) {
		TextureManager::Instance()->ClearFromTextureMap(tileset.name);
	}
}


void TileLayer::Update(Level* level) {
	if(m_position.GetX() < ((m_mapWidth * m_tileSize) - Game::Instance()->GetWindowSize().width) - m_tileSize) {
		m_velocity.SetX(Game::Instance()->GetScrollSpeed());
		m_position += m_velocity;
	} else {
		m_velocity.SetX(0);
	}
}


void TileLayer::Render() {
	SDL_Point firstPoint{ static_cast<int32_t>(m_position.GetX()) / m_tileSize,
						  static_cast<int32_t>(m_position.GetY()) / m_tileSize };
	SDL_Point secondPoint{ static_cast<int32_t>(m_position.GetX()) % m_tileSize,
						   static_cast<int32_t>(m_position.GetY()) % m_tileSize };
	for(int32_t row = 0; row < m_numberRows; ++row) {
		for(int32_t col = 0; col <= m_numberColumns; ++col) {
			if(static_cast<int64_t>(m_tileIds.size()) <= row + firstPoint.y ||
					static_cast<int64_t>(m_tileIds.front().size()) <= col + firstPoint.x) {
				continue;
			}

			int32_t id{ m_tileIds.at(row + firstPoint.y).at(col + firstPoint.x) };

			if(0 == id) {
				continue;
			}
			Tileset tileset{ GetTilesetById(id) };
			--id;

			const SDL_Rect tile{
				(col * m_tileSize) - secondPoint.x,
				(row * m_tileSize) - secondPoint.y,
				m_tileSize, m_tileSize
			};

			tileset.numberColumns = tileset.numberColumns == 0 ? 1 : tileset.numberColumns;
			const int32_t currentRow{ (id - (tileset.firstGridId - 1)) / tileset.numberColumns };
			const int32_t currentFrame{ (id - (tileset.firstGridId - 1)) % tileset.numberColumns };
			TextureManager::Instance()->DrawTile(tileset.name, tileset.margin, tileset.spacing,
												 tile.x, tile.y, tile.w, tile.h,
												 currentRow, currentFrame,
												 Game::Instance()->GetRenderer());
		}
	}
}


void TileLayer::SetTileIds(const std::vector<std::vector<int32_t>>& data) {
	m_tileIds = data;
}


void TileLayer::SetTileIds(std::vector<std::vector<int32_t>>&& data) {
	std::swap(m_tileIds, data);
}


void TileLayer::SetTileSize(int32_t tileSize) {
	m_tileSize = tileSize;
}


void TileLayer::SetMapWidth(int32_t mapWidth) {
	m_mapWidth = mapWidth;
}


void TileLayer::SetMapHeight(int32_t mapHeight) {
	m_mapHeight = mapHeight;
}


Tileset TileLayer::GetTilesetById(int32_t tileId) const {
	if(m_tilesets.empty()) {
		lout(LOG_TYPE::WARNING, "An attempt was made to search in an empty set of tiles!");
		return {};
	}

	for(size_t i = 0; i < m_tilesets.size() - 1; ++i) {
		if(tileId >= m_tilesets[i].firstGridId &&
				tileId < m_tilesets[i + 1].firstGridId) {
			return m_tilesets[i];
		}
	}

	return m_tilesets.back();
}


const std::vector<std::vector<int32_t>>& TileLayer::GetTileIds() const {
	return m_tileIds;
}


Vector2D TileLayer::GetPosition() const {
	return m_position;
}


SDL_Rect TileLayer::GetRect() const {
	return {
		static_cast<int32_t>(m_position.GetX()),
		static_cast<int32_t>(m_position.GetY()),
		m_mapWidth, m_mapHeight
	};
}


int32_t TileLayer::GetTileSize() const {
	return m_tileSize;
}

} // namespace Engine
