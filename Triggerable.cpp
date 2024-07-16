#include "Triggerable.h"

Triggerable::Triggerable(EntityManager *l_entityMgr)
    : Tile(l_entityMgr)
{
    load("Triggerable.char");
    m_type = EntityType::Tile;
}

Triggerable::~Triggerable(){
}

void Triggerable::onEntityCollision(Entity *l_collider){
}

void Triggerable::update(float l_dT){
    Tile::update(l_dT);
}

