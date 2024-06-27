#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>

struct Frame {
	sf::IntRect rect;
	double duration; // in seconds
};

class Animation {
private:
	std::vector<Frame> frames;
	double totalLength;
	double totalProgress;
	sf::Sprite *target;
public:
	Animation(sf::Sprite& target);
	void addFrame(Frame& frame);	
	void update(double elapsed);
};

#endif

