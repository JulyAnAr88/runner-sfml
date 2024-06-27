#include "Hitbox.h"
#include <cstddef>

Hitbox::Hitbox() {
	
}


sf::FloatRect Hitbox::checkCollision(Hitbox &a, Hitbox &b){
	sf::FloatRect retval;

	sf::FloatRect rA = a.getHitbox();
	sf::FloatRect rB = b.getHitbox();
		
	bool rightmostLeft = rA.left < rB.left ? rB.left : rA.left;
    bool leftmostRight = rA.width > rB.width ? rB.width : rA.width;
    bool bottommostTop = rA.top < rB.top ? rB.top : rA.top;
    bool topmostBottom = rA.height > rB.height ? rB.height : rA.height;

    // "make sense" means that left is left and right is right.
    bool makesSenseHorizontal = rightmostLeft < leftmostRight;
    bool makesSenseVertical = bottommostTop < topmostBottom;
	
    if (makesSenseHorizontal && makesSenseVertical){
        //sf::FloatRect *retval = new sf::FloatRect();
        retval.left = rightmostLeft;
        retval.top = bottommostTop;
        retval.width = leftmostRight - rightmostLeft;
        retval.height = topmostBottom - bottommostTop;
        return retval;
    }else{
        return retval;
    }
}
