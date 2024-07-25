#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameScene.h"
#include "BaseScene.h"
#include <fstream>
#include <iostream>

Game *Game::instance = nullptr;
Game::Game(){}

Game &Game::create(const sf::VideoMode &videoMode, BaseScene *scene, const std::string &name){
	if(instance){
		std::cerr<<"ERROR: can't call create(), game already running."<<std::endl;
	}else{
		Game & g = getInstance();
		g.m_window.create(videoMode, name, sf::Style::Close);
		g.m_next_scene = nullptr;
		g.loadTextures();
		g.m_view = new sf::View(sf::FloatRect(0, 0.f, WIDTH, HEIGHT));
		g.m_current_scene = scene;
		g.m_window.setFramerateLimit(60);
		g.m_clock.restart();
		srand(time(nullptr));
	}
	return getInstance();
}


Game &Game::getInstance(){
	if(!instance){
		instance = new Game();
	}
	return *instance;
}

void Game::run ( ) {
	m_current_scene->onCreate(m_tM);
	while(m_window.isOpen() && m_current_scene != nullptr) {
		sf::Event e;
		while(m_window.pollEvent(e)){
			if(e.type == sf::Event::Closed){
				m_window.close();
			}else{
				m_current_scene->processEvent(e);
			}
		}
		update();
		draw();
		if(m_next_scene != nullptr){
			delete m_current_scene;
			m_current_scene = m_next_scene;
			m_next_scene = nullptr;
		}
	}
}


void Game::update ( ) {
	m_current_scene->update(m_clock.getElapsedTime(),*this);
	m_view->setCenter(m_current_scene->getView().getCenter());
	m_clock.restart();
}

void Game::draw ( ) {
	m_window.clear(sf::Color(0,0,0,255));
	m_current_scene->draw(this->m_window);
	m_window.display();
}

void Game::processEvents ( ) {
	//Polling m_window events
	while (this->m_window.pollEvent(this->m_ev))
	{
		if (this->m_ev.type == sf::Event::Closed){
			//this->saveScores();
			this->m_window.close();
		}
		else if (this->m_ev.type == sf::Event::KeyPressed && this->m_ev.key.code == sf::Keyboard::Escape){
			//this->saveScores();
			this->m_window.close();
		}
		else{
			this->m_current_scene->processEvent(this->m_ev);
		}
	} 
}

void Game::switchScene(BaseScene *scene){
	m_next_scene = scene;
	scene->onCreate(m_tM);
}


void Game::loadPaths(const std::string &l_pathFile){
	std::ifstream paths;
	paths.open(l_pathFile);
	if (paths.is_open()){
		std::string line;
		while (std::getline(paths, line)){
			std::stringstream keystream(line);
			std::string pathName;
			std::string path;
			keystream >> pathName;
			keystream >> path;
			m_paths.emplace(pathName, path);
		}
		paths.close();
		return;
	}
	std::cerr << "! Failed loading the path file: " << l_pathFile << std::endl;
}

sf::View &Game::getView(){

    return *m_view;
}

void Game::loadTextures(){
	loadPaths("varios/textures.cfg");
	for(const auto& v: m_paths){
		m_vm.insert({v.first,load(v.second)});
		std::cout<<v.first<<" cargada"<<std::endl;	
	}
	m_tM.vm = &m_vm;
	
};

sf::Texture *Game::load(const std::string &l_path){
	sf::Texture *texture = new sf::Texture();
	if (!texture->loadFromFile(l_path)){
		delete texture;
		texture = nullptr;
		std::cerr << "! Failed to load texture: " << l_path << std::endl;
	}
	return texture;
}

Game::~Game ( ) {
	
	
}


