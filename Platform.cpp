#include "Platform.h"
#include <iostream>

Platform::Platform(const sf::Vector2f &pos, int tile): 
	m_pos(pos){
	switch(tile){
	case 0:
		m_tex.loadFromFile("img/Tile (1).png");
		break;
	case 1:
		m_tex.loadFromFile("img/Tile (2).png");
		break;
	case 2:
		m_tex.loadFromFile("img/Tile (3).png");
		break;
	case 3:
		m_tex.loadFromFile("img/Bush (1).png");
		break;
	case 4:
		m_tex.loadFromFile("img/Tree_1.png");
		break;
		
	case 6:
		m_tex.loadFromFile("img/tile025.png");
		break;
	};	
	
	m_spr.setTexture(m_tex);
	
	m_spr.setScale(0.75,0.75);
	
}

void Platform::update(double elapsed) {
	m_spr.setPosition(m_pos);
}

void Platform::draw(sf::RenderTarget & target) {
	target.draw(this->m_spr);
}

