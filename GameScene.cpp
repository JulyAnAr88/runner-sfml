#include "GameScene.h" 
#include "GameOverScene.h" 
#include "IntroScene.h" 
#include "HUD.h"
#include "SharedContext.h"
#include <cmath>
#include <vector>
#include <windows.h>

GameScene::GameScene() : BaseScene(){
}

void GameScene::onCreate(TextureMap &l_textureMap){
	m_music.openFromFile("sounds/Chamarrito.ogg");
	m_music.setVolume(50);
	m_music.setLoop(true);
	m_music.play();
	m_tm = &l_textureMap;
	this->m_view = new sf::View(sf::FloatRect(0, 0.f, WIDTH, HEIGHT));
	m_terreno = new Land(l_textureMap);
	m_terreno->setView(*m_view);
	m_terreno->loadMap("varios/map1.map");
	
}

void GameScene::onDestroy(){
}

void GameScene::update(const sf::Time& l_time, Game &g){
	*this->m_view = g.getView();
	sf::Time time = m_clock.getElapsedTime();
	m_terreno->update(l_time.asSeconds()*250,g);
	
	bool play= m_terreno->getPlayerPosition().x*3 > 0;
	bool plvi = m_view->getCenter().x+1 > WIDTH/4.5;
	pos_view_x = m_terreno->getPlayerPosition().x;
	
	if(play && plvi){		
		this->m_view->setCenter(sf::Vector2f(pos_view_x+250, HEIGHT*0.5));
	}
	this->m_view->setSize(sf::Vector2f( WIDTH, HEIGHT));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1)){
		//IntroScene *is = new IntroScene(m_view->getCenter());
		//is->onCreate(*m_tm);
		std::cout<<"center gamescene "<<m_view->getCenter().x<<" "<<m_view->getCenter().y<<std::endl; 
		g.switchScene(new IntroScene(m_view->getCenter()));
	}
	if(m_terreno->playerIsDead() || m_terreno->exito()){
		std::cout<<"center gamescene "<<m_view->getCenter().x<<" "<<m_view->getCenter().y<<std::endl; 
		std::cout<<"center gamescene "<<g.getView().getCenter().x<<" "<<g.getView().getCenter().y<<std::endl; 
		g.switchScene(new GameOverScene(m_terreno->getPoints(),m_terreno->getTime(),m_terreno->exito(), 
		//g.getView().getCenter()));
		g.getView().getCenter()));
		
	}
	
}

void GameScene::draw(sf::RenderWindow &w){
	w.clear();
	
	m_terreno->draw(w);
	//m_hud->draw(w);
	
	w.setView(*m_view);
	
	//w.display();
	
}

void GameScene::processEvent(const sf::Event &e){
	
}

GameScene::~GameScene(){
	//delete m_hud;
	//delete m_terreno;
	m_music.stop();
}
