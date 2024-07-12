#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "SharedContext.h"
#include "BaseScene.h"
#include "GameScene.h"
#include "PausedScene.h"
#include "IntroScene.h"
#include "MainMenuScene.h"
#include <vector>
#include <map>

class BaseScene;

enum class SceneType{ Intro = 1, MainMenu, Game, Paused, GameOver, Credits };

// Scene container.
using SceneContainer = std::vector<std::pair<SceneType, BaseScene*>>;
// Type container.
using TypeContainer = std::vector<SceneType>;
// Scene factory.
using SceneFactory = std::map<SceneType, std::function<BaseScene*(void)>>;

class SceneManager{
public:
	SceneManager(SharedContext* l_shared);
	~SceneManager();

	void update(const sf::Time& l_time);
	void draw();

	void processRequests();

	SharedContext* getContext();
	bool hasScene(const SceneType& l_type);

	void switchTo(const SceneType& l_type);
	void remove(const SceneType& l_type);
private:
	// Methods.
	void createScene(const SceneType& l_type);
	void removeScene(const SceneType& l_type);

	template<class T>
	void registerScene(const SceneType& l_type){
		m_sceneFactory[l_type] = [this]() -> BaseScene*
		{
			return new T(this);
		};
	}

	// Members.
	SharedContext* m_shared;
	SceneContainer m_scenes;
	TypeContainer m_toRemove;
	SceneFactory m_sceneFactory;
};

#endif

