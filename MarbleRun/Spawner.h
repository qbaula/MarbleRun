#pragma once

#include <vector>
#include "Surface.h"

class Level;
class b2Vec2;

class Spawner : public Surface {
public:
	Spawner();
	Spawner(Level *level, std::vector<b2Vec2 *> vertices);
	void setParams();
	void update();
	void spawnMarble();

private:
	Level *_level;

	class spawn_point_t {
	public:
		uint32_t x;
		uint32_t y;
	};

	spawn_point_t _spawn;
	uint32_t _count;
};