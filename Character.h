#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"
#include "Direction.h"
#include "SpriteSheet.h"

class Character : public Entity{
friend class EntityManager;
public:
	Character();
	virtual ~Character();

	void move(const Direction& l_dir);

	void jump();
	void takeDamage(const int& l_damage);

	void load(const std::string& l_path);

	virtual void update(float l_dT);
	void draw(sf::RenderWindow* l_wind);
protected:
	
	void animate();
	SpriteSheet m_spriteSheet;
	float m_jumpVelocity;
	Direction m_dir;

	int m_hitpoints;

};

#endif

