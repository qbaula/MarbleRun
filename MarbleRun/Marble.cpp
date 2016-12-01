#include <SDL2_gfxPrimitives.h>
#include <Box2D\Box2D.h>
#include "Marble.h"
#include "Game.h"
#include "Graphics.h"
#include "Logging.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

Marble::Marble() {}

Marble::Marble(b2World *world, float x, float y, float r) : _world(world), _radius(r), _color(0xF08080FF) {
	b2FixtureDef *fixture = createCircularFixture(r);
	setFixturePhysics(fixture, 1, 0.01f, 0.3f);
	_body = createBody(world, x, y);
	_body->CreateFixture(fixture);
	_body->SetUserData(this);
}

Marble::~Marble() {
	
}

void Marble::draw(Graphics &g) {
	SDL_Renderer *rend = g.getRenderer();
	b2Vec2 pos = _body->GetPosition();
	filledCircleColor(rend, 
					 (Sint16) pos.x, (Sint16) pos.y, (Sint16) _radius, 
					 _color);
}

bool Marble::update() {
	Logging::log(L"Marble::update()\n");
	bool out = outOfBounds(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (out) {
		_world->DestroyBody(_body);
	}

	return out;
}

b2Body * Marble::createBody(b2World * world, float x, float y) {
	b2BodyDef *bd = new b2BodyDef();	
	bd->position.Set(x, y);
	bd->type = b2_dynamicBody;
	bd->allowSleep = true;
	bd->awake = true;
	return world->CreateBody(bd);
}

b2FixtureDef * Marble::createCircularFixture(float radius) {
	b2FixtureDef *fd = new b2FixtureDef();
	b2CircleShape *circle = new b2CircleShape();
	circle->m_radius = radius;
	fd->shape = circle;

	return fd;
}

void Marble::setFixturePhysics(b2FixtureDef * fd, float density, float friction, float restitution) {
	fd->density = density;
	fd->friction = friction;
	fd->restitution = restitution;
}

bool Marble::outOfBounds(int xMax, int yMax) {
	b2Vec2 pos = _body->GetPosition();
	if ((pos.x - _radius > xMax) || (pos.y - _radius > yMax)) {
		return true;
	}
	
	return false;
}
