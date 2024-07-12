#include "EntityManager.h"
#include "SharedContext.h"

EntityManager::EntityManager(SharedContext* l_context, unsigned int l_maxEntities)
	:m_context(l_context), m_maxEntities(l_maxEntities), m_idCounter(0)
{
	loadEnemyTypes("EnemyList.list");
	registerEntity<Player>(EntityType::Player);
	registerEntity<Enemy>(EntityType::Enemy);
}
EntityManager::~EntityManager(){ purge(); }

int EntityManager::add(const EntityType& l_type, const std::string& l_name)
{
	auto itr = m_entityFactory.find(l_type);
	if (itr == m_entityFactory.end()){ return -1; }
	Entity* entity = itr->second();
	entity->m_id = m_idCounter;
	if (l_name != ""){ entity->m_name = l_name; }

	m_entities.emplace(m_idCounter,entity);

	if(l_type == EntityType::Enemy){
		auto itr = m_enemyTypes.find(l_name);
		if(itr != m_enemyTypes.end()){
			Enemy* enemy = (Enemy*)entity;
			enemy->load(itr->second);
		}
	}

	++m_idCounter;
	return m_idCounter - 1;
}

Entity* EntityManager::find(const std::string& l_name){
	for(auto &itr : m_entities){
		if(itr.second->getName() == l_name){
			return itr.second;
		}
	}
	return nullptr;
}

Entity* EntityManager::find(unsigned int l_id){
	auto itr = m_entities.find(l_id);
	if (itr == m_entities.end()){ return nullptr; }
	return itr->second;
}

void EntityManager::remove(unsigned int l_id){
	m_entitiesToRemove.emplace_back(l_id);
}

void EntityManager::update(float l_dT){
	for(auto &itr : m_entities){
		itr.second->update(l_dT);
	}
	
	processRemovals();
}

void EntityManager::draw(){
	sf::RenderWindow* wnd = m_context->m_wind->getRenderWindow();
	sf::FloatRect viewSpace = m_context->m_wind->getViewSpace();
	
	for(auto &itr : m_entities){
		if (!viewSpace.intersects(itr.second->m_hitbox)){ continue; }
		itr.second->draw(wnd);
	}
}

void EntityManager::purge(){
	for (auto &itr : m_entities){
		delete itr.second;
	}
	m_entities.clear();
	m_idCounter = 0;
}

void EntityManager::processRemovals(){
	while(m_entitiesToRemove.begin() != m_entitiesToRemove.end()){
		unsigned int id = m_entitiesToRemove.back();
		auto itr = m_entities.find(id);
		if(itr != m_entities.end()){
			std::cout << "Discarding entity: " << itr->second->getId() << std::endl;
			delete itr->second;
			m_entities.erase(itr);
		}
		m_entitiesToRemove.pop_back();
	}
}

void EntityManager::entityCollisionCheck(){
	if (m_entities.empty()){ return; }
	for(auto itr = m_entities.begin(); std::next(itr) != m_entities.end(); ++itr)
	{
		for(auto itr2 = std::next(itr); itr2 != m_entities.end(); ++itr2)
		{
			if(itr->first == itr2->first){ continue; }

			// Regular AABB bounding box collision.
			if(itr->second->m_hitbox.intersects(itr2->second->m_hitbox)){
				itr->second->onEntityCollision(itr2->second, false);
				itr2->second->onEntityCollision(itr->second, false);
			}
			
		}
	}
}

void EntityManager::loadEnemyTypes(const std::string& l_name){
	std::ifstream file;
	file.open(l_name);
	if (!file.is_open()){ std::cout << "! Failed loading file: " << l_name << std::endl; return; }
	std::string line;
	while(std::getline(file,line)){
		if (line[0] == '|'){ continue; }
		std::stringstream keystream(line);
		std::string name;
		std::string charFile;
		keystream >> name >> charFile;
		m_enemyTypes.emplace(name,charFile);
	}
	file.close();
}

SharedContext* EntityManager::getContext(){ return m_context; }
