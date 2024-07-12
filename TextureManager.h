#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

//template <typename T>
class TextureManager
{
public:
	TextureManager() { loadPaths("textures.cfg"); };
	~TextureManager() { purgeResources(); }

	void loadPaths(const std::string &l_pathFile)
	{
		std::ifstream paths;
		paths.open(l_pathFile);
		if (paths.is_open())
		{
			std::string line;
			while (std::getline(paths, line))
			{
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

	sf::Texture *load(const std::string &l_path)
	{
		sf::Texture *texture = new sf::Texture();
		if (!texture->loadFromFile(l_path))
		{
			delete texture;
			texture = nullptr;
			std::cerr << "! Failed to load texture: " << l_path << std::endl;
		}
		return texture;
	}

	std::string getPath(const std::string &l_id)
	{
		auto path = m_paths.find(l_id);
		return (path != m_paths.end() ? path->second : "");
	}

	sf::Texture *getResource(const std::string &l_id)
	{
		auto res = find(l_id);
		return (res ? res->first : nullptr);
	}

	bool requireResource(const std::string &l_id)
	{
		auto res = find(l_id);
		if (res)
		{
			++res->second;
			return true;
		}
		auto path = m_paths.find(l_id);
		if (path == m_paths.end())
		{
			return false;
		}
		sf::Texture *resource = load(path->second);
		if (!resource)
		{
			return false;
		}
		m_resources.emplace(l_id, std::make_pair(resource, 1));
		return true;
	}

	bool releaseResource(const std::string &l_id)
	{
		auto res = find(l_id);
		if (!res)
		{
			return false;
		}
		--res->second;
		if (!res->second)
		{
			unload(l_id);
		}
		return true;
	}

	void purgeResources()
	{
		std::cout << "Purging all resources:" << std::endl;
		while (m_resources.begin() != m_resources.end())
		{
			std::cout << "Removing: "
					  << m_resources.begin()->first << std::endl;
			delete m_resources.begin()->second.first;
			m_resources.erase(m_resources.begin());
		}
		std::cout << "Purging finished." << std::endl;
	}

private:
	std::map<std::string, std::pair<sf::Texture *, unsigned int>> m_resources;
	std::map<std::string, std::string> m_paths;

	std::pair<sf::Texture *, unsigned int> *find(const std::string &l_id)
	{
		auto itr = m_resources.find(l_id);
		return (itr != m_resources.end() ? &itr->second : nullptr);
	}

	bool unload(const std::string &l_id)
	{
		auto itr = m_resources.find(l_id);
		if (itr == m_resources.end())
		{
			return false;
		}
		delete itr->second.first;
		m_resources.erase(itr);
		return true;
	}
};

#endif
