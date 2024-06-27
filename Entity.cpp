#include "Entity.h"
#include <stddef.h>

Entity::Entity(){
	m_tex.loadFromFile(m_tex);
	/*//m_spr.setTexture(m_tex);
	//_spr.setScale(0.75,0.75);*/
}

sf::Sprite &Entity::getSprite(){
	return m_spr;
}

bool Entity::collideWith(const Entity & ent2) {
	auto r1 = this->m_spr.getGlobalBounds();
	auto r2 = ent2.m_spr.getGlobalBounds();
	return r1.intersects(r2);
}

sf::FloatRect Entity::getGlobalBounds(){
	return m_spr.getGlobalBounds();	
}

sf::Vector2f Entity::getPosition() const{
	return m_spr.getPosition(); 
}

sf::FloatRect Entity::checkCollision(Entity &b){
	sf::FloatRect retval;
	
	sf::FloatRect rA = this->getGlobalBounds();
	sf::FloatRect rB = b.getGlobalBounds();	
	
	auto rightmostLeft = rA.left < rB.left ? rB.left : rA.left;
	auto leftmostRight = rA.width+rA.left > rB.width+rB.left ? rB.width+rB.left : rA.width+rA.left;
	auto bottommostTop = rA.top < rB.top ? rB.top : rA.top;
	auto topmostBottom = rA.height+rA.top > rB.height+rB.top ? rB.height+rB.top : rA.height+rA.top;
	
	// "make sense" means that left is left and right is right.
	bool makesSenseHorizontal = rightmostLeft < leftmostRight;
	bool makesSenseVertical = bottommostTop < topmostBottom;
	
	if (makesSenseHorizontal && makesSenseVertical){
		retval.left = rightmostLeft;
		retval.top = bottommostTop;
		retval.width = leftmostRight - rightmostLeft;
		retval.height = topmostBottom - bottommostTop;
		return retval;
	}else{
		return retval;
	}
}


