#include "Anim_Base.h"
#include "SpriteSheet.h"

Anim_Base::Anim_Base(): m_frameCurrent(0), m_frameStart(0), m_frameEnd(0),
	m_frameRow(0), m_frameTime(0.f), m_elapsedTime(0.f), m_frameActionStart(-1),
	m_frameActionEnd(-1), m_loop(false), m_playing(false){}

Anim_Base::~Anim_Base(){}

void Anim_Base::setFrame(int l_frame){
	if((l_frame >= m_frameStart && l_frame <= m_frameEnd) ||
		(l_frame >= m_frameEnd && l_frame <= m_frameStart))
	{
		m_frameCurrent = l_frame;
	}
}

void Anim_Base::setFrameRect(int anim, sf::IntRect crop){
	m_frames.push_back(std::make_pair(anim,crop));
}

bool Anim_Base::isInAction(){
	if (m_frameActionStart == -1 || m_frameActionEnd == -1){ return true; }
	return (m_frameCurrent >= m_frameActionStart && m_frameCurrent <= m_frameActionEnd);
}

void Anim_Base::Reset(){
	m_frameCurrent = m_frameStart;
	m_elapsedTime = 0.0f;
	cropSprite();
}

void Anim_Base::update(const float& l_dT){
	if (!m_playing){ return; }
	m_elapsedTime += l_dT;
	if (m_elapsedTime < m_frameTime){ return; }
	frameStep();
	cropSprite();
	m_elapsedTime = 0;
}

void Anim_Base::setSpriteSheet(SpriteSheet* l_sheet){ m_spriteSheet = l_sheet; }
void Anim_Base::setStartFrame(int l_frame){ m_frameStart = l_frame; }
void Anim_Base::setEndFrame(int l_frame){ m_frameEnd = l_frame; }
void Anim_Base::setFrameRow(int l_row){ m_frameRow = l_row; }
void Anim_Base::setActionStart(int l_frame){ m_frameActionStart = l_frame; }
void Anim_Base::setActionEnd(int l_frame){ m_frameActionEnd = l_frame; }
void Anim_Base::setFrameTime(float l_time){ m_frameTime = l_time; }
void Anim_Base::setLooping(bool l_loop){ m_loop = l_loop; }
void Anim_Base::setName(const std::string& l_name){ m_name = l_name; }

SpriteSheet* Anim_Base::getSpriteSheet(){ return m_spriteSheet; }
int Anim_Base::getFrame(){ return m_frameCurrent; }
int Anim_Base::getStartFrame(){ return m_frameStart; }
int Anim_Base::getEndFrame(){ return m_frameEnd; }
int Anim_Base::getFrameRow(){ return m_frameRow; }
FrameContainer Anim_Base::getFrameContainer(){ return m_frames;}
int Anim_Base::getActionStart() { return m_frameActionStart; }
int Anim_Base::getActionEnd(){ return m_frameActionEnd; }
float Anim_Base::getFrameTime(){ return m_frameTime; }
float Anim_Base::getElapsedTime(){ return m_elapsedTime; }
std::string Anim_Base::getName(){ return m_name; }
bool Anim_Base::isLooping(){ return m_loop; }
bool Anim_Base::isPlaying(){ return m_playing; }

void Anim_Base::Play(){ m_playing = true; }
void Anim_Base::Pause(){ m_playing = false; }
void Anim_Base::Stop(){ m_playing = false; Reset(); }
