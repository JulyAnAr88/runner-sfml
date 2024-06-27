#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameScene.h"
#include "Constants.h"


int main(int argc, char *argv[]){
	SceneBase *scene = new GameScene();
	Game &g = Game::create(sf::VideoMode(WIDTH,HEIGHT), scene, "Carrera al bachi");
	g.run();
	
	return 0;
}

