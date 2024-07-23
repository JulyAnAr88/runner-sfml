#ifndef HUD_H
#define HUD_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include "BaseScene.h"

class HUD{
public:
	HUD(TextureMap &l_tm);

	void setView(sf::View &l_view);

	void update(double elapsed);
	void draw(sf::RenderWindow &w);
	void processEvent(const sf::Event &e);

	void setPosition(float x, float y);
	void setPlayerHP(int l_hp);

	std::string getTime();
	int getScore();
	void load(const std::string& l_path);
private:

	sf::View m_view;
	sf::Font m_scoreFont;
	sf::Text m_scorePrint;
	std::string m_scoreToPrint;
	sf::Text m_scoreText;
	sf::Clock m_clock;
	std::string m_timer;

	sf::Sprite m_heart0, m_heart1,
	m_heart2, m_heart3, m_heart4,m_heart5;

	sf::Vector2f m_position;

	int m_hitpointsPlayer;
	int m_puntos = 0;

	TextureMap *m_tm;
	SpriteSheet m_spriteSheet;
};

#endif

