#ifndef BASESCENE_H
#define BASESCENE_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
class SceneManager;
/**
 * Escena de la que heredarán todas las del juego
 */
class BaseScene {
	friend class SceneManager;
protected:
	SceneManager* m_sceneMgr;
	bool m_transparent;
	bool m_transcendent;
	sf::View m_view;
public:
	BaseScene(SceneManager* l_sceneManager) 
		:m_sceneMgr(l_sceneManager), m_transparent(false){};
	virtual ~BaseScene(){};

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;

	virtual void activate() = 0;
	virtual void deactivate() = 0;

	virtual void update(const sf::Time& l_time) = 0;
	virtual void draw() = 0;

	void setTransparent(const bool& l_transparent){ m_transparent = l_transparent; }
	bool isTransparent()const{ return m_transparent; }
	void setTranscendent(const bool& l_transcendence){ m_transcendent = l_transcendence; }
	bool isTranscendent()const{ return m_transcendent; }
	sf::View& getView(){ return m_view; }
	SceneManager* getSceneManager(){ return m_sceneMgr; }

};

#endif
