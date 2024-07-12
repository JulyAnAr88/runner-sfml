#include "Anim_Rect.h"
#include "SpriteSheet.h"

void Anim_Rect::cropSprite(){
	m_spriteSheet->cropSprite(m_frames[m_frameCurrent].second);
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