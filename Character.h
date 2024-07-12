#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "SpriteSheet.h"

class Character : public Entity{
friend class EntityManager;
public:
	Character(EntityManager* l_entityMgr);
	virtual ~Character();

	void move(const Direction& l_dir);

	void jump();
	void getHurt(const int& l_damage);

	void load(const std::string& l_path);

	/* virtual void OnEntityCollision(
		EntityBase* l_collider, bool l_attack) = 0; */

	virtual void update(float l_dT);
	void draw(sf::RenderWindow* l_wind);
protected:
	
	void animate();
	SpriteSheet m_spriteSheet;
	float m_jumpVelocity;

	int m_hitpoints;

};

#endif

