#ifndef MAP_H
#define MAP_H
#include <vector>
#include <map>
#include "Entity.h"
#include "Enemy.h"
#include "Tile.h"
#include "Player.h"
#include "BaseScene.h" 

class BaseScene;

struct TextureMap;

class Map {
public:
	Map(TextureMap &l_textureMap);
	
	void add(Tile *e);
		
	void addPlayer(Player *p);

	void addEnemy(Enemy *e);
	
	/// elimina una antidad de la escena
	void remove(Entity *e);

	void addEntityToDelete(Entity * de);
	void update(double elapsed);
	void draw(sf::RenderWindow &w);
	void clearVEntity();

	~Map();
private:
	sf::Sprite m_fondo;
	std::vector<Entity *> entities;
	std::vector<Entity *> enti_to_delete;
	Player* m_player;
	std::vector<Tile *> entitiles;
	std::vector<Enemy *> enemies;
	std::vector<Entity *> to_delete;

	TextureMap *m_tm;
};

#endif

