#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

class TextureManager{
public:
	TextureManager();
	~TextureManager();

	void loadPaths(const std::string &l_pathFile);
	sf::Texture *load(const std::string &l_path);
	std::string getPath(const std::string &l_id);
	sf::Texture *getResource(const std::string &l_id);
	bool requireResource(const std::string &l_id);
	bool releaseResource(const std::string &l_id);
	void purgeResources();

private:
	std::map<std::string, std::pair<sf::Texture *, unsigned int>> m_resources;
	std::map<std::string, std::string> m_paths;

	std::pair<sf::Texture *, unsigned int> *find(const std::string &l_id);

	bool unload(const std::string &l_id);
};

#endif
