#include "Animation.h"
#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>

Animation::Animation(sf::Sprite& target) { 
	this->target = &target;
	totalProgress = 0.0;
}

void Animation::addFrame(Frame& frame) {
	this->frames.push_back(std::move(frame)); 
	this->totalLength += frame.duration; 
}

void Animation::update(double elapsed) {
	// increase the total progress of the animation
	this->totalProgress += elapsed;
	
	// use this progress as a counter. Final frame at progress <= 0
	double progress = this->totalProgress;
	for(auto frame : this->frames) {
		progress -= (frame).duration;  
		
		// When progress is <= 0 or we are on the last frame in the list, stop
		if (progress <= 0.0 || &(frame) == &frames.back())
		{
			this->target->setTextureRect((frame).rect);  
			break; // we found our frame
		}
	}
}
