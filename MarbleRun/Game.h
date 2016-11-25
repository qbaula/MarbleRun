#pragma once

#include <vector>
#include <Box2D/Box2D.h>
#include "Graphics.h"
#include "Level.h"
#include "Marble.h"

class Game {
public:
	Game();
	~Game();

private:
	Level *_level;
	void gameLoop();
	void draw(Graphics &g);
	void update(int elapsedTime);
};
