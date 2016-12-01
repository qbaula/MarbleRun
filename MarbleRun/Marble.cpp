#include <SDL2_gfxPrimitives.h>
#include <Box2D\Box2D.h>
#include "Marble.h"
#include "Game.h"
#include "Graphics.h"
#include "Logging.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

Marble::Marble() {}

Marble::Marble(b2World *world, float x, float y, float r) : _world(world), _radius(r) {
	b2BodyDef *bd = new b2BodyDef();
	b2FixtureDef *fd = new b2FixtureDef();
	b2CircleShape *circle = new b2CircleShape();

	// define body properties
	bd->position.Set(x, y);		// set position
	bd->type = b2_dynamicBody;	// dynamic type, since it moves
	bd->allowSleep = true;
	bd->awake = true;
	this->_body = world->CreateBody(bd); // create the body
	
	// define fixture as circular
	circle->m_radius = r;
	fd->shape = circle;

	// parameters that affect physics
	fd->density = 1;
	fd->friction = 0.01f;
	fd->restitution = 0.3f;

	// attach fixture to body
	this->_body->CreateFixture(fd);
	this->_body->SetUserData(this);

	this->_color = 0xF08080FF;
}

Marble::~Marble() {
	
}

void Marble::draw(Graphics &g) {
	SDL_Renderer *rend = g.getRenderer();
	b2Vec2 pos = this->_body->GetPosition();

	filledCircleColor(rend, 
					 (Sint16) pos.x, (Sint16) pos.y, (Sint16) this->_radius, 
					 this->_color);
}

bool Marble::update() {
	Logging::log(L"Marble::update()\n");
	bool out = outOfBounds(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (out) {
		_world->DestroyBody(_body);
	}

	return out;
}

bool Marble::outOfBounds(int xMax, int yMax) {
	b2Vec2 pos = _body->GetPosition();
	if ((pos.x - _radius > xMax) || (pos.y - _radius > yMax)) {
		return true;
	}
	
	return false;
}
