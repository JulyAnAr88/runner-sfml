#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "Tile.h"
class Environment : public Tile{
public:
	Environment(EntityManager* l_entityMgr);
	~Environment();

	void onEntityCollision(Entity* l_collider);
	
};

#endif

