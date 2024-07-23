#include "Entity.h"
#include "Land.h"
#include <stddef.h>

Entity::Entity()
	:m_name("Base"), m_type(EntityType::Base), m_id(0),
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

void Entity::setId(int i){m_id = i;}
void Entity::setName(std::string l_name){m_name = l_name;}

const sf::Vector2f& Entity::getSize()const{ return m_size; }
std::string Entity::getName()const{ return m_name; }
EntityState Entity::getState()const{ return m_state; }
unsigned int Entity::getId()const{ return m_id; }
EntityType Entity::getType()const{ return m_type; }
const sf::Vector2f& Entity::getPosition()const{ return m_position; }

void Entity::move(float l_x, float l_y){
	m_positionOld = m_position;
	m_position += sf::Vector2f(l_x,l_y);
	
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

/*bool Entity::collideWith(const Entity & ent2) {
	auto r1 = this->getGlobalBounds();
	auto r2 = ent2.getGlobalBounds();
	return r1.intersects(r2);
} */

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
	
	float gravity = GRAVITY; 
	accelerate(0,gravity);
	addVelocity(m_acceleration.x * l_dT, m_acceleration.y * l_dT);
	setAcceleration(0.0f, 0.0f);
	sf::Vector2f frictionValue(0.8,0.8);

	float friction_x = (m_speed.x * frictionValue.x) * l_dT;
	float friction_y = (m_speed.y * frictionValue.y) * l_dT;
	applyFriction(friction_x, friction_y);
	sf::Vector2f deltaPos = m_velocity * (l_dT/10);
	//std::cout<<"enemy "<<deltaPos.x<<std::endl;
	move(deltaPos.x, deltaPos.y);
	
}



