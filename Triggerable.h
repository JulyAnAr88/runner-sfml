#ifndef TRIGGERABLE_H
#define TRIGGERABLE_H
#include "Tile.h"

class Triggerable : public Tile {
public:
	Triggerable(EntityManager* l_entityMgr);
	~Triggerable();

	void onEntityCollision(Entity* l_collider);
	void update(float l_dT);
private:
};

#endif

