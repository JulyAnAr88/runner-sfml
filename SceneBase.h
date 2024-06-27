#ifndef SCENEBASE_H
#define SCENEBASE_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Game;

/**
 * Escena de la que heredarán todas las del juego
 */
class SceneBase {
private:
	
public:
	SceneBase();
	
	virtual void update(float elapsed);
	
	virtual void draw(sf::RenderWindow &w);
	
	/// notifica a la escena de un evento
	virtual void processEvent(const sf::Event &e) = 0;
	
	virtual ~SceneBase(){};
};

#endif
