#include "Map.h"
#include "Entity.h"
#include "GameScene.h"

Map::Map(TextureMap &l_textureMap){
	sf::Texture *t_fondo;
	auto itr = *l_textureMap.vm->find("Bg1");	
	
	if(itr != *l_textureMap.vm->end()){
		t_fondo = itr.second;
	}
		
	m_fondo.setTexture(*t_fondo);
	m_fondo.setScale(0.75,0.75);
					
	m_player = new Player();
	m_player->setPosition(150,250);
	addPlayer(m_player);

	Enemy *ene = new Enemy();
	ene->load("char/Snake.char");
	ene->setPosition(450,150);
	addEnemy(ene);

	std::vector<int> m_vId;

	Tile *bloque = new Tile();
	bloque->load("char/Tile_Static.char",m_vId);
	bloque->setAnimId(15);
	bloque->setPosition(50,300);
	add(bloque);
	
}

void Map::update(double elapsed) {	
	m_player->update(elapsed);

	for(auto e: enemies){		
		e->update(elapsed);
	}
}

void Map::draw(sf::RenderWindow &w){

	w.draw(m_fondo);

	this->m_player->draw(&w);
	
	for(auto e: enemies){		
		e->draw(&w);
	}
	
	
}
void Map::add(Tile *e){
	entitiles.push_back(e);
}

void Map::addEnemy(Enemy *e){
	enemies.push_back(e);
}

void Map::addPlayer(Player *p){
	m_player = p;
}


void Map::remove(Entity *e){
	to_delete.push_back(e);
}

void Map::addEntityToDelete(Entity * de){
	enti_to_delete.push_back(de);
}
	
	
void Map::clearVEntity(){
	
	for(auto d: enti_to_delete){
		auto it = find(entities.begin(), entities.end(), d);
		if(it != entities.end()){
			entities.erase(it);
		}
	}
	
	enti_to_delete.clear();
}

Map::~Map()
{
}
