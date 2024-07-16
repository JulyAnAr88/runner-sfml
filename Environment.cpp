#include "Environment.h"

Environment::Environment(EntityManager* l_entityMgr) : Tile(l_entityMgr)
{
    load("Collider.char");
    m_type = EntityType::Environment;
}

Environment::~Environment() {	
}

void Environment::onEntityCollision(Entity *l_collider){
}

