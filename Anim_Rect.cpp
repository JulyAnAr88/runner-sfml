#include "Anim_Rect.h"
#include "SpriteSheet.h"

void Anim_Rect::cropSprite(){
	sf::IntRect rect(m_animX, m_animY, m_animWidth, m_animHeight);
	m_spriteSheet->cropSprite(rect);
}

void Anim_Rect::frameStep(){
	if (m_frameStart < m_frameEnd){ ++m_frameCurrent; }
	else { --m_frameCurrent; }

	if ((m_frameStart < m_frameEnd && m_frameCurrent > m_frameEnd) ||
		(m_frameStart > m_frameEnd && m_frameCurrent < m_frameEnd))
	{
		if (m_loop){ m_frameCurrent = m_frameStart; return; }
		m_frameCurrent = m_frameEnd;
		Pause();
	}
}

void Anim_Rect::readIn(std::stringstream& l_stream){
	l_stream >> m_frameRow >> m_frameStart >> m_frameEnd >> 
		m_frameTime >> m_frameActionStart >> m_frameActionEnd;
}

void Anim_Rect::setFrameRect(int anim, sf::IntRect crop){
	m_frames.emplace_back(anim,crop);
}