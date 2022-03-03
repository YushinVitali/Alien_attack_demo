/// @file game_object_factory.hpp
/// @brief Description of the abstract game object factory.
#pragma once

#ifndef __GAME_OBJECT_FACTORY_HPP__
#define __GAME_OBJECT_FACTORY_HPP__


#include <string>
#include <unordered_map>

#include <game_objects/game_object.hpp>


namespace Engine {

class BaseCreator {
public:
	virtual ~BaseCreator() = default;

	virtual GameObject* CreateGameObject() const = 0;
}; // class BaseCreator


/// @brief Abstract Game Object Factory.
class GameObjectFactory {
public:
	~GameObjectFactory();

	static GameObjectFactory* Instance();

	bool RegisterType(const std::string& typeId, BaseCreator* creator);
	GameObject* Create(const std::string& typeId);

private:
	GameObjectFactory() = default;

private:
	static GameObjectFactory* m_instance;

	std::unordered_map<std::string, BaseCreator*> m_creators;
}; // class GameObjectFactory

} // namespace Engine


#endif // !defined(__GAME_OBJECT_FACTORY_HPP__)
