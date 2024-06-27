#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <thread>
#include "Game.h"
#include "Land.h"
#include "Player.h"
#include "Platform.h"
#include "SceneBase.h"
class Game;
class Player;
class SceneBase;

class GameScene : public SceneBase {
public:
	GameScene();
	void update(float elapsed);
	void draw(sf::RenderWindow &w);
	void processEvent(const sf::Event &e);
	
	void createNewEntity(float velMin);
	
	/// agrega una nueva entidad a la escena
	void add(Entity *e);
	
	void addLand(Land *l);
	
	void addPlayer(Player *p);
	
	/// elimina una antidad de la escena
	void remove(Entity *e);
	
	void addBackgrounds(sf::Sprite *back);
	
	void addBackgrounds(std::vector<sf::Sprite*> back);
	~GameScene();
private:
	Player* m_player;
	Land* m_terreno;
	std::vector<Entity *> entities;
	std::vector<Entity *> to_delete;
	std::vector<sf::Sprite *> backgrounds;
	std::vector<Platform> m_platform;
	std::vector<sf::Texture> m_fondo;
	std::vector<sf::Sprite> m_inicio;
	sf::Clock m_time_new_entity;
	float m_vel_min;
	float pos_view_x = 0.f;// = WIDTH/4.1f;
	sf::View* pl_view;
	sf::Clock m_clock;

};

#endif
