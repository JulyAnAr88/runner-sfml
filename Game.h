#ifndef GAME_H
#define GAME_H
#include "BaseScene.h"
#include "Window.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include <SFML/Graphics/RenderWindow.hpp>

class BaseScene;

/***
 * Clase para manejar un bucle de juego con distintas escenas
 */

class Game
{
public:

	static Game &getInstance();

	/// crear un juego especificando el modo de video y la escena inicial
	static Game &create(const sf::VideoMode &videoMode, const std::string &name = "");
	
	void update();
	void render();
	void lateUpdate();

	sf::Time getElapsed();

	Window* getWindow();
private:
	Game();

	void restartClock();

	sf::Clock m_clock;
	sf::Time m_elapsed;
	SharedContext m_context;
	Window m_window;
	EntityManager m_entityManager;
	TextureManager m_textureManager;
	SceneManager m_sceneManager;
	static Game *instance;

	~Game();

};

#endif
