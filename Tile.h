#ifndef TILE_H
#define TILE_H
#include "Entity.h"
#include "SpriteSheet.h"
#include <SFML/Graphics.hpp>

class Tile : public Entity{
public:
	Tile();
	~Tile();
	void onEntityCollision(Entity* l_collider, bool l_attack);

	void load(const std::string& l_path);
	int getAnimId();
	
	void setAnimId(int l_animId);

	void update(float l_dT);
	void draw(sf::RenderWindow* l_wind);

protected:
	void animate();

	SpriteSheet m_spriteSheet;
	int m_animId;
	std::vector<int> m_vId;
};

#endif

