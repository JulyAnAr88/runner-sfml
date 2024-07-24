#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Music.hpp>
#include <vector>
#include <map>
#include "Game.h"
#include "Player.h"
#include "BaseScene.h"
#include "Land.h"
class Land;
class HUD;

class GameScene : public BaseScene {
public:
	GameScene();

	void onCreate(TextureMap &l_textureMap);
	void onDestroy();

	void update(const sf::Time& l_time, Game &g);
	void draw(sf::RenderWindow &w);
	void processEvent(const sf::Event &e);

	~GameScene();
protected:
	sf::Music m_music;

	Land* m_terreno;

	int m_puntos = 0;		
	float pos_view_x = 0;
	sf::Clock m_clock;

	HUD* m_hud;
	TextureMap* m_tm;

};

#endif
