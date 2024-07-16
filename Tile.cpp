#include "Tile.h"

Tile::Tile(EntityManager* l_entityMgr, int l_id = 0)
    :Entity(l_entityMgr), m_id(l_id), 
    m_spriteSheet(m_entityManager->getContext()->m_textureManager)
    {m_name = "Tile";}

Tile::~Tile(){
	if (m_texture == ""){ return; }
	m_context->m_textureManager->releaseResource(m_texture);
}

void Tile::animate(){
	EntityState state = getState();

	if (state == EntityState::Water && m_spriteSheet.
		getCurrentAnim()->getName() != "Water"){
		m_spriteSheet.setAnimation("Water",true,true);
	}	else if(state == EntityState::Flag && m_spriteSheet.
		getCurrentAnim()->getName() != "Flag"){
		m_spriteSheet.setAnimation("Flag",true,true);
	}
}

void Tile::readIn(std::stringstream &l_stream){
    l_stream >> m_name >> m_friction.x >>m_friction.y >> m_deadly >> 
		m_frameStart >> m_frameEnd>> m_frameTime >> 
        m_frameActionStart >> m_frameActionEnd;
}

void Tile::draw(sf::RenderWindow* l_wind){
	m_spriteSheet.draw(l_wind);
}

void Tile::load(const std::string& l_path){
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
			m_spriteSheet.loadTileSheet(path, *m_context->m_entityManager);
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

int Tile::getFrameEnd(){
    return m_frameEnd;
}

int Tile::getFrameStart(){
    return m_frameStart;
}

int Tile::getFrameTime(){
    return m_frameTime;
}

int Tile::getFrameActionStart(){
    return m_frameActionStart;
}

int Tile::getFrameActionEnd(){
    return m_frameActionEnd;
}

sf::IntRect Tile::getCoordCrop(){
    return m_coordCrop;
}

void Tile::setCoordCrop(int left, int top, int width, int height)
{
    m_coordCrop = sf::IntRect(left, top, width, height);
}

void Tile::onEntityCollision(Entity *l_collider, bool l_attack){
}

void Tile::update(float l_dT){
	Entity::update(l_dT);
	if(m_id == 19){
		setState(EntityState::Water);
	} else if(m_id == 26 || m_id == 28){
		if(!m_spriteSheet.getCurrentAnim()->isPlaying()){
			setState(EntityState::Flag);
		}
	}

	animate();

	m_spriteSheet.update(l_dT);
	m_spriteSheet.setSpritePosition(m_position);
}
