#pragma once

#include <vector>

struct b2Vec2;
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

	void allocateVertexVariables(std::vector<b2Vec2 *> vertices);
	void convertVectorToVertexVariables(std::vector<b2Vec2 *> vertices);
	void makeBody(b2World *world);
	void setPhysics(float density, float friction, float restitution);
	void setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
};

class StandardSurface : public Surface {
public:
	StandardSurface(b2World *world, std::vector<b2Vec2 *> vertices);
};

class BouncySurface : public Surface {
public:
	BouncySurface(b2World *world, std::vector<b2Vec2 *> vertices);
};
