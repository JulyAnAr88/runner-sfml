#include "MainMenuScene.h"
#include "SceneManager.h"
#include <SFML/Graphics/Color.hpp>

MainMenuScene::MainMenuScene(SceneManager* l_sceneManager)
	: BaseScene(l_sceneManager){}

MainMenuScene::~MainMenuScene(){}

void MainMenuScene::onCreate(){
	sf::Vector2u windowSize = m_sceneMgr->getContext()
		->m_wind->getRenderWindow()->getSize();
	m_font.loadFromFile("CompleteinHim.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("MENU"));
	m_text.setCharacterSize(64);
	m_text.setFillColor(sf::Color::Red);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 5.0f);

	m_buttonSize = sf::Vector2f(300.0f,32.0f);
	m_buttonPos = sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 3.0f);
	m_buttonPadding = 4; // 4px.

	std::string str[3];
	str[0] = "COMENZAR";
	str[1] = "OPCIONES";
	str[2] = "SALIR";

	for(int i = 0; i < 3; ++i){
		sf::Vector2f buttonPosition(
			m_buttonPos.x,m_buttonPos.y + 
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color::Red);

		m_rects[i].setOrigin(
			m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
		m_rects[i].setPosition(buttonPosition);

		m_labels[i].setFont(m_font);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(25);

		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(
			rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);

		m_labels[i].setPosition(buttonPosition);
	}

	EventManager* evMgr = m_sceneMgr->getContext()->m_eventManager;
	evMgr->addCallback(SceneType::MainMenu, "Mouse_Left",&MainMenuScene::MouseClick,this);
}

void MainMenuScene::onDestroy(){
	EventManager* evMgr = m_sceneMgr->getContext()->m_eventManager;
	evMgr->removeCallback(SceneType::MainMenu, "Mouse_Left");
}

void MainMenuScene::activate(){
	if (m_sceneMgr->hasScene(SceneType::Game)
		&& m_labels[0].getString() != "CONTINUAR")
	{
		m_labels[0].setString(sf::String("CONTINUAR"));
	} else {
		m_labels[0].setString(sf::String("COMENZAR"));
	}

	sf::FloatRect rect = m_labels[0].getLocalBounds();
		m_labels[0].setOrigin(rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f);
}

void MainMenuScene::MouseClick(EventDetails* l_details){
	SharedContext* context = m_sceneMgr->getContext();
	sf::Vector2i mousePos = l_details->m_mouse;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;
	for(int i = 0; i < 3; ++i){
		if(mousePos.x>=m_rects[i].getPosition().x - halfX &&
			mousePos.x<=m_rects[i].getPosition().x + halfX &&
			mousePos.y>=m_rects[i].getPosition().y - halfY &&
			mousePos.y<=m_rects[i].getPosition().y + halfY)
		{
			if(i == 0){
				m_sceneMgr->switchTo(SceneType::Game);
			} else if(i == 1){
				// Credits scene.
			} else if(i == 2){
				m_sceneMgr->getContext()->m_wind->close();
			}
		}
	}
}

void MainMenuScene::draw(){
	sf::RenderWindow* window = m_sceneMgr->
		getContext()->m_wind->getRenderWindow();
	window->clear(sf::Color(210,205,165));	
	window->draw(m_text);
	for(int i = 0; i < 3; ++i){
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
}

void MainMenuScene::update(const sf::Time& l_time){}
void MainMenuScene::deactivate(){}

