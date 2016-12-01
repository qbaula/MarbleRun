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
	bool update();

private:
	b2World *_world;
	b2Body *_body;
	uint32_t _color;
	float  _radius;

	b2Body *createBody(b2World *world, float x, float y);
	b2FixtureDef *createCircularFixture(float radius);
	void setFixturePhysics(b2FixtureDef *fd, float density, float friction, float restitution);

	bool outOfBounds(int xMax, int yMax);	
};