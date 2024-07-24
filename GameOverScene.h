#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H
#include "BaseScene.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Game.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <vector>

struct Tabla{
	int puntos;
	char nombre[4];
};


class GameOverScene : public BaseScene{
public:
	GameOverScene(int l_score, std::string l_time, bool exito,sf::Vector2f l_centerView);
	~GameOverScene();

	void onCreate(TextureMap &l_textureMap);
	void onDestroy();
	
	void activate();
	void deactivate();

	void saveScore(int l_p, std::string l_n);
	
	void update(const sf::Time& l_time, Game &g);
	void draw(sf::RenderWindow &w);

	void processEvent(const sf::Event &e);

private:
	sf::Font m_font, m_fontGameOver;
	sf::Text m_gameOver, m_textName, m_time, m_textTime, m_score, m_textScore, m_space,
		m_pos1, m_pos2, m_pos3, m_pos0;
	
	int m_newScore;
	std::string m_newName, m_newTime;
	std::vector<sf::Text> m_toPrint;
	std::vector<Tabla> m_vTabla;

	sf::Music m_music;

	char pos0='-';
	char pos1='-';
	char pos2='-';
	char pos3='-';

};

#endif

