#ifndef GAME_H
#define GAME_H
#include "SceneBase.h"
#include <SFML/Graphics/RenderWindow.hpp>

class SceneBase;

/***
* Clase para manejar un bucle de juego con distintas escenas
*/

class Game {
public:
	
	void run();
	
	void switchScene(SceneBase *scene);
	
	static Game &getInstance();
	
	/// crear un juego especificando el modo de video y la escena inicial
	static Game &create(const sf::VideoMode &videoMode, SceneBase *scene, const std::string &name = "");
	
	void loadTextures();
	// Para el sistema de puntajes
	void InitHighScore();//passes the data from the Tanto file to a vector of scores
	/*void AddScore(hsStruct score);//if the score is higher than the last score saved, it add the score to the scores vector
	std::vector<hsStruct> getHighscore();
	void saveScores();
	sf::RenderWindow& getWindow();*/
	
private:
	Game();
	
	void processEvents();
	void update();
	void draw();
	static Game *instance;
	
	sf::RenderWindow m_window;
	sf::Event m_ev;
	sf::Clock m_clock;
	
	SceneBase *m_current_scene, *m_next_scene = nullptr;
	
	~Game();
	
	//std::vector<hsStruct> Scores; 
	//hsStruct aux;
	
};


#endif
