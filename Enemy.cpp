#include "Enemy.h"
#include "SharedContext.h"

Enemy::Enemy()
	:Character()
	{ m_type = EntityType::Enemy; }

Enemy::~Enemy(){}

int Enemy::hurt(){
    return m_hitpoints;
}

void Enemy::onEntityCollision(Entity* l_collider, bool l_attack){

}

void Enemy::update(float l_dT){
	Character::update(l_dT/10000);
	setState(EntityState::Move);

	int random = rand() % 10 -5;
	Entity::move(-MOVE_SPEED*0.5,0);
	if(m_name == "Mosquito"){
		m_position.y = m_position.y+random;
		animate();	

		m_spriteSheet.update(l_dT/50);
	}else{
		animate();	

		m_spriteSheet.update(l_dT/500);
	}
	
	m_spriteSheet.setSpritePosition(m_position);
}
