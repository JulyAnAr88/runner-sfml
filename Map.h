#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <map>
#include <array>
#include <fstream>
#include <sstream>
#include "SharedContext.h"
#include "Anim_Rect.h"
#include "BaseScene.h"
#include "Entity.h"

class BaseScene;

enum Sheet{ Tile_Size = 128, Sheet_Width = 256, Sheet_Height = 256};

using TileMap = std::map<int ,Tile*>;
using TileSet = std::map<int ,TileInfo*>;

class Map{
public:
	Map(SharedContext* l_context, BaseScene* l_currentScene);
	~Map();

	Tile* getTile(unsigned int l_x, unsigned int l_y);
	TileInfo* getDefaultTile();

	float getGravity()const;
	unsigned int getTileSize()const;
	const sf::Vector2u& getMapSize()const;
	const sf::Vector2f& getPlayerStart()const;

	void loadMap(const std::string& l_path);
	void loadNext();

	void update(float l_dT);
	void draw();
private:
	// Method for converting 2D coordinates to 1D ints.
	unsigned int convertCoords(unsigned int l_x, unsigned int l_y);
	void loadTiles();
	void purgeMap();
	void purgeTileSet();

	TileSet m_tileSet;
	TileMap m_tileMap;
	sf::Sprite m_background;
	TileInfo m_defaultTile;
	sf::Vector2u m_maxMapSize;
	sf::Vector2f m_playerStart;
	unsigned int m_tileCount;
	unsigned int m_tileSetCount;
	float m_mapGravity;
	std::string m_nextMap;
	bool m_loadNextMap;
	std::string m_backgroundTexture;
	BaseScene* m_currentScene;
	SharedContext* m_context;
	std::string tilesPaths[3];

	Animations m_animations;
	Anim_Rect* m_tileAnimation;
};

#endif

