#ifndef REC_STATIC_H
#define REC_STATIC_H

#include "Animation.h"
#include "Direction.h"
#include "SpriteSheet.h"

class Rec_Static : public Animation{
protected:
	void frameStep();
	void cropSprite(sf::Vector2f l_scale);
	void readIn(std::stringstream& l_stream);

	void setFrameRect(int anim, sf::IntRect crop){};
};

#endif
