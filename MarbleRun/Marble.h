#pragma once
#include "Graphics.h"

class Marble {
public:
	Marble();
	Marble(float x, float y, float r);

	void draw(Graphics &g);
	void update(int elapsedTime);

private:
	float _x, _y, _r; // move x,y into Box2D Body
};