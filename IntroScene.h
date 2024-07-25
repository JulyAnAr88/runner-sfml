#ifndef INTROSCENE_H
#define INTROSCENE_H
#include "BaseScene.h"
#include "SharedContext.h"
class Game;

class IntroScene : public BaseScene{
public:
	IntroScene(sf::Vector2f l_centerView);
	IntroScene();
	~IntroScene();
	
	void onCreate(TextureMap &l_textureMap);
	void onDestroy();
	
	void activate();
	void deactivate();
	
	void update(const sf::Time& l_time, Game &g);
	void draw(sf::RenderWindow &w);

	void processEvent(const sf::Event &e);
	
private:
	sf::Sprite m_introSprite;
	sf::Font m_font, m_fontTitle;
	sf::Text m_textTitle, m_text;

	sf::Vector2f m_centerView = {WIDTH / 2.0f, HEIGHT / 2.0f};
};
#endif