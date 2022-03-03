/// @file object_layer.hpp
/// @brief Description of the object display layer.
#pragma once

#ifndef __OBEJCT_LAYER_HPP__
#define __OBEJCT_LAYER_HPP__


#include <vector>
#include <memory>

#include <level/level.hpp>
#include <level/layer.hpp>

#include <game_objects/game_object.hpp>

#include <collision/collision_manager.hpp>


namespace Engine {

/// @brief Layer of objects.
class ObjectLayer : public Layer {
public:
	ObjectLayer() = default;
	virtual ~ObjectLayer() override;

	virtual void Update(Level* level) override;
	virtual void Render() override;

	std::vector<std::shared_ptr<GameObject>>& GetGameObject();

private:
	CollisionManager m_collisionManager;
	std::vector<std::shared_ptr<GameObject>> m_gameObjects;
};

} // namespace Engine


#endif // !defined(__OBEJCT_LAYER_HPP__)
