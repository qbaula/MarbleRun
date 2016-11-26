#include "Level.h"

Level::Level() {
	// setup box2d game world
	b2Vec2 gravity(0.0f, 0.1f);
	this->_world = new b2World(gravity);

	this->_marbles.push_back(new Marble(this->_world, 50, 50, 28));
	this->_marbles.push_back(new Marble(this->_world, 200, 50, 28));

	std::vector<b2Vec2 *> vertices;
	vertices.push_back(new b2Vec2(0, 200));
	vertices.push_back(new b2Vec2(300, 250));
	vertices.push_back(new b2Vec2(200, 300));

	this->_surfaces.push_back(new BouncySurface(this->_world, vertices));
}

Level::~Level() {
	for (Marble *m : this->_marbles) {
		delete m;
	}

	for (Surface *s : this->_surfaces) {
		delete s;
	}
}

void Level::draw(Graphics &g) {
	for (Marble *m : this->_marbles) {
		m->draw(g);
	}

	for (Surface *s : this->_surfaces) {
		s->draw(g);
	}
}

void Level::update(int elapsedTime) {
	this->_world->Step(0.02f, 100, 100);
}

b2World *Level::getWorld() {
	return this->_world;
}