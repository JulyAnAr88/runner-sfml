#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Constants.h"
#include <iostream>


int main(int argc, char *argv[]){
	{
		Game &game = Game::create(sf::VideoMode(WIDTH,HEIGHT),"Carrera al bachi");
		while(!game.getWindow()->isDone()){
			game.update();
			game.render();
			game.lateUpdate();
		}
	}
		
	system("PAUSE");
}

