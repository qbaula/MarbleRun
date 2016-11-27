#pragma once

#include <vector>

class b2World;
class Graphics;
class Marble;
class Spawner;
class Surface;

class Level {
public:
	Level();
	~Level();

	void draw(Graphics &g);
	void update(int elapsedTime);
	b2World *getWorld();

	void addMarble(Marble *m);
	void addSpawner(Spawner *s);

private:
	b2World *_world;
	std::vector<Spawner *> _spawners;
	std::vector<Marble *> _marbles;
	std::vector<Surface *> _surfaces;
};