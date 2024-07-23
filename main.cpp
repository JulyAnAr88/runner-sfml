#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameScene.h"
#include "IntroScene.h"
#include "GameOverScene.h"
#include "SharedContext.h"
#include "ScoreScene.h"


int main(int argc, char *argv[]){
	SharedContext* m_context;
	BaseScene *scene = new IntroScene();
	//BaseScene *scene = new ScoreScene();
	Game &g = Game::create(sf::VideoMode(WIDTH,HEIGHT), scene, "Carrera al bachi");
	g.run();
	
	return 0;
}

