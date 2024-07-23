#include "IntroScene.h"
#include "Game.h"
#include "GameOverScene.h"
#include "ScoreScene.h"

IntroScene::IntroScene(sf::Vector2f l_centerView)
	: BaseScene(){
		m_view->setCenter(l_centerView);
	}

IntroScene::IntroScene()
	: BaseScene(){	}

IntroScene::~IntroScene(){}

void IntroScene::onCreate(TextureMap &l_textureMap){
	this->m_view = new sf::View(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
    auto itr = l_textureMap.vm->find("Intro");
    if(itr != l_textureMap.vm->end()){
	    m_introSprite.setTexture(*itr->second);
    }		
	m_introSprite.setScale(0.65,0.65);
	m_introSprite.setOrigin(itr->second->getSize().x / 2.0f,
							itr->second->getSize().y / 2.0f);

	m_introSprite.setPosition(WIDTH / 2.0f, HEIGHT / 2.0f);

	//m_fontTitle.loadFromFile("fonts/BowlbyOneSC-Regular.otf");
	m_textTitle.setFont(getFontB());
	m_textTitle.setString(sf::String("CARRERA AL BACHI"));
	m_textTitle.setCharacterSize(55);
	m_textTitle.setFillColor(sf::Color::Red);
	sf::FloatRect textRectTitle = m_textTitle.getLocalBounds();
	m_textTitle.setOrigin(textRectTitle.left + textRectTitle.width / 2.0f,
		textRectTitle.top + textRectTitle.height / 2.0f);
	/* m_textTitle.setPosition(m_introSprite.getPosition().x, 
		m_introSprite.getPosition().y + textureMgr->getResource("Intro")->getSize().y ); */
	m_textTitle.setPosition(WIDTH / 2.0f, HEIGHT / 4.0f);
	//m_font.loadFromFile("fonts/CompleteinHim.ttf");
	m_text.setFont(getFontC());
	m_text.setString(sf::String("Presiona ESPACIO para continuar"));
	m_text.setCharacterSize(35);
	m_text.setFillColor(sf::Color::Red);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	/* m_text.setPosition(m_introSprite.getPosition().x, 
		m_introSprite.getPosition().y + textureMgr->getResource("Intro")->getSize().y / 1.5f); */
    m_text.setPosition(WIDTH / 2.0f, HEIGHT / 1.5f);	
}

void IntroScene::onDestroy(){
}

void IntroScene::draw(sf::RenderWindow &window){
	window.clear(sf::Color(210,205,165));	
	window.draw(m_introSprite);
	window.draw(m_textTitle);
	window.draw(m_text);
}

void IntroScene::processEvent(const sf::Event &e){
}

void IntroScene::update(const sf::Time& l_time, Game &g){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
       g.switchScene(new GameScene());	    
       //g.switchScene(new ScoreScene());	    
		/* int i = 45;
		std::string s = "hola";
        g.switchScene(new GameOverScene(i,s, this->m_view->getCenter()));	 
		go->onCreate(*m_tm);
		GameOverScene *go = new GameOverScene(i,s, m_view);
		*/    
    }

}
void IntroScene::activate(){}
void IntroScene::deactivate(){}