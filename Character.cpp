#include "Character.h"
#include <iostream>
#include <fstream>
#include <sstream>

Character::Character()
	: Entity(), 
	m_jumpVelocity(250), m_hitpoints(5){ m_name = "Character"; }

Character::~Character(){ }

void Character::move(const Direction& l_dir){
	m_dir=l_dir;
	if (getState() == EntityState::Dying){ return; }
	m_spriteSheet.setDirection(l_dir);
	if (l_dir == Direction::Left){ accelerate(-m_speed.x, 0); }
	else { accelerate(m_speed.x, 0); }
	if (getState() == EntityState::Idle){ setState(EntityState::Walking); }
}

void Character::jump(){
	if (getState() == EntityState::Dying || getState() == EntityState::Jumping || getState() == EntityState::Run){ return; }
	setState(EntityState::Jumping);
	addVelocity(0, -m_jumpVelocity);
}

void Character::takeDamage(const int& l_damage){
	if (getState() == EntityState::Dying || getState() == EntityState::Hurt){ return; }
	m_hitpoints = (m_hitpoints - l_damage > 0 ? m_hitpoints - l_damage : 0);
	if (m_hitpoints){ setState(EntityState::Hurt); }
	else { setState(EntityState::Dying); }
}

void Character::load(const std::string& l_path){
	std::ifstream file;
	file.open(l_path);
	if (!file.is_open()){ std::cout << "! Failed loading the character file: " << l_path << std::endl; return; }
	std::string line;
	while(std::getline(file,line)){
		if (line[0] == '|'){ continue; }
		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if(type == "Name"){
			keystream >> m_name;
		} else if(type == "Spritesheet"){
			std::string path;
			keystream >> path;
			m_spriteSheet.loadSheet(path);
		} else if(type == "Hitpoints"){
			keystream >> m_hitpoints;
		} else if(type == "BoundingBox"){
			sf::Vector2f boundingSize;
			keystream >> boundingSize.x >> boundingSize.y;
			setSize(boundingSize.x, boundingSize.y);
		} else if(type == "DamageBox"){
			keystream >> m_hitbox.left >> m_hitbox.top 
				>> m_hitbox.width >> m_hitbox.height;
		} else if(type == "Speed"){
			keystream >> m_speed.x >> m_speed.y;
		} else if(type == "JumpVelocity"){
			keystream >> m_jumpVelocity;
		} else if(type == "MaxVelocity"){
			keystream >> m_maxVelocity.x >> m_maxVelocity.y;
		} else {
			std::cout << "! Unknown type in character file: " << type << std::endl;
		}
	}
	file.close();
}


void Character::animate(){
	EntityState state = getState();

    if(state == EntityState::Walking && m_spriteSheet.
		getCurrentAnim()->getName() != "Walk"){
		m_spriteSheet.setAnimation("Walk",true,true);
	}  else if(state == EntityState::Hurt && m_spriteSheet.
		getCurrentAnim()->getName() != "Hurt"){
		m_spriteSheet.setAnimation("Hurt",true,false);
	} else if(state == EntityState::Jumping && m_spriteSheet.
		getCurrentAnim()->getName() != "Jump"){
		m_spriteSheet.setAnimation("Jump",true,false);
	} else if(state == EntityState::Run && m_spriteSheet.
		getCurrentAnim()->getName() != "Run"){
		m_spriteSheet.setAnimation("Run",true,false);
	} else if(state == EntityState::Dying && m_spriteSheet.
		getCurrentAnim()->getName() != "Death"){
		m_spriteSheet.setAnimation("Death",true,false);
	} else if(state == EntityState::Idle && m_spriteSheet.
		getCurrentAnim()->getName() != "Idle"){
		m_spriteSheet.setAnimation("Idle",true,true);
	} else if(state == EntityState::Move && m_spriteSheet.
		getCurrentAnim()->getName() != "Move"){
		m_spriteSheet.setAnimation("Move",true,true);
	} 
}

void Character::update(float l_dT){
    Entity::update(l_dT/100);
}

void Character::draw(sf::RenderWindow* l_wind){
	m_spriteSheet.draw(l_wind);
}

