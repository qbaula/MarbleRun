#pragma once
#include <vector>
#include <Box2D\Box2D.h>
#include "Graphics.h"
#include "Marble.h"
#include "Surface.h"

class Level {
public:
	Level();
	~Level();

	b2World *getWorld();
	void draw(Graphics &g);
	void update(int elapsedTime);

private:
	b2World *_world;
	std::vector<Marble *> _marbles;
	std::vector<Surface *> _surfaces;
};