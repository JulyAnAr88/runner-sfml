#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(SharedContext* l_shared)
	: m_shared(l_shared)
{
	registerScene<IntroScene>(SceneType::Intro);
	registerScene<MainMenuScene>(SceneType::MainMenu);
	registerScene<GameScene>(SceneType::Game);
	registerScene<PausedScene>(SceneType::Paused);
	//registerScene<GameOverScene>(SceneType::GameOver);
}

SceneManager::~SceneManager(){
	for (auto &itr : m_scenes){
		itr.second->onDestroy();
		delete itr.second;
	}
}

void SceneManager::update(const sf::Time& l_time){
	
	if (m_scenes.empty()){ return; }
	if (m_scenes.back().second->isTranscendent() && m_scenes.size() > 1){
		//std::cout<<"en el update de SceneManager "<<std::endl;
		auto itr = m_scenes.end();
		while (itr != m_scenes.begin()){
			if (itr != m_scenes.end()){
				if (!itr->second->isTranscendent()){
					break;
				}
			}
			--itr;
		}
		for (; itr != m_scenes.end(); ++itr){
			itr->second->update(l_time);
		}
	} else {
		m_scenes.back().second->update(l_time);
	}
}

void SceneManager::draw(){
	if (m_scenes.empty()){ return; }
	if(m_scenes.back().second->isTransparent() && m_scenes.size() > 1){
		auto itr = m_scenes.end();
		while(itr != m_scenes.begin()){
			if(itr != m_scenes.end()){
				if(!itr->second->isTransparent()){
					break;
				}
			}
			--itr;
		}
		for(; itr != m_scenes.end(); ++itr){
			m_shared->m_wind->getRenderWindow()->setView(itr->second->getView());
			itr->second->draw();
		}
	} else {
		m_scenes.back().second->draw();
	}
}

SharedContext* SceneManager::getContext(){ return m_shared; }

bool SceneManager::hasScene(const SceneType& l_type){
	for (auto itr = m_scenes.begin();
		itr != m_scenes.end(); ++itr)
	{
		if (itr->first == l_type){
			auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), l_type);
			if (removed == m_toRemove.end()){ return true; }
			return false;
		}
	}
	return false;
}

void SceneManager::processRequests(){
	while (m_toRemove.begin() != m_toRemove.end()){
		removeScene(*m_toRemove.begin());
		m_toRemove.erase(m_toRemove.begin());
	}
}

void SceneManager::switchTo(const SceneType& l_type){
	m_shared->m_eventManager->setCurrentScene(l_type);
	for (auto itr = m_scenes.begin(); itr != m_scenes.end(); ++itr){
		if (itr->first == l_type){
			m_scenes.back().second->deactivate();
			SceneType tmp_type = itr->first;
			BaseScene* tmp_scene = itr->second;
			m_scenes.erase(itr);
			m_scenes.emplace_back(tmp_type, tmp_scene);
			tmp_scene->activate();
			m_shared->m_wind->getRenderWindow()->setView(tmp_scene->getView());
			return;
		}
	}

	// Scene with l_type wasn't found.
	if (!m_scenes.empty()){ m_scenes.back().second->deactivate(); }
	createScene(l_type);
	std::cout<<"en switchto Scene "<<m_scenes.size()<<std::endl;
	m_scenes.back().second->activate();
	m_shared->m_wind->getRenderWindow()->setView(m_scenes.back().second->getView());
}

void SceneManager::remove(const SceneType& l_type){
	m_toRemove.push_back(l_type);
}

// Private methods.

void SceneManager::createScene(const SceneType& l_type){
	auto newScene = m_sceneFactory.find(l_type);
	if (newScene == m_sceneFactory.end()){ return; }
	BaseScene* scene = newScene->second();
	scene->m_view = m_shared->m_wind->getRenderWindow()->getDefaultView();
	m_scenes.emplace_back(l_type, scene);
	scene->onCreate();
}

void SceneManager::removeScene(const SceneType& l_type){
	for (auto itr = m_scenes.begin();
		itr != m_scenes.end(); ++itr)
	{
		if (itr->first == l_type){
			itr->second->onDestroy();
			delete itr->second;
			m_scenes.erase(itr);
			return;
		}
	}
}

