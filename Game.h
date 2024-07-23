#ifndef GAME_H
#define GAME_H
#include "BaseScene.h"
#include "SharedContext.h"
#include <SFML/Graphics/RenderWindow.hpp>

class BaseScene;


using TileMap = std::map<int , sf::Texture*>;
using VariosMap = std::map<std::string, sf::Texture*>;
struct TextureMap{
	VariosMap *vm = nullptr;
	TileMap *tm = nullptr;
};

/***
* Clase para manejar un bucle de juego con distintas escenas
*/

class Game {
public:
	
	void run();
	
	void switchScene(BaseScene *scene);
	
	static Game &getInstance();
	
	/// crear un juego especificando el modo de video y la escena inicial
	static Game &create(const sf::VideoMode &videoMode, BaseScene *scene, const std::string &name = "");
	
	sf::Texture *load(const std::string &l_path);
	void loadTextures();
	void loadPaths(const std::string &l_pathFile);
	
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
	sf::View m_view;
	
	BaseScene *m_current_scene, *m_next_scene = nullptr;
	SharedContext *m_context;
	
	std::map<std::string, std::string> m_paths;
	TextureMap m_tM;
	VariosMap m_vm;
	TileMap *m_tileMs;
	
	~Game();
	
	//std::vector<hsStruct> Scores; 
	//hsStruct aux;
	
};


#endif
