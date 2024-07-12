#include "GameScene.h" 
#include "SceneManager.h"

GameScene::GameScene(SceneManager* l_sceneManager)
	: BaseScene(l_sceneManager){}

GameScene::~GameScene(){}

void GameScene::onCreate(){
	EventManager* evMgr = m_sceneMgr->
		getContext()->m_eventManager;

	evMgr->addCallback(SceneType::Game, "Key_Escape", &GameScene::MainMenu, this);
	evMgr->addCallback(SceneType::Game, "Key_P", &GameScene::Pause, this);
	//evMgr->AddCallback(SceneType::Game, "Key_O", &GameScene::ToggleOverlay, this);

	sf::Vector2u size = m_sceneMgr->getContext()->m_wind->getWindowSize();
	m_view.setSize(size.x,size.y);
	m_view.setCenter(size.x/2,size.y/2);
	m_view.zoom(0.6f);
	m_sceneMgr->getContext()->m_wind->getRenderWindow()->setView(m_view);

	m_gameMap = new Map(m_sceneMgr->getContext(), this);
	m_gameMap->loadMap("map1.map");
}

void GameScene::onDestroy(){
	EventManager* evMgr = m_sceneMgr->
		getContext()->m_eventManager;
	evMgr->removeCallback(SceneType::Game, "Key_Escape");
	evMgr->removeCallback(SceneType::Game, "Key_P");
	evMgr->removeCallback(SceneType::Game, "Key_O");
	
	delete m_gameMap;
	m_gameMap = nullptr;
}

void GameScene::update(const sf::Time& l_time){
	SharedContext* context = m_sceneMgr->getContext();
	Entity* player = context->m_entityManager->find("Player");
	if(!player){
		std::cout << "Respawning player..." << std::endl;
		context->m_entityManager->add(EntityType::Player,"Player");
		player = context->m_entityManager->find("Player");
		player->setPosition(m_gameMap->getPlayerStart());
	} else {
		m_view.setCenter(player->getPosition());
		context->m_wind->getRenderWindow()->setView(m_view);
	}

	sf::FloatRect viewSpace = context->m_wind->getViewSpace();
	if(viewSpace.left <= 0){
		m_view.setCenter(viewSpace.width / 2,m_view.getCenter().y);
		context->m_wind->getRenderWindow()->setView(m_view);
	} else if (viewSpace.left + viewSpace.width > (m_gameMap->getMapSize().x + 1) * Sheet::Tile_Size){
		m_view.setCenter(((m_gameMap->getMapSize().x + 1) * Sheet::Tile_Size) - (viewSpace.width / 2), m_view.getCenter().y);
		context->m_wind->getRenderWindow()->setView(m_view);
	}

	m_gameMap->update(l_time.asSeconds());
	m_sceneMgr->getContext()->m_entityManager->update(l_time.asSeconds());
}

void GameScene::draw(){
	m_gameMap->draw();
	m_sceneMgr->getContext()->m_entityManager->draw();
}

void GameScene::MainMenu(EventDetails* l_details){
	m_sceneMgr->switchTo(SceneType::MainMenu);
}

void GameScene::Pause(EventDetails* l_details){
	m_sceneMgr->switchTo(SceneType::Paused);
}

void GameScene::activate(){}
void GameScene::deactivate(){}
