#pragma once
#include "Graphics.h"

class Marble {
public:
	Marble();
	Marble(b2World *world, float x, float y, float r);

	void draw(Graphics &g);
	void update(int elapsedTime);

private:
	float  _r; // radius

	b2Body *_body;
	uint32_t _color;
};