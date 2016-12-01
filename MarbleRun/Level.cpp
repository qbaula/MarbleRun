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

	std::vector<b2Vec2 *> spawn_vertices;
	spawn_vertices.push_back(new b2Vec2(35, 45));
	spawn_vertices.push_back(new b2Vec2(45, 45));
	spawn_vertices.push_back(new b2Vec2(45, 55));
	spawn_vertices.push_back(new b2Vec2(35, 55));
	_spawners.push_back(new Spawner(this, spawn_vertices));
	_spawners[0]->startSpawning();
	
	std::vector<b2Vec2 *> vertices;
	vertices.push_back(new b2Vec2(10, 170));
	vertices.push_back(new b2Vec2(300, 250));
	vertices.push_back(new b2Vec2(200, 300));
	vertices.push_back(new b2Vec2(100, 275));
	_surfaces.push_back(new StandardSurface(_world, vertices));

	std::vector<b2Vec2 *> vertices2;
	vertices2.push_back(new b2Vec2(300, 300));
	vertices2.push_back(new b2Vec2(640, 300));
	vertices2.push_back(new b2Vec2(500, 370));
	_surfaces.push_back(new BouncySurface(_world, vertices2));
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
	_world->Step(0.05f, 100, 100);

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
}