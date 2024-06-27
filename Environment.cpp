#include <SFML/Graphics.hpp>
#include "Environment.h"

Environment::Environment(const sf::Vector2f &pos, int tile):
	m_pos(pos){
		switch(tile){
		case 0:
			m_tex.loadFromFile("img/Stone.png");			
			break;
		case 1:
			m_tex.loadFromFile("img/Tree_2.png");
			break;
		case 2:			
			m_tex.loadFromFile("img/Tree_3.png");
			break;
		case 3:
			m_tex.loadFromFile("img/Bush (4).png");
			break;		
		};	
		
		m_spr.setTexture(m_tex);
		
		//m_spr.setScale(0.75,0.75);
		
	}

void Environment::update(double elapsed) {
	m_spr.setPosition(m_pos);
}

sf::Sprite &Environment::getSprite(){
	return m_spr;
}

void Environment::draw(sf::RenderTarget & target) {
	target.draw(this->m_spr);
}

sf::FloatRect Environment::getGlobalBounds(){
	return m_spr.getGlobalBounds();	
}

sf::Vector2f Environment::getPosition() const{
	return m_spr.getPosition(); 
}
