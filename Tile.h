#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
/* #include "SharedContext.h" */
#include "SpriteSheet.h"
//class SpriteSheet;
class Tile : public Entity{
friend class EntityManager;
public:
	Tile(EntityManager* l_entityMgr, int l_id = 0);
	~Tile();

	void load(const std::string& l_path);

	int getFrameEnd();
	int getFrameStart();
	int getFrameTime();
	int getFrameActionStart();
	int getFrameActionEnd();
	sf::IntRect getCoordCrop();

	void setCoordCrop(int left, int top, int width, int height);

	virtual void onEntityCollision(Entity* l_collider, bool l_attack);

	virtual void update(float l_dT);
	void draw(sf::RenderWindow* l_wind);

private:

	int m_id;
	std::string m_name;
	sf::Vector2f m_friction;
	int m_frameStart;
	int m_frameEnd;
	int m_frameActionStart;
	int m_frameActionEnd;
	float m_frameTime;
	bool m_deadly;
	sf::IntRect m_coordCrop;

	//SharedContext* m_context;
	std::string m_texture;
	
	SpriteSheet* m_spriteSheet;

	void animate();

	void readIn(std::stringstream& l_stream);
};

#endif

