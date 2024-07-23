#ifndef REC_ANIM_H
#define REC_ANIM_H

#include "Animation.h"
#include "SpriteSheet.h"

class Rec_Anim : public Animation{
protected:
	void frameStep();
	void cropSprite(sf::Vector2f l_scale);
	void readIn(std::stringstream& l_stream);
public:
	Rec_Anim();
	Rec_Anim(int frameStart, int frameEnd, int frameTime, 
		int frameActionStart, int frameActionEnd);
};

#endif