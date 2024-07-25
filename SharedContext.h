#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "BaseScene.h"
#include "Entity.h"
#include "Land.h"

#define WIDTH 1024
#define HEIGHT 600

#define GRAVITY 1500.0f
#define MOVE_SPEED 5

#define SPAWNING_TIME_MOSQUITO 600.0f
#define SPAWNING_TIME_SERPIENTE 900.0f
#define SPAWNING_TIME_ARBUSTO 800.0f
#define SPAWNING_TIME_ROCA 1200.0f

class Land;
class Entity;

struct SharedContext{
	SharedContext():
        m_baseScene(nullptr),
        m_entity(nullptr),
		m_gameMap(nullptr),
		m_wind(nullptr){}
	
    BaseScene* m_baseScene;
    Entity* m_entity;
	Land* m_gameMap;
	sf::RenderWindow* m_wind;
};


#endif
