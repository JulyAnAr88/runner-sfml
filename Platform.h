#ifndef PLATFORM_H
#define PLATFORM_H
#include "Entity.h"
#include "Hitbox.h"
#include <SFML/Graphics.hpp>

class Platform : public Entity{
public:
	Platform(const sf::Vector2f &pos, int tile);
	void update(double elapsed) override;				
	void draw(sf::RenderTarget & target) override;
private:
	sf::Vector2f m_pos;
};

#endif

