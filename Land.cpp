#include "Land.h"
#include "Entity.h"
#include "Platform.h"
#include "Constants.h"
#include "Environment.h"

Land::Land() {
	Platform *platform = new Platform(sf::Vector2f(0, HEIGHT-96),0);
	entities.push_back(platform);
	Environment *stone = new Environment(sf::Vector2f(platform->getSprite().getGlobalBounds().width*1.5, HEIGHT-196),0);
	//stone->getSprite().setScale(1.5,1.5);
	enviro.push_back(stone);
	
	//m_platform.resize(4);	
	for(size_t i = 1; i<5;i++){
		Platform *platform2 = new Platform(sf::Vector2f(i*platform->getSprite().getGlobalBounds().width, HEIGHT-96),1);
		//m_platform.push_back(platform);
		entities.push_back(platform2);
	}
	Platform *platform3 = new Platform(sf::Vector2f(platform->getSprite().getGlobalBounds().width*5, HEIGHT-96),2);
	entities.push_back(platform3);
	Environment *tree = new Environment(sf::Vector2f(platform->getSprite().getGlobalBounds().width*2.5, 170),1);
	tree->getSprite().setScale(1.5,1.5);
	enviro.push_back(tree);
	Platform *agua1 = new Platform(sf::Vector2f((platform->getSprite().getGlobalBounds().width*6)-2, HEIGHT-76),3);
	entities.push_back(agua1);
	Platform *agua2 = new Platform(sf::Vector2f((platform->getSprite().getGlobalBounds().width*7)-2, HEIGHT-76),3);
	entities.push_back(agua2);
	Platform *platform4 = new Platform(sf::Vector2f(platform->getSprite().getGlobalBounds().width*8, HEIGHT-96),0);
	entities.push_back(platform4);
	for(size_t i = 9; i<15;i++){
		Platform *platform5 = new Platform(sf::Vector2f(i*platform->getSprite().getGlobalBounds().width, HEIGHT-96),1);
		//m_platform.push_back(platform);
		entities.push_back(platform5);
	}
	Platform *snake = new Platform(sf::Vector2f(platform->getSprite().getGlobalBounds().width*8.3, 530),6);
	snake->getSprite().setScale(1.2,1.2);
	entities.push_back(snake);
	
}

void Land::update(double elapsed) {	
	
}

void Land::draw(sf::RenderTarget & target){
	for(auto e: enviro){
		e->draw(target);
	}
	
	for(auto e: entities){
		e->draw(target);
	}
}


std::vector<Entity *> Land::getVEntity(){
	return this->entities;
}
	
std::vector<Environment *> Land::getVEnviro(){
	return this->enviro;
}

void Land::addEntityToDelete(Entity * de){
	enti_to_delete.push_back(de);
}
	
void Land::addEnviroToDelete(Environment * dev){
	enviro_to_delete.push_back(dev);
}
	
void Land::clearVEntity(){
	
	for(auto d: enti_to_delete){
		auto it = find(entities.begin(), entities.end(), d);
		if(it != entities.end()){
			entities.erase(it);
		}
	}
	
	enti_to_delete.clear();
}
	
void Land::clearVEnviro(){
	for(auto d: enviro_to_delete){
		auto it = find(enviro.begin(), enviro.end(), d);
		if(it != enviro.end()){
			enviro.erase(it);
		}
	}
	
	enviro_to_delete.clear();
}


