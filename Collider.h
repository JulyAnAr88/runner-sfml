#ifndef COLLIDER_H
#define COLLIDER_H
#include "Tile.h"

class Collider : public Tile {
public:
	Collider(EntityManager* l_entityMgr);
	~Collider();

	void onEntityCollision(Entity* l_collider);
	void update(float l_dT);
private:
};

#endif

