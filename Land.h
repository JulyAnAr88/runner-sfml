#ifndef LAND_H
#define LAND_H
#include <vector>
#include <functional>
#include "Entity.h"
#include "Enemy.h"
#include "Tile.h"
#include "HUD.h"
#include "Player.h"
#include "GameScene.h" 

class Game;

using EntityContainer = std::map<unsigned int, Entity*>;
using EntityFactory = std::map<EntityType, std::function<Entity*(void)>>;
using EnemyTypes = std::map<std::string, std::string>;
using TilesTypes = std::map<std::string, std::string>;
using TilesMap = std::map<unsigned int, std::pair<unsigned int, sf::Vector2f>>;
struct TextureMap;

class Land {
public:
	Land(TextureMap &l_textureMap);
	/// agrega una nueva entidad a la escena
	int add(const EntityType& l_type, const std::string& l_name = "");
			
	/// elimina una antidad de la escena
	void remove(int l_id);

	void loadMap(const std::string& l_path);
	void loadTilesTypes(const std::string& l_path);
	void loadEnemyTypes(const std::string& l_path);
	void loadNext();

	Entity *findEntity(unsigned int l_id);
	Entity *findEntity(const std::string& l_name);

	float getGravity();
	sf::Vector2f getPlayerPosition();
	sf::View getView();	
	sf::FloatRect getViewSpace(sf::RenderWindow &l_window);
	int getPoints();
	std::string getTime();

	void setView(sf::View &l_view);
	bool playerIsDead();
	bool exito();
	
	void update(double elapsed,Game &g);
	void draw(sf::RenderWindow &w);
	
	~Land();
private:
	template<class T>
	void registerEntity(const EntityType& l_type){
		m_entityFactory[l_type] = [this]() -> Entity*
		{
			return new T();
		};
	}

	void purgeMap();
	void processRemovals();

	sf::Sprite m_background;	
	sf::Vector2u m_maxMapSize;
	sf::Vector2f m_playerStart;
	sf::Vector2f m_defaultFriction;
	unsigned int m_tileCount;
	unsigned int m_tileSetCount;
	float m_mapGravity;
	std::string m_nextMap;
	bool m_loadNextMap;
	std::string m_backgroundTexture;
	BaseScene* m_currentScene;
	sf::View *m_view;

	int m_idTiles = 0;
	int m_idEntities = 0;

	int m_cantEnemies = 0;
	bool m_exito;

	EntityContainer m_entities;
	Player* m_player;
	std::vector<Tile *> m_tiles;
	std::vector<int> to_delete;

	TextureMap *m_tM;
	EnemyTypes m_enemyTypes;
	TilesTypes m_tilesTypes;
	TilesMap m_tilesMap;
	EntityFactory m_entityFactory;

	int m_greenFlag = 0;
	int m_redFlag = 0;
	
	double m_timePassedMosquito = 0.0;
    double m_timePassedSnake = 0.0;
    double m_timePassedObject = 0.0;
    double m_timePassedObstacle = 0.0;
	HUD *m_hud;
};

#endif

