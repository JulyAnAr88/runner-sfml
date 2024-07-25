#include "Land.h"
#include "Entity.h"
#include "GameOverScene.h" 
#include <windows.h>


Land::Land(TextureMap &l_textureMap): m_tM(&l_textureMap),
	m_mapGravity(50.f), m_loadNextMap(false){
	loadEnemyTypes("varios/EnemyList.list");
	loadTilesTypes("varios/TileList.list");
	registerEntity<Player>(EntityType::Player);
	registerEntity<Enemy>(EntityType::Enemy);
	registerEntity<Tile>(EntityType::Tile);

	m_hud = new HUD(*m_tM);
}

int Land::add(const EntityType &l_type, const std::string &l_name){
    auto itr = m_entityFactory.find(l_type);
	if (itr == m_entityFactory.end()){ return -1; }
	Entity* entity = itr->second();
	entity->setId(m_idEntities);
	if (l_name != ""){ entity->setName(l_name); }

	m_entities.emplace(m_idEntities,entity);

	if(l_type == EntityType::Enemy){
		auto itr = m_enemyTypes.find(l_name);
		if(itr != m_enemyTypes.end()){
			Enemy* enemy = (Enemy*)entity;
			enemy->load(itr->second);
		}
	}

	if(l_type == EntityType::Tile){
		auto itr = m_tilesTypes.find(l_name);
		if(itr != m_tilesTypes.end()){
			Tile* tile = (Tile*)entity;
			tile->load(itr->second);
		}
	}	

	++m_idEntities;
	return m_idEntities - 1;
}

void Land::update(double elapsed,Game &g) {
	
	generarEnemies(elapsed);

	generarTiles(elapsed);

	collisionCheck(elapsed);

	m_background.setPosition(m_view->getCenter().x-WIDTH/2,0);
	m_hud->setPosition(m_view->getCenter().x+WIDTH*0.33,HEIGHT*0.08);
	m_hud->update(elapsed, m_player->getHitpoints());
	
	processRemovals();

}

void Land::draw(sf::RenderWindow &w){

	w.draw(m_background);	

	for(const auto& e: m_entities){
		if (e.second->getType() != EntityType::Player || 
			e.second->getType() != EntityType::Enemy){
			for(auto t : m_tilesMap){
				if(e.first == t.first){
					Tile* tile = (Tile*)e.second;
					tile->setAnimId(t.second.first);
					tile->setPosition(t.second.second.x * m_maxMapSize.x, w.getSize().y/7.5*t.second.second.y);
					tile->draw(&w);
				}
			}
		}
	}

	for(const auto& t:m_tiles){
		t->draw(&w);
	}

	if(m_greenFlag !=0){
		Tile* te = (Tile*)findEntity(m_greenFlag);
		te->setAnimId(28); 
		te->setPosition(6392,385);
		te->draw(&w);
	}

	if(m_redFlag !=0){		
		Tile* te = (Tile*)findEntity(m_redFlag);
		te->setAnimId(29); 
		te->setPosition(3572,385);
		m_textHalf.setPosition(3575,175);
		te->draw(&w);
		w.draw(m_textHalf);
	}
	
	for(const auto& e: m_entities){
		if (e.second->getType() == EntityType::Player || 
			e.second->getType() == EntityType::Enemy){			
			e.second->draw(&w);
		}
	}
	
	m_hud->draw(w);
}



sf::FloatRect Land::getViewSpace(sf::RenderWindow &l_window){
	sf::Vector2f viewCenter(l_window.getView().getCenter());
	sf::Vector2f viewSize(l_window.getView().getSize());
	sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
	sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
	return viewSpace;
}

int Land::getPoints(){
	if(m_exito){
		return m_cantEnemies+1000;
	}
    return m_cantEnemies;
}

std::string Land::getTime(){
    return m_hud->getTime();
}

void Land::loadMap(const std::string &l_path){
	std::ifstream mapFile;
	mapFile.open(l_path);
	if (!mapFile.is_open()){ std::cout << "! Failed loading map file: " << l_path << std::endl; return; }
	
	std::string line;
	std::cout << "--- Loading a map: " << l_path << std::endl;

	int playerId = -1;	
	while(std::getline(mapFile,line)){
		if (line[0] == '|'){ continue; }
		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if(type == "STATIC"){
			int staticId = 0;
			keystream >> staticId;
			if (staticId < 0){ std::cout << "! Bad tile id: " << staticId << std::endl; continue; }
			int staticMapId = add(EntityType::Tile,"Tile_Static");
			if (staticMapId < 0){ continue; }
			sf::Vector2f tileCoords;
			keystream >> tileCoords.x >> tileCoords.y;
			m_tilesMap.emplace(staticMapId,std::make_pair(staticId,tileCoords));
			findEntity(staticMapId)->setPosition(tileCoords);	
		 } else if(type == "ANIMATED"){
			int animatId = 0;
			keystream >> animatId;
			if (animatId < 0){ std::cout << "! Bad tile id: " << animatId << std::endl; continue; }
			int animatMapId = add(EntityType::Tile,"Tile_Animated");
			if (animatMapId < 0){ continue; }
			sf::Vector2f tileCoords;
			keystream >> tileCoords.x >> tileCoords.y;
			m_tilesMap.emplace(animatMapId,std::make_pair(animatId,tileCoords));
			findEntity(animatMapId)->setPosition(tileCoords);
		}else if(type == "BACKGROUND"){
			if (m_backgroundTexture != ""){ continue; }
			keystream >> m_backgroundTexture;
			auto itr = m_tM->vm->find(m_backgroundTexture);	
			if (itr == m_tM->vm->end()){
				m_backgroundTexture = "";
				continue;
			}
			//std::cout<<"backg "<<itr->first<<" "<<std::endl;
			sf::Texture* texture = itr->second;
			m_background.setTexture(*texture);
			sf::Vector2f viewSize (WIDTH,HEIGHT);
			sf::Vector2u textureSize = texture->getSize();
			sf::Vector2f scaleFactors;
			scaleFactors.x = viewSize.x / textureSize.x;
			scaleFactors.y = viewSize.y / textureSize.y;
			m_background.setScale(scaleFactors);
		} else if(type == "SIZE"){
			keystream >> m_maxMapSize.x >> m_maxMapSize.y;
		} else if(type == "GRAVITY"){
			keystream >> m_mapGravity;
		} else if(type == "DEFAULT_FRICTION"){
			keystream >> m_defaultFriction.x >> m_defaultFriction.y;
		} else if(type == "NEXTMAP"){
			keystream >> m_nextMap;
		} else if(type == "PLAYER"){
			if (playerId != -1){ continue; }
			playerId = add(EntityType::Player);
			if (playerId < 0){ continue; }
			float playerX = 0, playerY = 0;
			keystream >> playerX >> playerY;
			m_player = (Player*) findEntity(playerId);
			m_player->setPosition(playerX,playerY);
			m_playerStart = sf::Vector2f(playerX, playerY);
		} else if(type == "ENEMY"){
			std::string enemyName;
			keystream >> enemyName;
			int enemyId = add(EntityType::Enemy, enemyName);
			if (enemyId < 0){ continue; }
			float enemyX = 0; float enemyY = 0;
			keystream >> enemyX >> enemyY;
			findEntity(enemyId)->setPosition(enemyX, enemyY);
		} else {
			std::cout << "! Unknown type \"" << type << "\"." << std::endl;
		}
	}
	mapFile.close();
	std::cout << "--- Map Loaded! ---" << std::endl;

	std::vector<int> m_vId;
	
}

void Land::loadTilesTypes(const std::string &l_path){
	std::ifstream file;
	file.open(l_path);
	if (!file.is_open()){ std::cout << "! Failed loading file: " << l_path << std::endl; return; }
	std::string line;
	while(std::getline(file,line)){
		if (line[0] == '|'){ continue; }
		std::stringstream keystream(line);
		std::string name;
		std::string charFile;
		keystream >> name >> charFile;
		m_tilesTypes.emplace(name,charFile);
	}
	file.close();
}

void Land::loadEnemyTypes(const std::string &l_path){
	std::ifstream file;
	file.open(l_path);
	if (!file.is_open()){ std::cout << "! Failed loading file: " << l_path << std::endl; return; }
	std::string line;
	while(std::getline(file,line)){
		if (line[0] == '|'){ continue; }
		std::stringstream keystream(line);
		std::string name;
		std::string charFile;
		keystream >> name >> charFile;
		m_enemyTypes.emplace(name,charFile);
	}
	file.close();
}

void Land::loadNext() { m_loadNextMap = true; }

void Land::generarEnemies(double elapsed){

	m_timePassedMosquito += elapsed;
	m_timePassedSnake += elapsed;

	if(m_timePassedMosquito > SPAWNING_TIME_MOSQUITO){		
		int enemyId = add(EntityType::Enemy,"Mosquito");
		findEntity(enemyId)->setPosition(m_view->getCenter().x*2, m_view->getCenter().y);
		m_timePassedMosquito = 0;
		m_cantEnemies +=1;
	}
	if(m_timePassedSnake > SPAWNING_TIME_SERPIENTE){		
		int enemyId = add(EntityType::Enemy,"Snake");
		findEntity(enemyId)->setPosition(m_view->getCenter().x*2, m_view->getSize().y*11.15/12);
		//findEntity(enemyId)->setPosition(m_view->getCenter().x*2, m_view->getSize().y*9.15/12);
		m_timePassedSnake = 0;
		m_cantEnemies +=1;
	}
}

//Generación de entidades aleatorias
void Land::generarTiles(double elapsed){
	
	m_timePassedObject += elapsed;
	m_timePassedObstacle += elapsed;

	
	if(m_timePassedObject > SPAWNING_TIME_ARBUSTO){		
		int objectId = add(EntityType::Tile,"Tile_Static");
		Tile * tile = (Tile *) findEntity(objectId);
		//21 22		
		int random = rand() % 2;
		sf::Vector2f coords(m_view->getSize().x*2,100);
		if(random == 0){
			tile->setAnimId(22);
			tile->setPosition(coords);
		}else{
			tile->setAnimId(21);
			tile->setPosition(coords);
		}
		tile->setPosition(m_view->getCenter().x*2, m_view->getSize().y*9.5/12);
		m_tiles.push_back(tile);
		m_timePassedObject = 0;
	}

	if(m_timePassedObstacle > SPAWNING_TIME_ROCA){		
		int objectId = add(EntityType::Tile,"Tile_Static");
		Tile * tile = (Tile *) findEntity(objectId);
		//17 18		
		int random = rand() % 2;
		sf::Vector2f coords(m_view->getSize().x*2,100);
		if(random == 0){
			tile->setAnimId(18);
			tile->setPosition(coords);
		}else{
			tile->setAnimId(17);
			tile->setPosition(coords);
		}
		tile->setPosition(m_view->getCenter().x*2, m_view->getSize().y*9.6/12);
		m_tiles.push_back(tile);
		m_timePassedObstacle = 0;
	}
}

//Interacciones con el ambiente
void Land::collisionCheck(double elapsed){
	sf::FloatRect nulo = {0,0,0,0};

	for(const auto& e: m_entities){
		e.second->update(elapsed);
		if (e.second->getName()=="Tile_Animated"){
			sf::FloatRect overlap = m_player->checkCollision(*e.second);
			Tile* te = (Tile*) e.second;		
			if(te->getAnimId() == 27){
				if(overlap != nulo){
					m_player->die();
				}
			}
		 }

		
		if (e.second->getName()=="Tile_Static"){
			sf::FloatRect overlap = m_player->checkCollision(*e.second);
			Tile* te = (Tile*) e.second;
			if(te->getAnimId() >0 && te->getAnimId()<19){
				if(overlap != nulo){
					m_player->separate(overlap,*e.second);
				}
			}

			if(te->getAnimId() == 24){
				if(overlap != nulo){
					Sleep(500);					
					m_exito = true;
				}
			}

			if(te->getAnimId() == 0){
				if(overlap != nulo){
					m_font.loadFromFile("fonts/CompleteinHim.ttf");
					m_textHalf.setFont(m_font);
					//m_textHalf.setFont(m_currentScene->getFontC());
					m_textHalf.setString(sf::String("Excelente, sigue asi!"));
					m_textHalf.setCharacterSize(55);
					m_textHalf.setFillColor(sf::Color::Red);
					sf::FloatRect textRectTitle = m_textHalf.getLocalBounds();
					m_textHalf.setOrigin(textRectTitle.left + textRectTitle.width / 2.0f,
						textRectTitle.top + textRectTitle.height / 2.0f);					
					m_textHalf.setPosition(3575,175);
				}
			}
			
			if(te->getAnimId() == 26){
				if(overlap != nulo){
					m_redFlag = add(EntityType::Tile,"Tile_Animated");
					remove(e.first); 
				}
			}

			if(te->getAnimId() == 25){
				if(overlap != nulo){
					remove(e.first);
					m_greenFlag = add(EntityType::Tile,"Tile_Animated");
				}
			}
		}
		
		if (e.second->getType() == EntityType::Enemy){
			/*	sf::FloatRect overlap = m_player->checkCollision(*e.second);
			if(e.second->getName()=="Snake" && overlap != nulo){
				std::cout<<"enemy Mx "<<e.second->getSize().x<<std::endl;
				std::cout<<"enemy My "<<e.second->getSize().y<<std::endl;
		 	std::cout<<"enemy Mwidth "<<en->getGlobalBounds().width<<std::endl;
				std::cout<<"enemy Mheight "<<en->getGlobalBounds().height<<std::endl;
				std::cout<<"enemy Mleft "<<en->getGlobalBounds().left<<std::endl;
				std::cout<<"enemy Mtop "<<en->getGlobalBounds().top<<std::endl;
			}
			*/
			sf::FloatRect overlap = m_player->checkCollision(*e.second);
				Enemy* en = (Enemy*) e.second;
			if(overlap != nulo){
				m_player->separate(overlap,*en);
				m_player->takeDamage(en->hurt());
				if(m_player->getHitpoints()== 0){
					m_player->die();
				}
			}
		}
	}

}

void Land::setView(sf::View &l_view){
	m_view = &l_view;
}

bool Land::playerIsDead(){
    return m_player->IsDead();
}

bool Land::exito(){
    return m_exito;
}

void Land::remove(int l_id){
    to_delete.push_back(l_id);
}

Land::~Land(){
	purgeMap();
}

void Land::purgeMap(){
	for (auto &itr : m_entities){
		delete itr.second;
	}
	m_entities.clear();
}

void Land::processRemovals(){

	for(const auto& e: m_entities){
		bool lejos = e.second->getPosition().x+WIDTH < m_player->getPosition().x;
		if(lejos){
			if(e.second->getType()!=EntityType::Tile){
				remove(e.first);
			}
		}
	}

	for(const auto e: m_tiles){
		bool lejos = e->getPosition().x+WIDTH < m_player->getPosition().x;
		if(lejos){
			if(e->getType()!=EntityType::Tile){
				delete e;
				m_tiles.pop_back();
			}
		}
	}

	while(to_delete.begin() != to_delete.end()){
		unsigned int id = to_delete.back();
		auto itr = m_entities.find(id);
		if(itr != m_entities.end()){	
			if(itr->second->getType()==EntityType::Tile){
				if(itr->second->getName()=="Tile_Static"){
					std::cout << "Discarding entity: " << itr->second->getId() << std::endl;
					delete itr->second;
					m_entities.erase(itr);
				}
			} else {
				std::cout << "Discarding entity: " << itr->second->getId() << std::endl;
				delete itr->second;
				m_entities.erase(itr);
			}
		}
		to_delete.pop_back();
	}
}

Entity *Land::findEntity(unsigned int l_id){
    auto itr = m_entities.find(l_id);
	if (itr == m_entities.end()){ return nullptr; }
	return itr->second;
}

Entity* Land::findEntity(const std::string& l_name){
	for(auto &itr : m_entities){
		if(itr.second->getName() == l_name){
			return itr.second;
		}
	}
	return nullptr;
}

float Land::getGravity(){
    return m_mapGravity;
}

sf::Vector2f Land::getPlayerPosition(){
    return m_player->getPosition();
}

sf::View Land::getView(){
    return *m_view;
}
