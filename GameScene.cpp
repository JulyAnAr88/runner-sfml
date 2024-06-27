#include "GameScene.h" 
#include "SceneBase.h"
#include "Constants.h"
#include "Platform.h"
#include "Environment.h"
#include <vector>
#include <thread>

GameScene::GameScene(){
	
	m_vel_min = 150;
	createNewEntity(m_vel_min);
	m_time_new_entity.restart();

	m_fondo.resize(5);
	m_fondo[0].loadFromFile("img/parallax/layer_08.png");
	m_fondo[1].loadFromFile("img/parallax/layer_07.png");
	m_fondo[2].loadFromFile("img/parallax/layer_05.png");
	/*fondo[3]->loadFromFile("img/parallax/layer_02.png");
	fondo[4]->loadFromFile("img/parallax/layer_01.png");*/
	
	m_inicio.resize(3);
	m_inicio[0].setTexture(m_fondo[0]);
	m_inicio[1].setTexture(m_fondo[1]);
	m_inicio[2].setTexture(m_fondo[2]);
	
	/**/for (auto b : m_inicio){
		addBackgrounds(&b);
	};
	
	m_terreno = new Land();
	
	addLand(m_terreno);
	
	m_player = new Player(sf::Vector2f(200, 350));
	addPlayer(m_player);
		
	
	//inicio.setPosition({0.0,350.0});
	this->pl_view = new sf::View(sf::FloatRect(pos_view_x, 0.f, WIDTH, HEIGHT));
	/*this->pl_view = new sf::View(win.getDefaultView().getCenter(),
							 static_cast<sf::Vector2f>(win.getSize()));
	this->m_win = &win;
	this->m_win->setView(*pl_view);*/
}


void GameScene::update(float elapsed){
	sf::FloatRect nulo = {0,0,0,0};
	m_terreno->update(elapsed);
	m_player->update(elapsed);
	
	for(auto e: m_terreno->getVEntity()){		
		e->update(elapsed);
		sf::FloatRect overlap = m_player->checkCollision(*e);
		if(overlap != nulo){
			m_player->separate(overlap,*e);
		}		
	}
	
	for(auto ev:m_terreno->getVEntity()){
		ev->update(elapsed);
	}
	
	for(auto e: m_terreno->getVEntity()){		
		if(e->getPosition().x<0){
			m_terreno->addEntityToDelete(e);
		}
	}
	
	m_terreno->clearVEntity();
	
	// elimina elementos del ambiente
	for(auto evd: m_terreno->getVEnviro()){
		if(evd->getPosition().x<0){
			m_terreno->addEnviroToDelete(evd);
		}
	}
	
	m_terreno->clearVEnviro();
	
	if(m_time_new_entity.getElapsedTime().asMicroseconds()>10){
		m_vel_min += 50;
		createNewEntity(m_vel_min);
		m_time_new_entity.restart();
	}
	
	bool play= m_player->getPosition().x*2 > 0;
	std::cout<<"player "<<play<<std::endl;
	bool plvi = pl_view->getCenter().x+1 > WIDTH/2.f;
	std::cout<<"pl_view "<<plvi<<std::endl;
	if(m_player->getPosition().x*2 > 0 && pl_view->getCenter().x+1 > WIDTH/2.f){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){ 
		pos_view_x += MOVE_SPEED*5;
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
		pos_view_x -= MOVE_SPEED*5;
	}
	
		this->pl_view->setCenter(sf::Vector2f(pos_view_x+600, HEIGHT/2.f));
	}
	//this->pl_view->setSize(sf::Vector2f( WIDTH, HEIGHT));
	//pos_view_x =0;
}

void GameScene::draw(sf::RenderWindow &w){
	w.clear();
	w.draw(m_inicio[0]);
	
	w.draw(m_inicio[1]);
	w.draw(m_inicio[2]);
	//w.draw(m_platform[0]->getSprite());
	m_terreno->draw(w);
		
	m_player->draw(w);
	
	for(auto e: entities){
		e->draw(w);
	}
	w.setView(*this->pl_view);
	/*this->m_player->draw(w);
	//win->draw(p_disp);
	
	w.display();*/
	
}


void GameScene::add(Entity *e){
	entities.push_back(e);
}

void GameScene::addLand(Land *l){
	m_terreno = l;
}

void GameScene::addPlayer(Player *p){
	m_player = p;
}

void GameScene::addBackgrounds(sf::Sprite *back){
	backgrounds.push_back(back);
}

void GameScene::addBackgrounds(std::vector<sf::Sprite*> back){
	for (auto b : back){
		this->backgrounds.push_back(b);
	};
	
}

void GameScene::remove(Entity *e){
	to_delete.push_back(e);
}

void GameScene::createNewEntity(float velMin){
	
}

void GameScene::processEvent(const sf::Event &e){
	
}

/*
void GameScene::updateCollision(Game &game, sf::RenderWindow &win)
{	
	//Collision with the bottom of screen
	if (this->m_player->getPosition().y > 
		win.mapPixelToCoords(sf::Vector2i(0,win.getSize().y + 3*(this->m_player->m_spr.getGlobalBounds().height)),*pl_view).y)
	{
		this->pl_view->setCenter(win.getDefaultView().getCenter());
		//game.SetScene(new death_scene(game.m_window,this->points));
	}
	
	//Collision with borders
	bool algo=this->m_player->getPosition().x > win.getSize().x && this->m_player->getMovement();
	
	if (this->m_player->getPosition().x > win.getSize().x && this->m_player->getMovement())
	{
		//std::cout<<"getMovement "<<this->player->m_spr.getGlobalBounds().width<<std::endl;
		this->m_player->teleport(0-(this->m_player->m_spr.getGlobalBounds().width));
	}
	if ((this->m_player->getPosition().x) < (0  - this->m_player->getGlobalBounds().width) && !this->m_player->getMovement())
	{
		std::cout<<win.getSize().x<<std::endl;
		this->m_player->teleport(win.getSize().x);
	}
	
	//Collision with platforms
	
	 if (this->player->isFalling() && plat->getCollision(*player))
	{
		
		this->player->bounce();
	} 
	
}

void GameScene::updateView(){
	if (m_player->m_spr.getPosition().y < 
		m_win->mapPixelToCoords(sf::Vector2i(WIDTH,HEIGHT/2),*pl_view).y)
	{
		//pl_view->setCenter(sf::Vector2f(pl_view->getCenter().x-(1.0*abs(this->player->getVelX())),pl_view->getCenter().y-(1.0*abs(this->player->getVelY()))));
	}
}

void GameScene::updatePlayer(){
	//std::cout<<clock.getElapsedTime().asMilliseconds()<<std::endl;
	//std::cout<<clock.getElapsedTime().asMicroseconds()<<std::endl;
	this->m_player->Update(m_clock.getElapsedTime().asMilliseconds());
	m_clock.restart();
	//check_level();
}

void GameScene::initVariables(){
	this->points = 1;
	this->plat = new PlatformEngine(10,points);
	this->m_player = new Player();
}
*/
GameScene::~GameScene(){
}
