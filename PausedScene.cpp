#include "PausedScene.h"
#include "SceneManager.h"

PausedScene::PausedScene(SceneManager* l_sceneManager)
	: BaseScene(l_sceneManager){}

PausedScene::~PausedScene(){}

void PausedScene::onCreate(){
	setTransparent(true); // Set our transparency flag.
	m_font.loadFromFile("CompleteinHim.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("PAUSA"));
	m_text.setCharacterSize(64);
	m_text.setStyle(sf::Text::Bold);

	sf::Vector2u windowSize = m_sceneMgr->
		getContext()->m_wind->getRenderWindow()->getSize();

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 2.0f);

	m_rect.setSize(sf::Vector2f(windowSize));
	m_rect.setPosition(0,0);
	m_rect.setFillColor(sf::Color(0,0,0,150));

	EventManager* evMgr = m_sceneMgr->getContext()->m_eventManager;
	evMgr->addCallback(SceneType::Paused,"Key_P",&PausedScene::Unpause,this);
}

void PausedScene::onDestroy(){
	EventManager* evMgr = m_sceneMgr->getContext()->m_eventManager;
	evMgr->removeCallback(SceneType::Paused, "Key_P");
}

void PausedScene::draw(){
	sf::RenderWindow* wind = m_sceneMgr->getContext()->m_wind->getRenderWindow();
	wind->draw(m_rect);
	wind->draw(m_text);
}

void PausedScene::Unpause(EventDetails* l_details){
	m_sceneMgr->switchTo(SceneType::Game);
}

void PausedScene::activate(){}
void PausedScene::deactivate(){}
void PausedScene::update(const sf::Time& l_time){}