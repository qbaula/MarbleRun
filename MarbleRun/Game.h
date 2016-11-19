#pragma once

#include "Graphics.h"

class Game {
public:
	Game();
	~Game();

private:
	void gameLoop();
	void draw(Graphics &g);
	void update(int elapsedTime);
};
