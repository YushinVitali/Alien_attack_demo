/// @file game_object_factory.cpp
/// @brief Implementing of the abstract game object factory
#include <game_objects/game_object_factory.hpp>

#include <logger.hpp>


namespace Engine {

GameObjectFactory* GameObjectFactory::m_instance{ nullptr };


GameObjectFactory::~GameObjectFactory() {
	for(auto& creator : m_creators) {
		delete creator.second;
	}
	m_creators.clear();
}


GameObjectFactory* GameObjectFactory::Instance() {
	if(!m_instance) {
		m_instance = new GameObjectFactory();
	}
	return m_instance;
}


bool GameObjectFactory::RegisterType(const std::string& typeId, BaseCreator* creator) {
	const std::unordered_map<std::string, BaseCreator*>::const_iterator it{ m_creators.find(typeId) };
	if(it != m_creators.end()) {
		delete creator;
		return false;
	}

	m_creators[typeId] = creator;

	return true;
}


GameObject* GameObjectFactory::Create(const std::string& typeId) {
	const std::unordered_map<std::string, BaseCreator*>::const_iterator creator{
		m_creators.find(typeId)
	};
	if(m_creators.end() == creator) {
		lout(LOG_TYPE::ERROR, "Could not find type: " + typeId);
		return nullptr;
	}
	return creator->second->CreateGameObject();
}

} // namespace Engine
