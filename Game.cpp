#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameScene.h"
#include "BaseScene.h"
#include <fstream>
#include <iostream>

Game *Game::instance = nullptr;
Game::Game():m_sceneManager(&m_context), m_entityManager(&m_context, 100){
}

Game &Game::create(const sf::VideoMode &videoMode, const std::string &name)
{
	if (instance){
		std::cerr << "ERROR: can't call create(), game already running." << std::endl;
	}else{
		Game &g = getInstance();
		g.m_clock.restart();
		srand(time(nullptr));
		
		/* g.m_sceneManager = SceneManager(&g.m_context);
		g.m_entityManager = EntityManager(&g.m_context, 100); */
		g.m_window.getRenderWindow()->create(videoMode, name);
		g.m_window.getRenderWindow()->setFramerateLimit(60);		

		g.m_context.m_wind = &g.m_window;
		g.m_context.m_eventManager = g.m_window.getEventManager();
		g.m_context.m_textureManager = &g.m_textureManager;
		g.m_context.m_entityManager = &g.m_entityManager;

		g.m_sceneManager.switchTo(SceneType::Intro);
		std::cout<<g.m_sceneManager.hasScene(SceneType::Intro)<<std::endl;
		return getInstance();
	}
}

Game &Game::getInstance(){
	if (!instance){		
		std::cout<<"gameInstance creado "<<std::endl;
		instance = new Game();
	}
	return *instance;
}

sf::Time Game::getElapsed(){ return m_clock.getElapsedTime(); }
void Game::restartClock(){ m_elapsed = m_clock.restart(); }
Window* Game::getWindow(){ return &m_window; }

void Game::update(){
	m_window.update();
	m_sceneManager.update(m_elapsed);
}

void Game::render(){
	m_window.beginDraw();
	// Render here.
	m_sceneManager.draw();

	// Debug.
	/* if(m_context.m_debugOverlay.Debug()){
		m_context.m_debugOverlay.Draw(m_window.GetRenderWindow());
	} */
	// End debug.

	m_window.endDraw();
}

void Game::lateUpdate(){
	m_sceneManager.processRequests();
	restartClock();
}

Game::~Game() {}
