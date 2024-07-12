#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <map>
#include <array>
#include <fstream>
#include <sstream>
#include "SharedContext.h"
#include "BaseScene.h"

class BaseScene;

enum Sheet{ Tile_Size = 32, Sheet_Width = 256, Sheet_Height = 256};

using TileID = unsigned int;

struct TileInfo{
	TileInfo(SharedContext* l_context, 
		const std::string& l_texture = "", TileID l_id = 0)
		: m_context(l_context), m_id(0), m_deadly(false)
	{
		TextureManager* tmgr = l_context->m_textureManager;
		if (l_texture == ""){ m_id = l_id; return; }
		if (!tmgr->requireResource(l_texture)){ return; }
		m_texture = l_texture;
		m_id = l_id;
		m_sprite.setTexture(*tmgr->getResource(m_texture));
		sf::IntRect tileBoundaries(m_id % (Sheet::Sheet_Width / Sheet::Tile_Size) * Sheet::Tile_Size,
			m_id / (Sheet::Sheet_Height / Sheet::Tile_Size) * Sheet::Tile_Size,
			Sheet::Tile_Size,Sheet::Tile_Size);
		m_sprite.setTextureRect(tileBoundaries);
	}

	~TileInfo(){
		if (m_texture == ""){ return; }
		m_context->m_textureManager->releaseResource(m_texture);
	}

	sf::Sprite m_sprite;

	TileID m_id;
	std::string m_name;
	sf::Vector2f m_friction;
	bool m_deadly;

	SharedContext* m_context;
	std::string m_texture;
};

struct Tile{
	TileInfo* m_properties;
	bool m_warp; // Is the tile a warp.
	// Other flags unique to each tile.
};

using TileMap = std::map<TileID,Tile*>;
using TileSet = std::map<TileID,TileInfo*>;

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
	void loadTiles(const std::string& l_path);
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
};

#endif

