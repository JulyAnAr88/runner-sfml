#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Environment{
public:
	Environment(const sf::Vector2f &pos, int tile);
	void update(double elapsed);				
	void draw(sf::RenderTarget & target);
	sf::FloatRect getGlobalBounds();
	sf::Sprite &getSprite();
	sf::Vector2f getPosition() const; 
private:
	sf::Texture m_tex;
	sf::Sprite m_spr;	
	sf::Vector2f m_pos;
};

#endif

