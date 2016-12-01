#include <Box2D\Box2D.h>
#include "Graphics.h"
#include "Level.h"
#include "Logging.h"
#include "Spawner.h"
#include "Marble.h"

Level::Level() {
	// setup box2d game world
	b2Vec2 gravity(0.0f, 0.1f);
	this->_world = new b2World(gravity);
}

Level::~Level() {
	for (Marble *m : _marbles) {
		delete m;
	}

	for (Surface *s : _surfaces) {
		delete s;
	}

	for (Spawner *s : _spawners) {
		delete s;
	}
}

void Level::draw(Graphics &g) {
	for (Marble *m : _marbles) {
		m->draw(g);
	}

	for (Surface *s : _surfaces) {
		s->draw(g);
	}

	for (Spawner *s : _spawners) {
		s->draw(g);
	}
}

void Level::update(int elapsedTime) {
	_world->Step(0.07f, 100, 100);

	auto end = _marbles.end();
	for (auto iter = _marbles.begin(); iter < _marbles.end(); iter++) {
		Logging::log(L"Num marbles: #%d\n", _marbles.size());
		bool removed = (*iter)->update();
		if (removed) {
			iter = _marbles.erase(iter);
			if (iter == _marbles.end()) {
				break;
			}
		}
	}

	for (Spawner *s : _spawners) {
		s->update();
	}
}

b2World *Level::getWorld() {
	return _world;
}

void Level::addMarble(Marble *m) {
	_marbles.push_back(m);
}

void Level::addSurface(Surface * s) {
	_surfaces.push_back(s);
}

void Level::addSpawner(Spawner *s) {
	_spawners.push_back(s);
	s->startSpawning();
}