#ifndef ANIM_RECT_H
#define ANIM_RECT_H
#include "Anim_Base.h"

class Anim_Rect : public Anim_Base{
protected:
	void frameStep();
	void cropSprite();
	void readIn(std::stringstream& l_stream);

	void setFrameRect(int anim, sf::IntRect crop);
	
private:
	int m_animX;
	int m_animY;
	int m_animWidth;
	int m_animHeight;
};

#endif

