/// @file object_layer.cpp
/// @brief Implementation of the object display layer.
#include <level/object_layer.hpp>

#include <memory>

#include <game.hpp>

#include <SDL.h>


namespace Engine {

ObjectLayer::~ObjectLayer() {
	m_gameObjects.clear();
}


void ObjectLayer::Update(Level* level) {
	if(!level) {
		return;
	}
	auto player = level->GetPlayer();

	m_collisionManager.CheckPlayerEnemyBulletCollision(player);
	m_collisionManager.CheckEnemyPlayerBulletCollision(m_gameObjects);
	m_collisionManager.CheckPlayerEnemyCollision(player, m_gameObjects);

	const auto windowSize{ Game::Instance()->GetWindowSize() };
	if (std::shared_ptr<Actor::Player> sPlayer = player.lock()) {
		if(sPlayer->GetPosition().GetX() + sPlayer->GetWidth() < windowSize.width) {
			m_collisionManager.CheckPlayerTileCollision(player, level->GetCollisionLayers());
		}
	}

	for(auto object = m_gameObjects.begin(); object != m_gameObjects.end();) {
		const bool isObjectInVisiableArea{
			(*object)->GetPosition().GetX() <= windowSize.width &&
			(*object)->GetPosition().GetY() <= windowSize.height
		};
		if(isObjectInVisiableArea) {
			(*object)->SetUpdating(true);
			(*object)->Update();
		} else {
			if(std::string{ "Player" } != (*object)->Type()) {
				(*object)->SetUpdating(false);
				(*object)->Scroll(Game::Instance()->GetScrollSpeed());
			} else {
				(*object)->SetUpdating(true);
				(*object)->Update();
			}
		}

		if((*object)->GetPosition().GetX() < (0 - (*object)->GetWidth()) ||
				(*object)->GetPosition().GetY() > windowSize.height ||
				(*object)->isDead()) {
			object = m_gameObjects.erase(object);
			continue;
		} else {
			++object;
		}
	}
}


void ObjectLayer::Render() {
	for(const auto& object : m_gameObjects) {
		const bool isObjectInVisiableArea{
			object->GetPosition().GetX() <= Game::Instance()->GetWindowSize().width &&
			object->GetPosition().GetY() <= Game::Instance()->GetWindowSize().height
		};
		if(isObjectInVisiableArea) {
			object->Draw();
		}
	}
}


std::vector<std::shared_ptr<GameObject>>& ObjectLayer::GetGameObject() {
	return m_gameObjects;
}

} // namespace Engine
