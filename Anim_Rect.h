#ifndef ANIM_RECT_H
#define ANIM_RECT_H
#include "Anim_Base.h"

class Anim_Rect : public Anim_Base{
protected:
	void frameStep();
	void cropSprite();
	void readIn(std::stringstream& l_stream);
public:
	Anim_Rect();
	Anim_Rect(int frameStart, int frameEnd, int frameTime, 
		int frameActionStart, int frameActionEnd);
};

#endif

