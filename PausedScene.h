#ifndef PAUSEDSCENE_H
#define PAUSEDSCENE_H
#include "BaseScene.h"
#include "EventManager.h"

class PausedScene : public BaseScene{
public:
	PausedScene(SceneManager *l_sceneManager);
	~PausedScene();

	void onCreate();
	void onDestroy();

	void activate();
	void deactivate();

	void update(const sf::Time &l_time);
	void draw();

	void Unpause(EventDetails *l_details);

private:
	sf::Font m_font;
	sf::Text m_text;
	sf::RectangleShape m_rect;
};

#endif
