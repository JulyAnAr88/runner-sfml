#include "TextureManager.h"

TextureManager::TextureManager() { loadPaths("textures.cfg"); }

TextureManager::~TextureManager() { purgeResources(); }

void TextureManager::loadPaths(const std::string &l_pathFile){
	std::ifstream paths;
	paths.open(l_pathFile);
	if (paths.is_open()){
		std::string line;
		while (std::getline(paths, line)){
			std::stringstream keystream(line);
			std::string pathName;
			std::string path;
			keystream >> pathName;
			keystream >> path;
			m_paths.emplace(pathName, path);
		}
		paths.close();
		return;
	}
	std::cerr << "! Failed loading the path file: " << l_pathFile << std::endl;
}

sf::Texture *TextureManager::load(const std::string &l_path){
	sf::Texture *texture = new sf::Texture();
	if (!texture->loadFromFile(l_path)){
		delete texture;
		texture = nullptr;
		std::cerr << "! Failed to load texture: " << l_path << std::endl;
	}
	return texture;
}

std::string TextureManager::getPath(const std::string &l_id){
	auto path = m_paths.find(l_id);
	return (path != m_paths.end() ? path->second : "");
}

sf::Texture *TextureManager::getResource(const std::string &l_id){
	auto res = find(l_id);
	return (res ? res->first : nullptr);
}

bool TextureManager::requireResource(const std::string &l_id){
	auto res = find(l_id);
	if (res){
		++res->second;
		return true;
	}
	auto path = m_paths.find(l_id);
	if (path == m_paths.end()){
		return false;
	}
	sf::Texture *resource = load(path->second);
	if (!resource){
		return false;
	}
	m_resources.emplace(l_id, std::make_pair(resource, 1));
	return true;
}

bool TextureManager::releaseResource(const std::string &l_id){
	auto res = find(l_id);
	if (!res){
		return false;
	}
	--res->second;
	if (!res->second){
		unload(l_id);
	}
	return true;
}

void TextureManager::purgeResources(){
	std::cout << "Purging all resources:" << std::endl;
	while (m_resources.begin() != m_resources.end()){
		std::cout << "Removing: "
					<< m_resources.begin()->first << std::endl;
		delete m_resources.begin()->second.first;
		m_resources.erase(m_resources.begin());
	}
	std::cout << "Purging finished." << std::endl;
}

std::pair<sf::Texture *, unsigned int> *TextureManager::find(const std::string &l_id){
	auto itr = m_resources.find(l_id);
	return (itr != m_resources.end() ? &itr->second : nullptr);
}

bool TextureManager::unload(const std::string &l_id){
	auto itr = m_resources.find(l_id);
	if (itr == m_resources.end()){
		return false;
	}
	delete itr->second.first;
	m_resources.erase(itr);
	return true;
}