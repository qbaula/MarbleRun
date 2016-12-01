#pragma once
#include <vector>

class Camera;
class Level;
class Graphics;
class Input;
struct b2Vec2;
union SDL_Event;

class Game {
public:
	Game();
	~Game();

private:
	Camera *_camera;
	Level *_level;
	int _last_update_ms;
	bool _running;

	void gameLoop();
	void draw(Graphics &g);
	void update(int elapsedTime);
	void quit();

	void processInput(Input &input, SDL_Event &event);
	void recordKeyEvents(Input &input, SDL_Event &event);
	void processKeyEvents(Input &input);
	void createNewLevel();
	std::vector<b2Vec2 *> scaleVertices(std::vector<b2Vec2 *> vertices);
	void createObject(std::vector<b2Vec2 *> vertices);
	int updateTime();
};
