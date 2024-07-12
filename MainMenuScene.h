#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H
#include "BaseScene.h"
#include "EventManager.h"

class MainMenuScene : public BaseScene {
public:
	MainMenuScene(SceneManager* l_sceneManager);
	~MainMenuScene();

	void onCreate();
	void onDestroy();
	
	void activate();
	void deactivate();
	
	void update(const sf::Time& l_time);
	void draw();

	void MouseClick(EventDetails* l_details);
private:
	sf::Font m_font;
	sf::Text m_text;

	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPos;
	unsigned int m_buttonPadding;

	sf::RectangleShape m_rects[3];
	sf::Text m_labels[3];
};

#endif

