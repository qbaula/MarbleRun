#include "Level.h"

Level::Level() {
	// setup box2d game world
	b2Vec2 gravity(0.0f, 0.1f);
	this->_world = new b2World(gravity);

	this->_marbles.push_back(new Marble(this->_world, 50, 50, 28));
	this->_marbles.push_back(new Marble(this->_world, 200, 50, 28));

	std::vector<b2Vec2 *> vertices;
	vertices.push_back(new b2Vec2(10, 170));
	vertices.push_back(new b2Vec2(300, 250));
	vertices.push_back(new b2Vec2(200, 300));
	vertices.push_back(new b2Vec2(100, 275));

	this->_surfaces.push_back(new StandardSurface(this->_world, vertices));

	std::vector<b2Vec2 *> vertices2;
	vertices2.push_back(new b2Vec2(300, 300));
	vertices2.push_back(new b2Vec2(600, 300));
	vertices2.push_back(new b2Vec2(500, 370));

	this->_surfaces.push_back(new BouncySurface(this->_world, vertices2));
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