#pragma once

#include <vector>

class b2Vec2;
class b2Body;
class b2World;
class Graphics;

class Surface {
public:
	Surface();
	Surface(std::vector<b2Vec2 *> vertices);
	~Surface();

	void draw(Graphics &g);

protected:
	// For Box2D
	b2Vec2 *_vertices;
	int32_t _numVertices;
	b2Body *_body;

	float _density;
	float _friction;
	float _restitution;

	// SDL
	int16_t *_vx;
	int16_t *_vy;
	uint8_t _r;
	uint8_t _g;
	uint8_t _b;
	uint8_t _a;

	void makeBody(b2World *world);
	virtual void setParams() = 0;
};

class StandardSurface : public Surface {
public:
	StandardSurface(b2World *world, std::vector<b2Vec2 *> vertices);
	void setParams();
};

class BouncySurface : public Surface {
public:
	BouncySurface(b2World *world, std::vector<b2Vec2 *> vertices);
	void setParams();
};
