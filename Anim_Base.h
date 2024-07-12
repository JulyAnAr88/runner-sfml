#ifndef ANIM_BASE_H
#define ANIM_BASE_H

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>
class SpriteSheet;


using FrameContainer = std::vector<std::pair<int,sf::IntRect>>;
using Frame = unsigned int;

class Anim_Base{
	friend class SpriteSheet;
public:
	Anim_Base();
	virtual ~Anim_Base();

	void setSpriteSheet(SpriteSheet* l_sheet);
	void setFrame(Frame l_frame);
	void setStartFrame(Frame l_frame);
	void setEndFrame(Frame l_frame);
	void setFrameRow(Frame l_row);
	void setActionStart(Frame l_frame);
	void setActionEnd(Frame l_frame);
	void setFrameTime(float l_time);
	void setLooping(bool l_loop);
	void setName(const std::string& l_name);

	SpriteSheet* getSpriteSheet();
	Frame getFrame();
	Frame getStartFrame();
	Frame getEndFrame();
	Frame getFrameRow();
	FrameContainer getFrameContainer();
	int getActionStart();
	int getActionEnd();
	float getFrameTime();
	float getElapsedTime();
	bool isLooping();
	bool isPlaying();
	bool isInAction();
	std::string getName();

	void Play();
	void Pause();
	void Stop();
	void Reset();

	virtual void update(const float& l_dT);

	friend std::stringstream& operator >>(
		std::stringstream& l_stream, Anim_Base& a)
	{
		a.readIn(l_stream);
		return l_stream;
	}
protected:
	virtual void frameStep() = 0;
	virtual void cropSprite() = 0;
	virtual void readIn(std::stringstream& l_stream) = 0;
	virtual void setFrameRect(int anim, sf::IntRect crop) = 0;

	Frame m_frameCurrent;
	Frame m_frameStart;
	Frame m_frameEnd;
	Frame m_frameRow;
	int m_frameActionStart;
	int m_frameActionEnd;
	float m_frameTime;
	float m_elapsedTime;
	bool m_loop;
	bool m_playing;

	std::string m_name;

	SpriteSheet* m_spriteSheet;
	
	FrameContainer m_frames;
};
#endif

