#include "Animation.h"
#include "SpriteSheet.h"

Animation::Animation(): m_frameCurrent(0), m_frameStart(0), m_frameEnd(0),
	m_frameRow(0), m_frameTime(0.f), m_elapsedTime(0.f), m_frameActionStart(-1),
	m_frameActionEnd(-1), m_loop(false), m_playing(false){}

Animation::~Animation(){}

void Animation::setFrame(int l_frame){
	if((l_frame >= m_frameStart && l_frame <= m_frameEnd) ||
		(l_frame >= m_frameEnd && l_frame <= m_frameStart))
	{
		m_frameCurrent = l_frame;
	}
}

void Animation::setFrameRect(int anim, sf::IntRect crop, float l_scale){
	m_frames.push_back(std::make_pair(anim,crop));
	m_scale = l_scale;
}

bool Animation::isInAction(){
	if (m_frameActionStart == -1 || m_frameActionEnd == -1){ return true; }
	return (m_frameCurrent >= m_frameActionStart && m_frameCurrent <= m_frameActionEnd);
}

void Animation::Reset(){
	m_frameCurrent = m_frameStart;
	m_elapsedTime = 0.0f;
	cropSprite();
}

void Animation::update(const float& l_dT){
	if (!m_playing){ return; }
	m_elapsedTime += l_dT;
	if (m_elapsedTime < m_frameTime){ return; }
	frameStep();
	cropSprite();
	m_elapsedTime = 0;
}

void Animation::setSpriteSheet(SpriteSheet* l_sheet){ m_spriteSheet = l_sheet; }
void Animation::setStartFrame(int l_frame){ m_frameStart = l_frame; }
void Animation::setEndFrame(int l_frame){ m_frameEnd = l_frame; }
void Animation::setFrameRow(int l_row){ m_frameRow = l_row; }
void Animation::setActionStart(int l_frame){ m_frameActionStart = l_frame; }
void Animation::setActionEnd(int l_frame){ m_frameActionEnd = l_frame; }
void Animation::setFrameTime(float l_time){ m_frameTime = l_time; }
void Animation::setLooping(bool l_loop){ m_loop = l_loop; }
void Animation::setName(const std::string& l_name){ m_name = l_name; }

SpriteSheet* Animation::getSpriteSheet(){ return m_spriteSheet; }
int Animation::getFrame(){ return m_frameCurrent; }
int Animation::getStartFrame(){ return m_frameStart; }
int Animation::getEndFrame(){ return m_frameEnd; }
int Animation::getFrameRow(){ return m_frameRow; }
FrameContainer Animation::getFrameContainer(){ return m_frames;}
int Animation::getActionStart() { return m_frameActionStart; }
int Animation::getActionEnd(){ return m_frameActionEnd; }
float Animation::getFrameTime(){ return m_frameTime; }
float Animation::getElapsedTime(){ return m_elapsedTime; }
float Animation::getScale(){ return m_scale;}
std::string Animation::getName() { return m_name; }
bool Animation::isLooping(){ return m_loop; }
bool Animation::isPlaying(){ return m_playing; }

void Animation::Play(){ m_playing = true; }
void Animation::Pause(){ m_playing = false; }
void Animation::Stop(){ m_playing = false; Reset(); }