#include <SDL2_gfxPrimitives.h>
#include "Logging.h"
#include "Surface.h"

Surface::Surface() {}

Surface::Surface(std::vector<b2Vec2 *> vertices) {
	this->_vertices = (b2Vec2 *)calloc(vertices.size(), sizeof(b2Vec2));
	this->_vx = (int16_t *)calloc(vertices.size(), sizeof(int16_t));
	this->_vy = (int16_t *)calloc(vertices.size(), sizeof(int16_t));
	for (unsigned int i = 0; i < vertices.size(); i++) {
		this->_vertices[i] = *(vertices[i]);
		this->_vx[i] = (int16_t)(*(vertices[i])).x;
		this->_vy[i] = (int16_t)(*(vertices[i])).y;
	}
	this->_numVertices = vertices.size();
}

StandardSurface::StandardSurface(b2World *world, std::vector<b2Vec2 *> vertices)
	: Surface(vertices) {
	this->setParams();
	this->makeBody(world);
}

BouncySurface::BouncySurface(b2World *world, std::vector<b2Vec2 *> vertices)
	: Surface(vertices) {
	this->setParams();
	this->makeBody(world);
}

Surface::~Surface() {
	delete this->_vertices;
	delete this->_vx;
	delete this->_vy;
}

void Surface::draw(Graphics &g) {
	SDL_Renderer *rend = g.getRenderer();

	filledPolygonRGBA(rend,
					   this->_vx, this->_vy, this->_numVertices, 
					   this->_r, this->_g, this->_b, this->_a);
}

void Surface::makeBody(b2World *world) {
	b2BodyDef *bd = new b2BodyDef();
	b2FixtureDef *fd = new b2FixtureDef();
	b2ChainShape *chain = new b2ChainShape();

	this->_body = world->CreateBody(bd);

	// define fixture as a chain loop
	chain->CreateLoop(this->_vertices, this->_numVertices);
	fd->shape = chain;

	// parameters that affect physics
	fd->density = this->_density;
	fd->friction = this->_friction;
	fd->restitution = this->_restitution;

	// attache fixture to body
	this->_body->CreateFixture(fd);
	this->_body->SetUserData(this);
}

void StandardSurface::setParams() {
	Logging::log(L"Surface\n");
	this->_density = 1;
	this->_friction = 0.01;
	this->_restitution = 0.2;
	this->_r = 0xA0;
	this->_g = 0xA0;
	this->_b = 0xA0;
	this->_a = 0xFF;
}

void BouncySurface::setParams() {
	Logging::log(L"Bouncy Surface\n");
	this->_density = 1;
	this->_friction = 0.01;
	this->_restitution = 0.9;
	this->_r = 0x70;
	this->_g = 0x80;
	this->_b = 0x90;
	this->_a = 0xF0;
}