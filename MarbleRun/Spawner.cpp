#include <Box2D\Box2D.h>
#include "Level.h"
#include "Spawner.h"
#include "Marble.h"
#include "Logging.h"

Spawner::Spawner() {

}

Spawner::Spawner(Level *level, std::vector<b2Vec2 *> vertices) 
	: Surface(vertices),
	  _level(level) {
	this->setParams();
	this->_count = 0;

	for (unsigned int i = 0; i < vertices.size(); i++) {
		this->_spawn.x += vertices[i]->x;
		this->_spawn.y += vertices[i]->y;
	}

	this->_spawn.x /= vertices.size();
	this->_spawn.y /= vertices.size();
}

void Spawner::update() {
	_count += 1;
	if (_count % 5000 == 0) {
		spawnMarble();
		_count = 0;
	}
}

void Spawner::spawnMarble() {
	Marble *newMarble = new Marble(this->_level->getWorld(),
								   50, 50, 28);
	this->_level->addMarble(newMarble);

}

void Spawner::setParams() {
	this->_r = 0xDC;
	this->_g = 0x14;
	this->_b = 0x3C;
	this->_a = 0xF0;
}