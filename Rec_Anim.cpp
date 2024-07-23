#include "Rec_Anim.h"

Rec_Anim::Rec_Anim(){}

Rec_Anim::Rec_Anim(int frameStart, int frameEnd, int frameTime, int frameActionStart, int frameActionEnd){
	m_frameStart = frameStart;
	m_frameEnd = frameEnd;
	m_frameTime = frameTime;
	m_frameActionStart = frameActionStart;
	m_frameActionEnd = frameActionEnd;
}

void Rec_Anim::cropSprite(sf::Vector2f l_scale){
	sf::Vector2f nulo(1.0,1.0);
	if(l_scale != nulo){
		m_spriteSheet->cropSprite(m_frames[m_frameCurrent].second,l_scale);
	}else {
		m_spriteSheet->cropSprite(m_frames[m_frameCurrent].second);
	}
}

void Rec_Anim::frameStep(){
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

void Rec_Anim::readIn(std::stringstream& l_stream){
	l_stream >> m_frameRow >> m_frameStart >> m_frameEnd >> 
		m_frameTime >> m_frameActionStart >> m_frameActionEnd;
}

