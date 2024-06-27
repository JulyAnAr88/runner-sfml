#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Hitbox.h"

class Entity {
protected:
	sf::Texture m_tex;
	sf::Sprite m_spr;	
	sf::Vector2f velocity;	
	sf::Vector2f acceleration;
	
public:	
	Entity();        			
	virtual void draw(sf::RenderTarget &tar) = 0;   
	virtual void update(double elapsed) = 0;
	sf::FloatRect getGlobalBounds();
	bool collideWith(const Entity & ent2);
	sf::Sprite &getSprite();
	sf::Vector2f getPosition() const; //Returns the current player position
	sf::FloatRect checkCollision(Entity &b);
	~Entity() {};
};

#endif

