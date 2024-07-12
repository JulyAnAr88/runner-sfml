#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character{
public:
	Enemy(EntityManager* l_entityMgr);
	~Enemy();

	void onEntityCollision(Entity* l_collider, bool l_attack);
	void update(float l_dT);
private:
	sf::Vector2f m_destination;
	bool m_hasDestination;
};

#endif

