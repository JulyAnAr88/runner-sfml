#include "Enemy.h"

Enemy::Enemy(EntityManager* l_entityMgr)
	:Character(l_entityMgr), m_hasDestination(false){ m_type = EntityType::Enemy; }

Enemy::~Enemy(){}

void Enemy::onEntityCollision(Entity* l_collider, bool l_attack){

}

void Enemy::update(float l_dT){
	Character::update(l_dT);
	
}
