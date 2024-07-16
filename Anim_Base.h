#ifndef ANIM_BASE_H
#define ANIM_BASE_H

#include <string>
#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>
class SpriteSheet;


using FrameContainer = std::vector<std::pair<int,sf::IntRect>>;
class Anim_Base{
	friend class SpriteSheet;
public:
	Anim_Base();
	virtual ~Anim_Base();

	void setSpriteSheet(SpriteSheet* l_sheet);
	void setFrame(int l_frame);
	void setStartFrame(int l_frame);
	void setEndFrame(int l_frame);
	void setFrameRow(int l_row);
	void setActionStart(int l_frame);
	void setActionEnd(int l_frame);
	void setFrameTime(float l_time);
	void setLooping(bool l_loop);
	void setName(const std::string& l_name);
	void setFrameRect(int anim, sf::IntRect crop);

	SpriteSheet* getSpriteSheet();
	int getFrame();
	int getStartFrame();
	int getEndFrame();
	int getFrameRow();
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

	int m_frameCurrent;
	int m_frameStart;
	int m_frameEnd;
	int m_frameRow;
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

