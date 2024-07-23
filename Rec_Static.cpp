#include "Rec_Static.h"

void Rec_Static::cropSprite(sf::Vector2f l_scale){
	//std::cout <<"escala "<<this->getScale()<<std::endl;
	sf::Vector2f nulo(1.0,1.0);
	if(l_scale != nulo){
		m_spriteSheet->cropSprite(m_frames[0].second,l_scale);
	}else{
		m_spriteSheet->cropSprite(m_frames[0].second);
	}
}

void Rec_Static::frameStep(){
	
}

void Rec_Static::readIn(std::stringstream& l_stream){
	l_stream >> m_frameStart >> m_frameEnd >> m_frameRow
		>> m_frameTime >> m_frameActionStart >> m_frameActionEnd;
}


