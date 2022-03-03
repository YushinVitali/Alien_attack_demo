/// @file level.cpp
/// @brief Implementation of the game level.
#include <level/level.hpp>

#include <logger.hpp>

#include <texture_manager.hpp>


namespace Engine {

Level::~Level() {
	m_layers.clear();
	m_collisionLayers.clear();
	m_tilests.clear();
}


void Level::Update() {
	for(const auto& layer : m_layers) {
		layer->Update(this);
	}
}


void Level::Render() {
	for(const auto& layer : m_layers) {
		layer->Render();
	}
}


std::vector<Tileset>& Level::GetTilesets() {
	return m_tilests;
}


std::vector<std::shared_ptr<Layer>>& Level::GetLayers() {
	return m_layers;
}


std::vector<std::weak_ptr<TileLayer>>& Level::GetCollisionLayers() {
	return m_collisionLayers;
}


void Level::SetPlayer(std::weak_ptr<Actor::Player> player) {
	m_player = std::move(player);
}


const std::weak_ptr<Actor::Player>& Level::GetPlayer() {
	return m_player;
}

} // namespace Engine
