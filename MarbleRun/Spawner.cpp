#include <Box2D\Box2D.h>
#include "Level.h"
#include "Spawner.h"
#include "Marble.h"
#include "Logging.h"

const int SPAWN_RATE = 2000;

Spawner::Spawner() {}

Spawner::Spawner(Level *level, std::vector<b2Vec2 *> vertices) 
	: Surface(vertices),
	  _level(level) {
	setColor(0xDC, 0x14, 0x3C, 0xF0);
	initSpawner();
	calcSpawnPoint(vertices);
}

void Spawner::update() {
	_count += 1;
	if (_spawn_flag && _count % SPAWN_RATE == 0) {
		spawnMarble();
		_count = 0;
	}
}

void Spawner::startSpawning() {
	_count = 0;
	_spawn_flag = true;
	spawnMarble();
}

void Spawner::stopSpawning() {
	_spawn_flag = false;
}

void Spawner::initSpawner() {
	_count = 0;
	_spawn.x = 0;
	_spawn.y = 0;
	_spawn_flag = false;
}

void Spawner::calcSpawnPoint(std::vector<b2Vec2 *> vertices) {
	for (unsigned int i = 0; i < vertices.size(); i++) {
		_spawn.x += (uint32_t)vertices[i]->x;
		_spawn.y += (uint32_t)vertices[i]->y;
	}

	_spawn.x /= vertices.size();
	_spawn.y /= vertices.size();
}

void Spawner::spawnMarble() {
	Logging::log(L"%d %d\n", _spawn.x, _spawn.y);
	Marble *newMarble = new Marble(_level->getWorld(),
								   (float) _spawn.x, (float) _spawn.y, 28);
	_level->addMarble(newMarble);
}