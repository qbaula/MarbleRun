#pragma once

#include <vector>
#include "Surface.h"

class Level;
struct b2Vec2;

class Spawner : public Surface {
public:
	Spawner();
	Spawner(Level *level, std::vector<b2Vec2 *> vertices);
	void update();
	void startSpawning();
	void stopSpawning();

private:
	class spawn_point_t {
	public:
		uint32_t x;
		uint32_t y;
	};

	Level *_level;
	uint32_t _count;
	spawn_point_t _spawn;
	bool _spawn_flag;

	void initSpawner();
	void calcSpawnPoint(std::vector<b2Vec2 *> vertices);
	void spawnMarble();
};