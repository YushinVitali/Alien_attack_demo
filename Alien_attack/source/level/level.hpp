/// @file level.hpp
/// @brief Description of the game level.
#pragma once

#ifndef __LEVEL_HPP__
#define __LEVEL_HPP__


#include <vector>
#include <memory>

#include <level/tileset.hpp>
#include <level/layer.hpp>
#include <level/tile_layer.hpp>

#include <parser/level_parser.hpp>

#include <game_objects/actor/player.hpp>


namespace Engine {

/// @brief Game level.
class Level {
public:
	~Level();

	void Update();
	void Render();
public:
	std::vector<Tileset>& GetTilesets();
	std::vector<std::shared_ptr<Layer>>& GetLayers();
	std::vector<std::weak_ptr<TileLayer>>& GetCollisionLayers();

	void SetPlayer(std::weak_ptr<Actor::Player> player);
	const std::weak_ptr<Actor::Player>& GetPlayer();

private:
	friend class LevelParser;
	Level() = default;

private:
	std::vector<Tileset> m_tilests;
	std::vector<std::shared_ptr<Layer>> m_layers;
	std::vector<std::weak_ptr<TileLayer>> m_collisionLayers;

	std::weak_ptr<Actor::Player> m_player;
}; // class Level

} // namespace Engine


#endif // !defined(__LEVEL_HPP__)
