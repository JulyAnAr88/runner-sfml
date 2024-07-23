#include "SpriteSheet.h"
#include <cstdlib>

SpriteSheet::SpriteSheet() 
	:m_animationCurrent(nullptr), 
	m_spriteScale(1.f, 1.f){}

SpriteSheet::~SpriteSheet(){ releaseSheet(); }

void SpriteSheet::releaseSheet(){	
	m_animationCurrent = nullptr;
	while(m_animations.begin() != m_animations.end()){
		delete m_animations.begin()->second;
		m_animations.erase(m_animations.begin());
	}
}

sf::Vector2i SpriteSheet::getSpriteSize()const{ return m_spriteSize; }
sf::Vector2f SpriteSheet::getSpritePosition()const{ return m_sprite.getPosition(); }
Direction SpriteSheet::getDirection()const{ return m_direction; }
Animation* SpriteSheet::getCurrentAnim(){ return m_animationCurrent; }

void SpriteSheet::setSpriteSize(const sf::Vector2i& l_size){
	m_spriteSize = l_size;
	m_sprite.setOrigin(m_spriteSize.x / 2, m_spriteSize.y);
}

void SpriteSheet::setSpritePosition(const sf::Vector2f& l_pos){ m_sprite.setPosition(l_pos); }

void SpriteSheet::setDirection(const Direction& l_dir){
	if (l_dir == m_direction){ return; }
	m_direction = l_dir;
	if(m_direction == Direction::Left){
		m_animationCurrent->cropSprite({-0.3,0.3});
	}else{
		m_animationCurrent->cropSprite({0.3,0.3});
	}
}

void SpriteSheet::cropSprite(const sf::IntRect& l_rect){ 
	m_sprite.setTextureRect(l_rect);
}

void SpriteSheet::cropSprite(const sf::IntRect& l_rect, sf::Vector2f l_scale){
	sf::Vector2f nulo(1.0,1.0);
	if(l_scale != nulo){
		m_sprite.setScale(l_scale);
	}
	m_sprite.setTextureRect(l_rect);
}

bool SpriteSheet::loadSheet(const std::string& l_file){
	std::ifstream sheet;
	sheet.open(l_file);
	if(sheet.is_open()){
		releaseSheet(); // release current sheet resources.
		std::string line;
		while(std::getline(sheet,line)){
			if (line[0] == '|'){ continue; }
			std::stringstream keystream(line);
			std::string type;
			keystream >> type;
			Animation* anim	= nullptr;
			if(type == "Texture"){
				if (m_texture != ""){
					std::cerr << "! Duplicate texture entries in: " << l_file << std::endl;
					continue;
				}
				std::string texture;
				keystream >> texture;
				m_texture = texture;
				//std::cout<<"textura "<<m_texture<<std::endl;
				sf::Texture *textura = new sf::Texture();
				textura->loadFromFile(m_texture);
				m_sprite.setTexture(*textura);
			} else if(type == "Size"){
				keystream >> m_spriteSize.x >> m_spriteSize.y;
				setSpriteSize(m_spriteSize);
			} else if(type == "Scale"){
				keystream >> m_spriteScale.x >> m_spriteScale.y;
				m_sprite.setScale(m_spriteScale);
			} else if(type == "AnimationType"){
				keystream >> m_animType;
			} else if(type == "Animation"){
				std::string name;
				keystream >> name;
				if (m_animations.find(name) != m_animations.end()){
					std::cerr << "! Duplicate animation(" << name << ") in: " << l_file << std::endl;
					continue;
				}
				if(m_animType == "None"){
					anim = new Rec_Static();	

					keystream >> *anim;
					int x= 0, y= 0, w= 0, h= 0;
					for(size_t i = 0; i <= anim->getEndFrame(); i++){
						keystream >> x >> y >> w >> h;
						sf::IntRect l_crop(x,y,w,h);
						anim->setFrameRect(anim->getFrameRow(),l_crop,m_spriteScale.x);
					}
					
				} else if (m_animType == "Untidy"){
					anim = new Rec_Anim();				

					keystream >> *anim;
					int x= 0, y= 0, w= 0, h= 0;
					for(size_t i = 0; i <= anim->getEndFrame(); i++){
						keystream >> x >> y >> w >> h;
						sf::IntRect l_crop(x,y,w,h);
						anim->setFrameRect(anim->getFrameRow(),l_crop,m_spriteScale.x);
						//std::cout<<"coord "<<x<<" "<<y<<" "<<w<<" "<<h<<std::endl;
					}

				} else {
					std::cerr << "! Unknown animation type: " << m_animType << std::endl;
					continue;
				}				
				
				anim->setSpriteSheet(this);
				anim->setName(name);
				anim->Reset();
				m_animations.emplace(name,anim);
				if (m_animationCurrent){ continue; }
				m_animationCurrent = anim;
				m_animationCurrent->Play();
			}
		}
		sheet.close();
		return true;
	}
	std::cerr << "! Failed loading spritesheet: " << l_file << std::endl;
	return false;
}

bool SpriteSheet::loadTileSheet(const std::string& l_file){
	std::ifstream sheet;
	sheet.open(l_file);
	if(sheet.is_open()){
		releaseSheet(); // Release current sheet resources.
		std::string line;
		while(std::getline(sheet,line)){
			if (line[0] == '|'){ continue; }
			std::stringstream keystream(line);
			std::string type;
			keystream >> type;
			Animation* anim	= nullptr;
			if(type == "Texture"){
				if (m_texture != ""){
					std::cerr << "! Duplicate texture entries in: " << l_file << std::endl;
					continue;
				}
				std::string texture;
				keystream >> texture;
				
				m_texture = texture;
				//std::cout<<"textura "<<m_texture<<std::endl;
				sf::Texture *textura = new sf::Texture();
				textura->loadFromFile(m_texture);
				
				m_sprite.setTexture(*textura);
			} else if(type == "Size"){
				keystream >> m_spriteSize.x >> m_spriteSize.y;
				setSpriteSize(m_spriteSize);
			} else if(type == "AnimationType"){
				keystream >> m_animType;
			} else if(type.find_first_not_of( "0123456789" ) == std::string::npos){
				int tileId = atoi(type.c_str());
				//entityId.push_back(tileId);
				if (tileId < 0){ continue; }
				std::string tileName;
				keystream >> tileName;
				float tileFrictionX, tileFrictionY, tileDeadly;
				keystream >> tileFrictionX >>tileFrictionY >> tileDeadly;
				if(m_animType == "None"){
					anim = new Rec_Static();	

					int x= 0, y= 0, w= 0, h= 0;
					for(size_t i = 0; i <= anim->getEndFrame(); i++){
						keystream >>m_scale>> x >> y >> w >> h;
						sf::IntRect l_crop(x,y,w,h);
						anim->setFrameRect(anim->getFrameRow(),l_crop,m_scale);
					}
					anim->setSpriteSheet(this);
					anim->setName(tileName);
					anim->Reset();
					m_staticAnimations.emplace(tileId,anim);
					
				} else if (m_animType == "Untidy"){
					anim = new Rec_Anim();				

					keystream >> *anim;
					int x= 0, y= 0, w= 0, h= 0;
					keystream >> m_scale;
					for(size_t i = 0; i <= anim->getEndFrame(); i++){
						keystream >> x >> y >> w >> h;
						sf::IntRect l_crop(x,y,w,h);
						anim->setFrameRect(anim->getFrameRow(),l_crop,m_scale);
					}
					anim->setSpriteSheet(this);
					anim->setName(tileName);
					anim->Reset();
					m_animations.emplace(tileName,anim);					

				} else {
					std::cerr << "! Unknown animation type: " << m_animType << std::endl;
					continue;
				}			

				//std::cout<<"tile "<<tileId<<" "<<tileName<<std::endl;
				if (m_animationCurrent){ continue; }
				m_animationCurrent = anim;
				m_animationCurrent->Play();				
			}
		}
		
		sheet.close();
		return true;
	}
	std::cerr << "! Failed loading spritesheet: " << l_file << std::endl;
	return false;
}

bool SpriteSheet::setAnimation(const std::string& l_name, 
	const bool& l_play, const bool& l_loop){
	auto itr = m_animations.find(l_name);
	if (itr == m_animations.end()){ return false; }
	if (itr->second == m_animationCurrent){ return false; }
	if (m_animationCurrent){ m_animationCurrent->Stop(); }
	m_animationCurrent = itr->second;
	m_animationCurrent->setLooping(l_loop);
	if(l_play){ m_animationCurrent->Play(); }
	sf::Vector2f scale(itr->second->getScale(),itr->second->getScale());
	m_animationCurrent->cropSprite(scale);
	return true;
}

bool SpriteSheet::setAnimation(const int l_id, 
	const bool& l_play, const bool& l_loop){
	auto itr = m_staticAnimations.find(l_id);
	if (itr == m_staticAnimations.end()){ return false; }
	if (itr->second == m_animationCurrent){ return false; }
	if (m_animationCurrent){ m_animationCurrent->Stop(); }
	m_animationCurrent = itr->second;
	m_animationCurrent->setLooping(l_loop);
	if(l_play){ m_animationCurrent->Play(); }
	sf::Vector2f scale(itr->second->getScale(),itr->second->getScale());
	m_animationCurrent->cropSprite(scale);
	return true;
}

void SpriteSheet::update(const float& l_dT){
	m_animationCurrent->update(l_dT);
}
void SpriteSheet::draw(sf::RenderWindow* l_wnd){ 
	l_wnd->draw(m_sprite); 
}