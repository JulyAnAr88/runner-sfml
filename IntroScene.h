#ifndef INTROSCENE_H
#define INTROSCENE_H
#include "BaseScene.h"
#include "EventManager.h"

class IntroScene : public BaseScene{
public:
	IntroScene(SceneManager* l_sceneManager);
	~IntroScene();
	
	void onCreate();
	void onDestroy();
	
	void activate();
	void deactivate();
	
	void update(const sf::Time& l_time);
	void draw();
	
	void Continue(EventDetails* l_details);
private:
	sf::Sprite m_introSprite;
	sf::Font m_font;
	sf::Font m_fontTitle;
	sf::Text m_textTitle;
	sf::Text m_text;
};
#endif

