#include <SDL2_gfxPrimitives.h>
#include <Box2D\Box2D.h>
#include "Graphics.h"
#include "Logging.h"
#include "Surface.h"

Surface::Surface() {}

Surface::Surface(std::vector<b2Vec2 *> vertices) {
	allocateVertexVariables(vertices);
	convertVectorToVertexVariables(vertices);
}
void Surface::allocateVertexVariables(std::vector<b2Vec2 *> vertices) {
	_vertices = (b2Vec2 *)calloc(vertices.size(), sizeof(b2Vec2));
	_vx = (int16_t *)calloc(vertices.size(), sizeof(int16_t));
	_vy = (int16_t *)calloc(vertices.size(), sizeof(int16_t));
}

void Surface::convertVectorToVertexVariables(std::vector<b2Vec2 *> vertices) {
	for (unsigned int i = 0; i < vertices.size(); i++) {
		_vertices[i] = *(vertices[i]);
		_vx[i] = (int16_t)vertices[i]->x;
		_vy[i] = (int16_t)vertices[i]->y;
	}

	this->_numVertices = vertices.size();
}

Surface::~Surface() {
	delete _vertices;
	delete _vx;
	delete _vy;
}

void Surface::draw(Graphics &g) {
	SDL_Renderer *rend = g.getRenderer();

	filledPolygonRGBA(rend,
					   _vx, _vy, _numVertices, 
					   _r, _g, _b, _a);
}

void Surface::makeBody(b2World *world) {
	b2BodyDef *bd = new b2BodyDef();
	b2FixtureDef *fd = new b2FixtureDef();
	b2ChainShape *chain = new b2ChainShape();

	_body = world->CreateBody(bd);

	// define fixture as a chain loop
	chain->CreateLoop(_vertices, _numVertices);
	fd->shape = chain;

	// parameters that affect physics
	fd->density = _density;
	fd->friction = _friction;
	fd->restitution = _restitution;

	// attache fixture to body
	_body->CreateFixture(fd);
	_body->SetUserData(this);
}

void Surface::setPhysics(float density, float friction, float restitution) {
	_density = density;
	_friction = friction;
	_restitution = restitution;
}

void Surface::setColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	_r = red;
	_g = green;
	_b = blue;
	_a = alpha;
}

StandardSurface::StandardSurface(b2World *world, std::vector<b2Vec2 *> vertices)
	: Surface(vertices) {
	setPhysics(1.f, 0.001f, 0.4f);
	setColor(0x00, 0x00, 0xCD, 0xFF);
	makeBody(world);
}

BouncySurface::BouncySurface(b2World *world, std::vector<b2Vec2 *> vertices)
	: Surface(vertices) {
	setPhysics(1.f, 0.01f, 0.9f);
	setColor(0x00, 0x60, 0x00, 0xF0);
	makeBody(world);
}