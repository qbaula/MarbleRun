#pragma once

#include <vector>
#include <Box2D/Box2D.h>
#include "Graphics.h"
#include "Marble.h"

class Game {
public:
	Game();
	~Game();

	b2World *_world;
	b2World *getWorld();

private:
	std::vector<Marble *> _marbles;
	
	void gameLoop();
	void draw(Graphics &g);
	void update(int elapsedTime);
};
