#include "Player.h"
#include "SharedContext.h"
#include <windows.h>
#include <cmath>

Player::Player()
	: Character()
{
	load("char/Player.char");
	m_type = EntityType::Player;
}

Player::~Player(){ }

void Player::update(float l_dT){
	Character::update(l_dT);



	bool up = m_position.y - m_positionOld.y > 2.0;
	bool goToLeft = m_dir == Direction::Left;
	if(getState() != EntityState::Dying && getState() != EntityState::Hurt){
		//if(std::abs(m_velocity.y) >= 1.f){
		if(up){
			setState(EntityState::Jumping);
		} else if(std::abs(m_velocity.x) >= 0.1f){
			setState(EntityState::Walking);			
		} else {
			m_corriendo = 0;
			setState(EntityState::Idle);
		}
	} else if(getState() == EntityState::Hurt){
		if(!m_spriteSheet.getCurrentAnim()->isPlaying()){
			setState(EntityState::Idle);
		}
	 /*else if(getState() == EntityState::Dying){
		if(!m_spriteSheet.getCurrentAnim()->isPlaying()){
			
		}*/
	} 

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){ 
			Character::move(Direction::Right);
			Entity::move(MOVE_SPEED,0);
	} else	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){ 
			Character::move(Direction::Left);
			Entity::move(-MOVE_SPEED,0);
	} else{
		//m_corriendo = 0;
		if(!isJumping){
			this->addVelocity(0,0);
			m_speed.x = 0;
			setState(EntityState::Idle);
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
		if(goToLeft){
			if(!isJumping && canJump){
				Character::move(Direction::Left);
				Entity::move(-MOVE_SPEED,-m_jumpVelocity);
				Character::jump();
				isJumping = true;
				canJump = false;
			} 
		}else if(!isJumping && canJump){
			Character::move(Direction::Right);
			Entity::move(MOVE_SPEED,-m_jumpVelocity);
			Character::jump();
			isJumping = true;
			canJump = false;
		}
		
	}

	sf::Vector2u mapSize(WIDTH,HEIGHT);
	if(m_position.x < 0){
		m_position.x = 0;
	} else if(m_position.x > (mapSize.x + 1) * 32){
		m_position.x = (mapSize.x + 1) * 32;
	}

	if(m_position.y < 0){
		m_position.y = 0;
	} else if(m_position.y > (mapSize.y + 1) * 32){
		m_position.y = (mapSize.y + 1) * 32;
		die();
	}

	animate();		

	m_spriteSheet.update(l_dT);
	m_spriteSheet.setSpritePosition(m_position);
}



void Player::separate(sf::FloatRect overlap, const Entity & ent2){
	
	if(overlap.width < overlap.height){
		if(this->getPosition().x > ent2.getPosition().x){
			Entity::move(overlap.width,0);
		}else if(this->getPosition().x < ent2.getPosition().x){			
			Entity::move(-overlap.width,0);
		}
	}else{
		if(this->getPosition().y > ent2.getPosition().y){
			Entity::move(0,overlap.height);
			m_velocity.y=0;
		}else if(this->getPosition().y < ent2.getPosition().y){
			Entity::move(0,-overlap.height);
			m_velocity.y=0;
			this->canJump = true;
			this->isJumping = false;
		}
	}
	
}

 void Player::onEntityCollision(Entity* l_collider, bool l_attack){
} 


int Player::getHitpoints(){
    return m_hitpoints;
}

void Player::die(){
	setState(EntityState::Dying);
	animate();
}

bool Player::IsDead(){
    return getState() == EntityState::Dying;
}
