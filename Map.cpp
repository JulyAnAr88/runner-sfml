#include "Map.h"
#include "SceneManager.h"
#include <cmath>

Map::Map(SharedContext* l_context, BaseScene* l_currentScene)
	:m_context(l_context), /* m_defaultTile(l_context), */ m_maxMapSize(32, 32),
	m_tileCount(0), m_tileSetCount(0), m_mapGravity(512.f), m_loadNextMap(false),
	m_currentScene(l_currentScene)
{
	m_context->m_gameMap = this;
	std::string tilesPaths[3];
	tilesPaths[0] = "Collider.sheet";
	tilesPaths[1] = "Environment.sheet";
	tilesPaths[2] = "Triggerable.sheet";
	loadTiles();
}

Map::~Map(){
	purgeMap();
	purgeTileSet();
	m_context->m_gameMap = nullptr;
}

Tile* Map::getTile(unsigned int l_x, unsigned int l_y){
	auto itr = m_tileMap.find(convertCoords(l_x,l_y));
	return(itr != m_tileMap.end() ? itr->second : nullptr);
}
//TileInfo* Map::getDefaultTile(){ return &m_defaultTile; }
float Map::getGravity()const{ return m_mapGravity; }
unsigned int Map::getTileSize()const{ return Sheet::Tile_Size; }
const sf::Vector2u& Map::getMapSize()const{ return m_maxMapSize; }
const sf::Vector2f& Map::getPlayerStart()const{ return m_playerStart; }

void Map::loadMap(const std::string& l_path){
	std::ifstream mapFile;
	mapFile.open(l_path);
	if (!mapFile.is_open()){ std::cout << "! Failed loading map file: " << l_path << std::endl; return; }
	EntityManager* entityMgr = m_context->m_entityManager;
	std::string line;
	std::cout << "--- Loading a map: " << l_path << std::endl;

	int playerId = -1;
	while(std::getline(mapFile,line)){
		if (line[0] == '|'){ continue; }
		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if(type == "COLLIDER"){
			int colliderId = 0;
			keystream >> colliderId;
			if (colliderId < 0){ std::cout << "! Bad tile id: " << colliderId << std::endl; continue; }
			auto itr = m_tileSet.find(colliderId);
			if (itr == m_tileSet.end()){ std::cout << "! Tile id(" << colliderId << ") was not found in tileset." << std::endl; continue; }
			sf::Vector2i tileCoords;
			keystream >> tileCoords.x >> tileCoords.y;
			TileInfo ti;
			ti[colliderId] = type;
			if (tileCoords.x > m_maxMapSize.x || tileCoords.y > m_maxMapSize.y){
				std::cout << "! Tile is out of range: "<< tileCoords.x << " " << tileCoords.y << std::endl;
				continue;
			}
			colliderId = entityMgr->add(EntityType::Tile,"Collider",colliderId);
			if (colliderId < 0){ continue; }
			if(!m_tileMap.emplace(convertCoords(tileCoords.x,tileCoords.y),entityMgr->find(colliderId)).second){
				// Duplicate tile detected!
				std::cout << "! Duplicate tile! : " << tileCoords.x 
					<< "" << tileCoords.y << std::endl;
				entityMgr->remove(colliderId);
				continue;
			}
			entityMgr->find(colliderId)->setPosition(tileCoords.x,tileCoords.y);
		} else if(type == "ENVIRONMENT"){
			int enviroId = 0;
			keystream >> enviroId;
			int enviroMapId = entityMgr->add(EntityType::Tile, "Environment", enviroId);
			if (enviroMapId < 0){ std::cout << "! Bad env id: " << enviroMapId << std::endl; continue;  }
			float enviroX = 0; float enviroY = 0;
			keystream >> enviroX >> enviroY;
			entityMgr->find(enviroMapId)->setPosition(enviroX, enviroY);
		}else if(type == "BACKGROUND"){
			if (m_backgroundTexture != ""){ continue; }
			keystream >> m_backgroundTexture;
			if (!m_context->m_textureManager->requireResource(m_backgroundTexture)){
				m_backgroundTexture = "";
				continue;
			}
			sf::Texture* texture = m_context->m_textureManager->getResource(m_backgroundTexture);
			m_background.setTexture(*texture);
			sf::Vector2f viewSize = m_currentScene->getView().getSize();
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
			//keystream >> m_defaultTile.m_friction.x >> m_defaultTile.m_friction.y;
		} else if(type == "NEXTMAP"){
			keystream >> m_nextMap;
		} else if(type == "PLAYER"){
			if (playerId != -1){ continue; }
			// Set up the player position here.
			playerId = entityMgr->add(EntityType::Player);
			if (playerId < 0){ continue; }
			float playerX = 0; float playerY = 0;
			keystream >> playerX >> playerY;
			entityMgr->find(playerId)->setPosition(playerX,playerY);
			m_playerStart = sf::Vector2f(playerX, playerY);
		} else if(type == "ENEMY"){
			std::string enemyName;
			keystream >> enemyName;
			int enemyId = entityMgr->add(EntityType::Enemy, enemyName);
			if (enemyId < 0){ continue; }
			float enemyX = 0; float enemyY = 0;
			keystream >> enemyX >> enemyY;
			entityMgr->find(enemyId)->setPosition(enemyX, enemyY);
		} else {
			// Something else.
			std::cout << "! Unknown type \"" << type << "\"." << std::endl;
		}
	}
	mapFile.close();
	std::cout << "--- Map Loaded! ---" << std::endl;
}

void Map::loadNext(){ m_loadNextMap = true; }

void Map::loadTiles(){
	/*Collider *collider = new Collider(m_context->m_entityManager);
	for(size_t i = 0; i < m_context->m_entityManager->getTileCant(); i++){
		m_tileSet.emplace(i, new Collider(m_context->m_entityManager,i));
	}
	Environment *enviro = new Environment(m_context->m_entityManager);
	Triggerable *triggerable = new Triggerable(m_context->m_entityManager);

		for(size_t i = 0; i < l_path->size();i++){
	 loadt
		std::ifstream file;
		file.open(l_path[i]);
		if (!file.is_open()){ std::cout << "! Failed loading tile set file: " << l_path << std::endl; return; }
		std::string line;
		while(std::getline(file,line)){
			if (line[0] == '|'){ continue; }
			std::stringstream keystream(line);
			int tileId;
			keystream >> tileId;
			if (tileId < 0){ continue; }
			TileInfo* tile = new TileInfo(m_context,"TileSheet",tileId);
			keystream >> tile->m_name >> tile->m_friction.x >> tile->m_friction.y 
			>> tile->m_deadly >> tile->m_frameStart >> tile->m_frameEnd
			>> tile->m_frameTime >> tile->m_frameActionStart >> tile->m_frameActionEnd;
			if (tile->m_frameEnd > 0){
				Anim_Rect* anim = new Anim_Rect(tile->m_frameStart, tile->m_frameEnd,
				 tile->m_frameTime, tile->m_frameActionStart, tile->m_frameActionEnd);
				for(size_t i = 0; i <= anim->getEndFrame(); i++){
					keystream >> tile->coordCrop.left >> tile->coordCrop.top >> tile->coordCrop.width >> tile->coordCrop.height;
					anim->setFrameRect(anim->getFrameRow(), tile->coordCrop);
				/* std::cout<<"coord tile "<<i<<" "<<tile->coordCrop.left<<" "<<tile->coordCrop.top<<" "<<
				 tile->coordCrop.width<<" "<<tile->coordCrop.height<<std::endl; 
				}
				anim->setName(tile->m_name);
				anim->Reset();
				m_animations.emplace(tile->m_name,anim);
				anim->Play();
			}else{
				keystream >> tile->coordCrop.left >> tile->coordCrop.top >> tile->coordCrop.width >> tile->coordCrop.height;
			}
				std::cout<<"load en map tile "<<tile->coordCrop.left<<" "<<tile->coordCrop.top<<" "<<
				 tile->coordCrop.width<<" "<<tile->coordCrop.height<<std::endl;

			if(!m_tileSet.emplace(tileId,tile).second){
				// Duplicate tile detected!
				std::cout << "! Duplicate tile type: " << tile->m_name << std::endl;
				delete tile;
			}
		}
		file.close(); 
	}*/
}

void Map::update(float l_dT){
	if(m_loadNextMap){
		purgeMap();
		m_loadNextMap = false;
		if(m_nextMap != ""){
			loadMap(m_nextMap);
		} else {
			m_currentScene->getSceneManager()->switchTo(SceneType::GameOver);
		}
		m_nextMap = "";
	}
	sf::FloatRect viewSpace = m_context->m_wind->getViewSpace();
	m_background.setPosition(viewSpace.left, viewSpace.top);
}

void Map::draw(){
	sf::RenderWindow* l_wind = m_context->m_wind->getRenderWindow();
	l_wind->draw(m_background);
	sf::FloatRect viewSpace = m_context->m_wind->getViewSpace();

	sf::Vector2i tileBegin(floor(viewSpace.left / Sheet::Tile_Size),floor(viewSpace.top / Sheet::Tile_Size));
	sf::Vector2i tileEnd(ceil((viewSpace.left + viewSpace.width) / Sheet::Tile_Size),
		ceil((viewSpace.top + viewSpace.height) / Sheet::Tile_Size));

	unsigned int count = 0;
	for(int x = tileBegin.x; x <= tileEnd.x; ++x){
		for(int y = tileBegin.y; y <= tileEnd.y; ++y){
			if(x < 0 || y < 0){ continue; }
			Tile* tile = getTile(x,y);
			if (!tile){ continue; }
			sf::Sprite& sprite = tile->m_properties->m_sprite;
			sprite.setPosition(x * Sheet::Tile_Size, y * Sheet::Tile_Size);
			l_wind->draw(sprite);
			++count;
		}
	}
}

unsigned int Map::convertCoords(unsigned int l_x, unsigned int l_y){
	return (l_x * m_maxMapSize.x) + l_y; // Row-major.
}

void Map::purgeMap(){
	m_tileCount = 0;
	for (auto &itr : m_tileMap){
		delete itr.second;
	}
	m_tileMap.clear();
	m_context->m_entityManager->purge();

	if (m_backgroundTexture == ""){ return; }
	m_context->m_textureManager->releaseResource(m_backgroundTexture);
	m_backgroundTexture = "";
}

void Map::purgeTileSet(){
	for (auto &itr : m_tileSet){
		delete itr.second;
	}
	m_tileSet.clear();
	m_tileSetCount = 0;
}