#ifndef SCORESCENE_H
#define SCORESCENE_H
#include "BaseScene.h"
#include "GameOverScene.h"
#include "IntroScene.h"

class ScoreScene : public BaseScene{
public:
	ScoreScene(sf::Vector2f l_centerView);
	ScoreScene();
	~ScoreScene();
	
	void onCreate(TextureMap &l_textureMap);
	void onDestroy();
	
	void activate();
	void deactivate();

	void readTabla();
		
	void update(const sf::Time& l_time, Game &g);
	void draw(sf::RenderWindow &w);

	void processEvent(const sf::Event &e);
private:
	sf::Sprite m_introSprite;
	sf::Font m_font, m_fontPuntaje;
	sf::Text m_puntaje, m_pos4, m_pos1, m_pos2, m_pos3, m_pos0, 
	m_namePos4, m_namePos1, m_namePos2, m_namePos3, m_namePos0, m_escape;
	
	std::vector<Tabla> m_vTabla;
	std::vector<sf::Text> m_textos;	
	std::map<int,std::pair<std::string, std::string>> *toText;
};

#endif

