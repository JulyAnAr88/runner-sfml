#include "Collider.h"

Collider::Collider(EntityManager *l_entityMgr)
    : Tile(l_entityMgr)
{
    load("Collider.char");
    m_type = EntityType::Tile;
}

Collider::~Collider(){
}

void Collider::onEntityCollision(Entity *l_collider){
}

void Collider::update(float l_dT){
    Tile::update(l_dT);
}
