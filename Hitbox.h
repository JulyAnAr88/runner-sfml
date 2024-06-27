#ifndef HITBOX_H
#define HITBOX_H
#include <SFML/Graphics.hpp>

class Hitbox {
public:
	Hitbox();
	
	virtual sf::FloatRect getHitbox() = 0;
	
	static sf::FloatRect checkCollision(Hitbox &a, Hitbox &b);
private:
	
};

#endif

