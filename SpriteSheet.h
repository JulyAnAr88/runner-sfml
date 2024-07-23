#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Animation.h"
#include "Rec_Static.h"
#include "Rec_Anim.h"
#include "Direction.h"
#include <map>

using Animations = std::map<std::string, Animation*>;
using Static_Animations = std::map<int, Animation*>;

class SpriteSheet{
public:
	SpriteSheet();
	~SpriteSheet();

	void cropSprite(const sf::IntRect& l_rect, sf::Vector2f l_scale);
	void cropSprite(const sf::IntRect& l_rect);
	sf::Vector2i getSpriteSize()const;
	sf::Vector2f getSpritePosition()const;
	void setSpriteSize(const sf::Vector2i& l_size);
	void setSpritePosition(const sf::Vector2f& l_pos);

	void setDirection(const Direction& l_dir);
	Direction getDirection()const;

	bool loadSheet(const std::string& l_file);
	bool loadTileSheet(const std::string& l_file);
	void releaseSheet();

	Animation* getCurrentAnim();
	bool setAnimation(const std::string& l_name, 
		const bool& l_play = false, 
		const bool& l_loop = false);
	bool setAnimation(const int l_id, 
		const bool& l_play = false, 
		const bool& l_loop = false);

	void update(const float& l_dT);
	void draw(sf::RenderWindow* l_wnd);
private:
	std::string m_texture;
	sf::Sprite m_sprite;
	sf::Vector2i m_spriteSize;
	sf::Vector2f m_spriteScale;
	Direction m_direction;
	float m_scale = 1.0;

	std::string m_animType;
	Animations m_animations;
	Animation* m_animationCurrent;
	Static_Animations m_staticAnimations;

};

#endif