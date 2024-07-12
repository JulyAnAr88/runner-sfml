#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "Map.h"
#include "BaseScene.h"
#include "EventManager.h"

class GameScene : public BaseScene {
public:
	GameScene(SceneManager* l_sceneManager);
	
	void onCreate();
	void onDestroy();

	void activate();
	void deactivate();

	void update(const sf::Time& l_time);
	void draw();

	void MainMenu(EventDetails* l_details);
	void Pause(EventDetails* l_details);
	//void ToggleOverlay(EventDetails* l_details);
	~GameScene();
private:
	Map* m_gameMap;

};

#endif
