#include "Player.h"
#include "EntityManager.h"
#include "SceneManager.h"

Player::Player(EntityManager* l_entityMgr)
	: Character(l_entityMgr)
{
	load("Player.char");
	m_type = EntityType::Player;

	EventManager* events = m_entityManager->getContext()->m_eventManager;
	events->addCallback<Player>(SceneType::Game, "Player_MoveLeft", &Player::react, this);
	events->addCallback<Player>(SceneType::Game, "Player_MoveRight", &Player::react, this);
	events->addCallback<Player>(SceneType::Game, "Player_Jump", &Player::react, this);
}

Player::~Player(){
	EventManager* events = m_entityManager->getContext()->m_eventManager;
	events->removeCallback(SceneType::Game, "Player_MoveLeft");
	events->removeCallback(SceneType::Game, "Player_MoveRight");
	events->removeCallback(SceneType::Game, "Player_Jump");
}

void Player::react(EventDetails* l_details){
	if (l_details->m_name == "Player_MoveLeft"){
		Character::move(Direction::Left);
	} else if (l_details->m_name == "Player_MoveRight"){
		Character::move(Direction::Right);
	} else if (l_details->m_name == "Player_Jump"){
		Character::jump();
	} 
}

void Player::onEntityCollision(Entity* l_collider, bool l_attack){
	if (m_state == EntityState::Dying){ return; }
	if(l_attack){
		if (!m_spriteSheet.getCurrentAnim()->isInAction()){ return; }
		if (l_collider->getType() != EntityType::Enemy &&
			l_collider->getType() != EntityType::Player)
		{
			return;
		}
		Character* opponent = (Character*)l_collider;
		opponent->getHurt(1);
		if(m_position.x > opponent->getPosition().x){
			opponent->addVelocity(-32,0);
		} else {
			opponent->addVelocity(32,0);
		}
	} else {
		// Other behavior.
	}
}