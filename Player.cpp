#include "Animation.h"
#include "Player.h"
#include "Constants.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cmath>

Player::Player(const sf::Vector2f &pos) : /*Entity("img/nene.png"),*/
				m_pos(pos), 
				anim_idle(m_spr) {
	m_tex.loadFromFile("img/nene.png");
	loadIdle();
	m_spr.setTexture(m_tex);
	m_spr.setTextureRect(this->rect_animation);
	m_spr.setScale(0.35,0.35);
	m_spr.setOrigin(m_spr.getLocalBounds().width/2.f,m_spr.getLocalBounds().height*.75f);
	/*m_spr.setOrigin(m_spr.getLocalBounds().left+(m_spr.getGlobalBounds().width/2.f),
					m_spr.getGlobalBounds().top+(m_spr.getGlobalBounds().top/2.f));*/
	Frame f1,f2,f3;
	f1.duration = 0.01;
	f1.rect = sf::IntRect(3462,1778,284,476);
	f2.duration = 0.01;
	f2.rect = sf::IntRect(3750,1778,283,476);
	f3.duration = 0.01;
	f1.rect = sf::IntRect(2,2037,283,476);
	anim_idle.addFrame(f1);
	anim_idle.addFrame(f2);
	anim_idle.addFrame(f3);
	initPhysics();
	/*v_tex.resize(3);
	v_tex[0].loadFromFile("models/player_idle.png");
	v_tex[1].loadFromFile("models/player_movingUp.png");
	v_tex[2].loadFromFile("models/player_movingDown.png");*/
}

void Player::loadIdle(){
	this->rect_animation.left = 289;
	this->rect_animation.top = 2087;
	this->rect_animation.height = 477;
	this->rect_animation.width = 284;
}

void Player::update(double elapsed) {
	//std::cout<<"actualizando player"<<std::endl;
	Frame f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12,f13,f14,f15;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){ //para mover el jugador a la derecha
		if(this->canJump){
			m_spr.setScale(0.35,0.35);
			velocity.x += MOVE_SPEED;
			f1.duration = 50;
			f1.rect = sf::IntRect(2617,1250,285,468);
			f2.duration = 50;
			f2.rect = sf::IntRect(2906,1295,286,468);
			f3.duration = 50;
			f3.rect = sf::IntRect(3173,833,303,458);
			f4.duration = 50;
			f4.rect = sf::IntRect(991,707,320,452);
			f5.duration = 50;
			f5.rect = sf::IntRect(1315,708,322,452);
			f6.duration = 50;
			f6.rect = sf::IntRect(2238,734,308,454);
			f7.duration = 50;
			f7.rect = sf::IntRect(2,1095,294,463);
			f8.duration = 50;
			f8.rect = sf::IntRect(3196,1301,286,468);
			f9.duration = 50;
			f9.rect = sf::IntRect(290,1612,286,471);
			f10.duration = 50;
			f10.rect = sf::IntRect(1744,1173,291,467);
			f11.duration = 50;
			f11.rect = sf::IntRect(1928,715,306,454);
			f12.duration = 50;
			f12.rect = sf::IntRect(361,696,314,443);
			f13.duration = 50;
			f13.rect = sf::IntRect(679,706,308,445);
			f14.duration = 50;
			f14.rect = sf::IntRect(2871,790,298,456);
			f15.duration = 50;
			f15.rect = sf::IntRect(595,1155,287,465);
			anim_idle.addFrame(f1);
			anim_idle.addFrame(f2);
			anim_idle.addFrame(f3);
			anim_idle.addFrame(f4);
			anim_idle.addFrame(f5);
			anim_idle.addFrame(f6);
			anim_idle.addFrame(f7);
			anim_idle.addFrame(f8);
			anim_idle.addFrame(f9);
			anim_idle.addFrame(f10);
			anim_idle.addFrame(f11);
			anim_idle.addFrame(f12);
			anim_idle.addFrame(f13);
			anim_idle.addFrame(f14);
			anim_idle.addFrame(f15);
			//anim_idle.update(elapsed);
			if(this->canJump && this->timePassedWalk > 3){
				velocity.x += MOVE_SPEED* 1.2f;
				std::cout<<"corriendo"<<std::endl;
			}
		}
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){ // para mover el jugador a la izquierda
		if(this->canJump){
			m_spr.setScale(-0.35,0.35);
			velocity.x -= MOVE_SPEED;
		}
	}else{
		if(!this->isJumping){
		velocity.x = 0;
		this->timePassedWalk = 0;
		f1.duration = 50;
		f1.rect = sf::IntRect(289,2087,284,477);
		f2.duration = 50;
		f2.rect = sf::IntRect(3462,1778,284,476);
		f3.duration = 50;
		f3.rect = sf::IntRect(3750,1778,283,476);
		f4.duration = 50;
		f4.rect = sf::IntRect(2,2037,283,476);
		f5.duration = 50;
		f5.rect = sf::IntRect(2308,1694,282,475);
		f6.duration = 50;
		f6.rect = sf::IntRect(1445,1642,282,474);
		f7.duration = 50;
		f7.rect = sf::IntRect(1158,1634,283,472);
		f8.duration = 50;
		f8.rect = sf::IntRect(2,1562,284,471);
		f9.duration = 50;
		f9.rect = sf::IntRect(3775,1305,284,469);
		f10.duration = 50;
		f10.rect = sf::IntRect(2328,1222,285,468);
		f11.duration = 50;
		f11.rect = sf::IntRect(886,1163,286,466);
		f12.duration = 50;
		f12.rect = sf::IntRect(1176,1164,286,466);
		f13.duration = 50;
		f13.rect = sf::IntRect(3486,1305,285,469);
		f14.duration = 50;
		f14.rect = sf::IntRect(869,1633,285,472);
		f15.duration = 50;
		f15.rect = sf::IntRect(2020,1663,284,475);
		anim_idle.addFrame(f1);
		anim_idle.addFrame(f2);
		anim_idle.addFrame(f3);
		anim_idle.addFrame(f4);
		anim_idle.addFrame(f5);
		anim_idle.addFrame(f6);
		anim_idle.addFrame(f7);
		anim_idle.addFrame(f8);
		anim_idle.addFrame(f9);
		anim_idle.addFrame(f10);
		anim_idle.addFrame(f11);
		anim_idle.addFrame(f12);
		anim_idle.addFrame(f13);
		anim_idle.addFrame(f14);
		anim_idle.addFrame(f15);
		}
	}
	
	
	anim_idle.update(elapsed);
	velocity.y += m_gravity;
	
	m_pos +=  velocity;
	//if(m_pos.y>=300){
	if(this->canJump && !this->isJumping){
		
		velocity.y = 0;
		//m_pos.y = 480;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
			if (this->canJump && !this->isJumping){
				this->canJump = false;            
				this->isJumping = true;   /* */   
				velocity.y = -JUMP_SPEED;
			}
		}
	}
	
	/*
	sf::Vector2f charPos = m_spr.getPosition();*/
	if(m_spr.getPosition().x < 0) m_pos.x = m_spr.getLocalBounds().width/6.f;
	//if(charPos.x > WIDTH-m_spr.getGlobalBounds().width) m_pos.x = WIDTH;
	
	m_spr.setPosition(m_pos);
	//updatePhysics();
	
}

void Player::initPhysics ( ) {
	
	drag = 0.96;
	m_gravity = GRAVITY;
}

void Player::move (const float dir_x) { //WIP
	//aceleracion
	//velocity.x += dir_x*aceleration;
	/*if(std::abs(velocity.y)>velocity_max_y){
		velocity.x = velocity_max_y*((velocity.y<0.f)? -1.f:1.f);
	}
	//limitar la aceleracion
	if(std::abs(velocity.x)>velocity_max){
		velocity.x = velocity_max*((velocity.x<0.f)? -1.f:1.f);
	}*/
}

void Player::updatePhysics ( ) {
	//gravedad
	velocity.y += 0.5f * m_gravity;
	
	//desaceleracion
	//velocity = velocity*drag; // multiplico ambos valores de velocity por la desaceleracion con una sobrecarga que posee la clase vector2f
	
	//limitar la desaceleracion
	/*if(std::abs(velocity.x)<velocity_min)
		velocity.x=0.f;
	if(std::abs(velocity.y)<velocity_min)
		velocity.y=velocity_min;
	m_spr.move(velocity);*/
}

float Player::getVelY(){
	return this->velocity.y;
}

float Player::getVelX(){
	return this->velocity.x;
}

void Player::draw(sf::RenderTarget & target) {
	target.draw(this->m_spr);
}

void Player::bounce(){
	this->m_spr.setTexture(this->v_tex[0]);
	this->velocity.y=(-38);
}

bool Player::getMovement(){
	if (this->velocity.x>0)
	{
		return true;
	}
	return false;
}

void Player::separate(sf::FloatRect overlap, const Entity & ent2){
	
	if(overlap.width < overlap.height){
		if(this->getPosition().x > ent2.getPosition().x){
			this->m_pos.x += overlap.width;
		}else if(this->getPosition().x < ent2.getPosition().x){
			this->m_pos.x -= overlap.width;
		}
	}else{
		if(this->getPosition().y > ent2.getPosition().y){
			this->m_pos.x += overlap.height;
			velocity.y = 0;
		}else if(this->getPosition().y < ent2.getPosition().y){
			this->m_pos.y -= overlap.height;
			//velocity.y = 0;
			this->canJump = true;
			this->isJumping = false;
		}
	}
	
}

bool Player::isFalling(){
	//std::cerr <<"Velocity: " << this->velocity.y << std::endl;
	if (velocity.y>0)
	{
		this->m_spr.setTexture(this->v_tex[2]);
		return true;
	}
	this->m_spr.setTexture(this->v_tex[1]);
	return false;
}

/*void Player::teleport(int x){
	int y = m_spr.getPosition().y;
	m_spr.setPosition(x,y);
}*/
