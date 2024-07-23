#include "HUD.h"
#include "SharedContext.h"
#include <cmath>

HUD::HUD(TextureMap &l_tm) {	 
	m_tm = &l_tm;
	auto itr = m_tm->vm->find("HUD");
    if(itr != m_tm->vm->end()){
	    m_heart5.setTexture(*itr->second);
    }		
	//m_introSprite.setScale(0.65,0.65);
	m_heart5.setOrigin(itr->second->getSize().x / 2.0f,
							itr->second->getSize().y / 2.0f);
	sf::FloatRect hearts = m_heart5.getLocalBounds();

	m_heart5.setPosition(hearts.width *0.3, hearts.height *.3);


    m_scoreFont.loadFromFile("fonts/CompleteinHim.ttf");
	m_scoreText.setFont(m_scoreFont);
	m_scoreText.setString(sf::String("Tiempo: "));
	m_scoreText.setCharacterSize(45);
	m_scoreText.setFillColor(sf::Color::Red);
	sf::FloatRect textRect = m_scoreText.getLocalBounds();
	m_scoreText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	/* m_scoreText.setPosition(m_introSprite.getPosition().x, 
		m_introSprite.getPosition().y + textureMgr->getResource("Intro")->getSize().y / 1.5f); */
    m_scoreText.setPosition(WIDTH - textRect.width *3, textRect.height*2.5);

	//m_scoreToPrint = std::to_string(m_puntos);
	m_scorePrint.setFont(m_scoreFont);
	m_scorePrint.setString(m_scoreToPrint);
	m_scorePrint.setCharacterSize(45);
	m_scorePrint.setStyle(sf::Text::Bold);
	m_scorePrint.setPosition(300,8.7);
	m_scorePrint.setColor(sf::Color::White);
	m_scorePrint.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}


void HUD::update(double elapsed){
	m_puntos += elapsed;
	//std::cout<<m_puntos<<" puntos"<<std::endl;
	m_scoreToPrint = getTime();



}

void HUD::draw(sf::RenderWindow &w){
    m_scoreText.setPosition(m_position);
	m_scorePrint.setPosition(m_position.x+m_scoreText.getGlobalBounds().width,
		m_position.y);
	m_scorePrint.setString(m_scoreToPrint);
    w.draw(m_scoreText);
    w.draw(m_scorePrint);
  
}

void HUD::processEvent(const sf::Event &e){}

void HUD::setPosition(float x, float y){
    m_position.x = x;
    m_position.y = y;
}

void HUD::setPlayerHP(int l_hp){
    m_hitpointsPlayer = l_hp;
}

std::string HUD::getTime(){

	
	sf::Time time = m_clock.getElapsedTime();
	int secsPass = floor(time.asSeconds());
	int minutesPass = floor(time.asSeconds())/60;

	std::stringstream sec, min, tiempo;
	
	int minToPrint = minutesPass%60;
	if(minToPrint < 10){
		min<<"0"<<minToPrint;
	}
	
	int secToPrint = secsPass%60;
		if(secToPrint < 10){
			sec<<"0"<<secToPrint%60;
		}else{
			sec<<secToPrint;
		}
	
	tiempo<<min.str()<<":"<<sec.str();

	
	return tiempo.str(); 

}

int HUD::getScore(){
    return m_puntos;
}

void HUD::load(const std::string &l_path){

	m_spriteSheet.loadTileSheet(l_path);
}

void HUD::setView(sf::View &l_view){
	m_view = l_view;
}