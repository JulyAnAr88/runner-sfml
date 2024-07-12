#include "Entity.h"
#include "EntityManager.h"
#include "SharedContext.h"
#include "Map.h"
#include <stddef.h>

Entity::Entity(EntityManager* l_entityMgr)
	:m_entityManager(l_entityMgr), m_name("Base"), 
	m_type(EntityType::Base), m_id(0), m_referenceTile(nullptr),
	m_state(EntityState::Idle){}

Entity::~Entity(){}

void Entity::setPosition(float l_x, float l_y){
	m_position = sf::Vector2f(l_x,l_y);
	updateHitbox();
}

void Entity::setPosition(const sf::Vector2f& l_pos){
	m_position = l_pos;
	updateHitbox();
}

void Entity::setSize(float l_x, float l_y){
	m_size = sf::Vector2f(l_x,l_y);
	updateHitbox();
}

void Entity::setAcceleration(float l_x, float l_y){
	m_acceleration = sf::Vector2f(l_x,l_y);
}

void Entity::setState(const EntityState& l_state){
	if (m_state == EntityState::Dying){ return; }
	m_state = l_state;
}

const sf::Vector2f& Entity::getSize()const{ return m_size; }
std::string Entity::getName()const{ return m_name; }
EntityState Entity::getState()const{ return m_state; }
unsigned int Entity::getId()const{ return m_id; }
EntityType Entity::getType()const{ return m_type; }
const sf::Vector2f& Entity::getPosition()const{ return m_position; }

void Entity::move(float l_x, float l_y){
	m_positionOld = m_position;
	m_position += sf::Vector2f(l_x,l_y);
	sf::Vector2u mapSize = m_entityManager->getContext()->m_gameMap->getMapSize();
	if(m_position.x < 0){
		m_position.x = 0;
	} else if(m_position.x > (mapSize.x + 1) * Sheet::Tile_Size){
		m_position.x = (mapSize.x + 1) * Sheet::Tile_Size;
	}

	if(m_position.y < 0){
		m_position.y = 0;
	} else if(m_position.y > (mapSize.y + 1) * Sheet::Tile_Size){
		m_position.y = (mapSize.y + 1) * Sheet::Tile_Size;
		setState(EntityState::Dying);
	}
	updateHitbox();
}

void Entity::addVelocity(float l_x, float l_y){
	m_velocity += sf::Vector2f(l_x,l_y);
	if(abs(m_velocity.x) > m_maxVelocity.x){
		if(m_velocity.x < 0){ m_velocity.x = -m_maxVelocity.x; }
		else { m_velocity.x = m_maxVelocity.x; }
	}

	if(abs(m_velocity.y) > m_maxVelocity.y){
		if(m_velocity.y < 0){ m_velocity.y = -m_maxVelocity.y; }
		else { m_velocity.y = m_maxVelocity.y; }
	}
}

void Entity::accelerate(float l_x, float l_y){
	m_acceleration += sf::Vector2f(l_x,l_y);
}

void Entity::applyFriction(float l_x, float l_y){
	if(m_velocity.x != 0){
		if(abs(m_velocity.x) - abs(l_x) < 0){ m_velocity.x = 0; }
		else {
			if(m_velocity.x < 0){ m_velocity.x += l_x; }
			else { m_velocity.x -= l_x; }
		}
	}

	if(m_velocity.y != 0){
		if (abs(m_velocity.y) - abs(l_y) < 0){ m_velocity.y = 0; }
		else {
			if(m_velocity.y < 0){ m_velocity.y += l_y; }
			else { m_velocity.y -= l_y; }
		}
	}
}

/* bool Entity::collideWith(const Entity & ent2) {
	auto r1 = this->getGlobalBounds();
	auto r2 = ent2.getGlobalBounds();
	return r1.intersects(r2);
} */

void Entity::separate(sf::FloatRect overlap, const Entity & ent2){
	
	if(overlap.width < overlap.height){
		if(this->getPosition().x > ent2.getPosition().x){
			move(overlap.width,0);
		}else if(this->getPosition().x < ent2.getPosition().x){			
			move(-overlap.width,0);
		}
	}else{
		if(this->getPosition().y > ent2.getPosition().y){
			move(0,overlap.height);
			addVelocity(0,0);
		}else if(this->getPosition().y < ent2.getPosition().y){
			move(0,-overlap.height);
			addVelocity(0,0);/* 
			this->canJump = true;
			this->isJumping = false; */
		}
	}
	
}


sf::FloatRect Entity::getGlobalBounds(){
	return this->m_hitbox;	
}

void Entity::updateHitbox(){
	m_hitbox = sf::FloatRect(m_position.x - (m_size.x / 2),m_position.y - m_size.y, m_size.x,m_size.y);
}

/**
 * Axis-Aligned Bounding Box collision detection
 */
sf::FloatRect Entity::checkCollision(Entity &b){
	sf::FloatRect retval;
	
	sf::FloatRect rA = this->getGlobalBounds();
	sf::FloatRect rB = b.getGlobalBounds();	
	
	auto rightMostLeft = rA.left < rB.left ? rB.left : rA.left;
	auto leftMostRight = rA.width+rA.left > rB.width+rB.left ? rB.width+rB.left : rA.width+rA.left;
	auto bottomMostTop = rA.top < rB.top ? rB.top : rA.top;
	auto topMostBottom = rA.height+rA.top > rB.height+rB.top ? rB.height+rB.top : rA.height+rA.top;
	
	// "make sense" means that left is left and right is right.
	bool makesSenseHorizontal = rightMostLeft < leftMostRight;
	bool makesSenseVertical = bottomMostTop < topMostBottom;
	
	if (makesSenseHorizontal && makesSenseVertical){
		retval.left = rightMostLeft;
		retval.top = bottomMostTop;
		retval.width = leftMostRight - rightMostLeft;
		retval.height = topMostBottom - bottomMostTop;
		return retval;
	}else{
		return retval;
	}
}

void Entity::update(float l_dT){
	Map* map = m_entityManager->getContext()->m_gameMap;
	float gravity = map->getGravity();
	accelerate(0,gravity);
	addVelocity(m_acceleration.x * l_dT, m_acceleration.y * l_dT);
	setAcceleration(0.0f, 0.0f);
	sf::Vector2f frictionValue;
	if(m_referenceTile){
		frictionValue = m_referenceTile->m_friction;
		if(m_referenceTile->m_deadly){ setState(EntityState::Dying); }
	} else if(map->getDefaultTile()){
		frictionValue = map->getDefaultTile()->m_friction;
	} else {
		frictionValue = m_friction;
	}

	float friction_x = (m_speed.x * frictionValue.x) * l_dT;
	float friction_y = (m_speed.y * frictionValue.y) * l_dT;
	applyFriction(friction_x, friction_y);
	sf::Vector2f deltaPos = m_velocity * l_dT;
	move(deltaPos.x, deltaPos.y);
}

