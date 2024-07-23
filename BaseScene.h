#ifndef BASESCENE_H
#define BASESCENE_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Game;
struct TextureMap;
/**
 * Escena de la que heredarán todas las del juego
 */
class BaseScene {
protected:
	sf::View *m_view;
	sf::Font m_fontComplete, m_fontBowlby;
public:
	BaseScene(){ loadFonts();};

	virtual ~BaseScene(){};

	virtual void onCreate(TextureMap &l_textureMap) = 0;
	virtual void onDestroy() = 0;
	
	virtual void update(const sf::Time& l_time, Game &g) = 0;
	
	virtual void draw(sf::RenderWindow &w) = 0;

	void setView(sf::View &l_view){*m_view = l_view;}
	
	/// notifica a la escena de un evento
	virtual void processEvent(const sf::Event &e) = 0;

	sf::View& getView(){ return *m_view; }

	sf::Font& getFontB(){ 
		m_fontBowlby.loadFromFile("fonts/BowlbyOneSC-Regular.otf");
		return m_fontBowlby;}
	
	sf::Font& getFontC(){ 
		m_fontComplete.loadFromFile("fonts/CompleteinHim.ttf");
		return m_fontComplete;}

	void loadFonts(){
		m_fontBowlby.loadFromFile("fonts/BowlbyOneSC-Regular.otf");
		m_fontComplete.loadFromFile("fonts/CompleteinHim.ttf");
	}

};

#endif
