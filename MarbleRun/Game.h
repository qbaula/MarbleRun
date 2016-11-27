#pragma once

class Level;
class Graphics;

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
