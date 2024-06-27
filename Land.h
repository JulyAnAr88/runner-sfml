#ifndef LAND_H
#define LAND_H
#include <vector>
#include "Entity.h"
#include "Environment.h"

class Land {
public:
	Land();
	std::vector<Entity *> getVEntity();
	std::vector<Environment *> getVEnviro();
	void addEntityToDelete(Entity * de);
	void addEnviroToDelete(Environment * dev);
	void update(double elapsed);
	void draw(sf::RenderTarget & target);
	void clearVEntity();
	void clearVEnviro();
private:
	std::vector<Entity *> entities;
	std::vector<Environment *> enviro;
	std::vector<Environment *> enviro_to_delete;
	std::vector<Entity *> enti_to_delete;
};

#endif

