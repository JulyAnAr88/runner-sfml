#pragma once
#include "Character.h"

class SharedContext;

class Player : public Character{
public:
	Player();
	~Player();
	
	void onEntityCollision(Entity* l_collider, bool l_attack);
	
	void separate(sf::FloatRect overlap, const Entity & ent2);
	int getHitpoints();
	void die();
	bool IsDead();

	void update(float l_dT);
private:
	bool canJump = true;
	bool isJumping = false;	
	bool isDead = false;

	float m_corriendo = 0.0;

};


