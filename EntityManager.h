#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include <functional>
#include "Player.h"
#include "Enemy.h"

using EntityContainer = std::map<unsigned int,Entity*>;
using EntityFactory = std::map<EntityType, std::function<Entity*(void)>>;
using EnemyTypes = std::map<std::string,std::string>;

struct SharedContext;

class EntityManager{
public:
	EntityManager(SharedContext* l_context, unsigned int l_maxEntities);
	~EntityManager();

	int add(const EntityType& l_type, const std::string& l_name = "");
	Entity* find(unsigned int l_id);
	Entity* find(const std::string& l_name);
	void remove(unsigned int l_id);

	void update(float l_dT);
	void draw();

	void purge();

	SharedContext* getContext();
private:
	template<class T>
	void registerEntity(const EntityType& l_type){
		m_entityFactory[l_type] = [this]() -> Entity*
		{
			return new T(this);
		};
	}

	void processRemovals();
	void loadEnemyTypes(const std::string& l_name);
	/* void entityCollisionCheck(); */

	EntityContainer m_entities;
	EnemyTypes m_enemyTypes;
	EntityFactory m_entityFactory;
	SharedContext* m_context;
	unsigned int m_idCounter;
	unsigned int m_maxEntities;

	std::vector<unsigned int> m_entitiesToRemove;
};

#endif

