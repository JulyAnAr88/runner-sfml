#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "TextureManager.h"
#include "Anim_Directional.h"
#include "Anim_Rect.h"
#include "Tile.h"
#include <map>

using Animations = std::map<std::string,Anim_Base*>;
using TileMap = std::map<int,Tile*>;

class SpriteSheet{
public:
	SpriteSheet(TextureManager* l_textMgr);
	~SpriteSheet();

	void cropSprite(const sf::IntRect& l_rect);
	sf::Vector2i getSpriteSize()const;
	sf::Vector2f getSpritePosition()const;
	void setSpriteSize(const sf::Vector2i& l_size);
	void setSpritePosition(const sf::Vector2f& l_pos);

	void setDirection(const Direction& l_dir);
	Direction getDirection()const;

	bool loadSheet(const std::string& l_file);
	bool loadTileSheet(const std::string& l_file, EntityManager& entityMgr);
	void releaseSheet();

	Anim_Base* getCurrentAnim();
	bool setAnimation(const std::string& l_name, 
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

	std::string m_animType;
	Animations m_animations;
	Anim_Base* m_animationCurrent;
	TileMap m_tiles;

	TextureManager* m_textureManager;
};

#endif

