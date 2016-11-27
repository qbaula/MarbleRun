#pragma once

class Graphics;
class b2World;
class b2Body;

class Marble {
public:
	Marble();
	Marble(b2World *world, float x, float y, float r);
	~Marble();

	void draw(Graphics &g);

private:
	float  _r; // radius

	b2Body *_body;
	uint32_t _color;
};