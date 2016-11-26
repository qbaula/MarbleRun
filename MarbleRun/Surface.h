#pragma once
#include <vector>
#include <Box2D\Box2D.h>
#include "Graphics.h"

class Surface {
public:
	Surface();
	Surface(std::vector<b2Vec2 *> vertices);
	~Surface();

	void draw(Graphics &g);
	virtual void setParams() = 0;

protected:
	// For Box2D
	b2Vec2 *_vertices;
	int32_t _numVertices;
	b2Body *_body;
	uint32_t _color;

	float _density;
	float _friction;
	float _restitution;

	// SDL
	int16_t *_vx;
	int16_t *_vy;

	void makeBody(b2World *world);
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
