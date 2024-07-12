#include "IntroScene.h"
#include "SceneManager.h"

IntroScene::IntroScene(SceneManager* l_sceneManager)
	: BaseScene(l_sceneManager){}

IntroScene::~IntroScene(){}

void IntroScene::onCreate(){
	sf::Vector2u windowSize = m_sceneMgr->getContext()
		->m_wind->getRenderWindow()->getSize();
	TextureManager* textureMgr = m_sceneMgr->getContext()->m_textureManager;
	textureMgr->requireResource("Intro");
	m_introSprite.setTexture(*textureMgr->getResource("Intro"));
	m_introSprite.setScale(0.45,0.45);
	m_introSprite.setOrigin(textureMgr->getResource("Intro")->getSize().x / 2.0f,
							textureMgr->getResource("Intro")->getSize().y / 2.0f);

	m_introSprite.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_fontTitle.loadFromFile("BowlbyOneSC-Regular.otf");
	m_textTitle.setFont(m_fontTitle);
	m_textTitle.setString(sf::String("CARRERA AL BACHI"));
	m_textTitle.setCharacterSize(55);
	m_textTitle.setFillColor(sf::Color::Red);
	sf::FloatRect textRectTitle = m_textTitle.getLocalBounds();
	m_textTitle.setOrigin(textRectTitle.left + textRectTitle.width / 2.0f,
		textRectTitle.top + textRectTitle.height / 2.0f);
	/* m_textTitle.setPosition(m_introSprite.getPosition().x, 
		m_introSprite.getPosition().y + textureMgr->getResource("Intro")->getSize().y ); */
	m_textTitle.setPosition(windowSize.x / 2.0f, windowSize.y / 4.0f);
	m_font.loadFromFile("CompleteinHim.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("Presiona ESPACIO para continuar"));
	m_text.setCharacterSize(35);
	m_text.setFillColor(sf::Color::Red);
	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	/* m_text.setPosition(m_introSprite.getPosition().x, 
		m_introSprite.getPosition().y + textureMgr->getResource("Intro")->getSize().y / 1.5f); */
    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 1.5f);
	EventManager* evMgr = m_sceneMgr->getContext()->m_eventManager;
	evMgr->addCallback(SceneType::Intro, "Intro_Continue",&IntroScene::Continue,this);
}

void IntroScene::onDestroy(){
	TextureManager* textureMgr = m_sceneMgr->getContext()->m_textureManager;
	textureMgr->releaseResource("Intro");

	EventManager* evMgr = m_sceneMgr->getContext()->m_eventManager;
	evMgr->removeCallback(SceneType::Intro,"Intro_Continue");
}

void IntroScene::draw(){
	sf::RenderWindow* window = m_sceneMgr->getContext()->m_wind->getRenderWindow();
	window->clear(sf::Color(210,205,165));	
	window->draw(m_introSprite);
	window->draw(m_textTitle);
	window->draw(m_text);
}

void IntroScene::Continue(EventDetails* l_details){
	m_sceneMgr->switchTo(SceneType::MainMenu);
	m_sceneMgr->remove(SceneType::Intro);
}

void IntroScene::update(const sf::Time& l_time){}
void IntroScene::activate(){}
void IntroScene::deactivate(){}
