#include "Tile.h"

Tile::Tile() 
    :Entity()
{m_name = "Tile";}

Tile::~Tile(){}

void Tile::onEntityCollision(Entity *l_collider, bool l_attack){}

void Tile::load(const std::string &l_path){
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
			m_spriteSheet.loadTileSheet(path);
		} else if(type == "BoundingBox"){
			sf::Vector2f boundingSize;
			keystream >> boundingSize.x >> boundingSize.y;
			setSize(boundingSize.x, boundingSize.y);
		} else if(type == "DamageBox"){
			keystream >> m_hitbox.left >> m_hitbox.top 
				>> m_hitbox.width >> m_hitbox.height;
		} else {
			std::cout << "! Unknown type in character file: " << type << std::endl;
		}
	}
	file.close();	
}

int Tile::getAnimId(){
	return m_animId;
}

void Tile::update(float l_dT){
    Entity::update(l_dT/150);
	if(m_animId == 27){
		setState(EntityState::Water);
	} else if(m_animId > 27){
		setState(EntityState::Flag);
	}

	animate();

	m_spriteSheet.update(l_dT/250);
	m_spriteSheet.setSpritePosition(m_position);
}

void Tile::draw(sf::RenderWindow *l_wind){
	m_spriteSheet.draw(l_wind);
}

void Tile::animate(){
    EntityState state = getState();
	if (m_animId<27){
		m_spriteSheet.setAnimation(m_animId,true,true);
	}else if (state == EntityState::Water && m_spriteSheet.
		getCurrentAnim()->getName() != "Water"){
		m_spriteSheet.setAnimation("Water",true,true);
	}	else if(state == EntityState::Flag && m_spriteSheet.
		getCurrentAnim()->getName() != "Flag"){
		m_spriteSheet.setAnimation("Flag",true,true);
	}
}

void Tile::setAnimId(int l_animId){	m_animId = l_animId;}
