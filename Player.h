#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "Animation.h"

class Player : virtual public Entity{
public:
	Player(const sf::Vector2f &pos);
	void update(double elapsed) override;				// 
	void initPhysics();									//  Updates all physics and priv vars
	void loadIdle();
	void move(const float dir_x);	  					//
	void updatePhysics();								//
	void draw(sf::RenderTarget & target) override;
	bool getMovement(); // Returns true if moving right, false if moving left
	void bounce(); //Makes the player bounce
	float getVelY();
	float getVelX();	
	void separate(sf::FloatRect overlap, const Entity & ent2);
	bool isFalling(); //Returns true if the player is falling
	//void teleport(int x); // Teleports the play to given x value
	
private:
	sf::Vector2f m_pos;
	//Physics
	float velocity_max;
	float velocity_min;
	float velocity_max_y;
	float drag;
	float m_gravity;
	
	sf::IntRect rect_animation;
	Animation anim_idle;
	bool canJump = true;
	bool isJumping = false;	
	bool isDead = false;
	double timePassedWalk;
	int maxHealth;
	int currentHealth;
	
	std::vector<sf::Texture> v_tex;
};

#endif

