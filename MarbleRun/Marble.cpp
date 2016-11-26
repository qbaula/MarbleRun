#include <SDL2_gfxPrimitives.h>
#include <Box2D\Box2D.h>
#include "Marble.h"
#include "Game.h"
#include "Graphics.h"
#include "Logging.h"

Marble::Marble() {}

Marble::Marble(b2World *world, float x, float y, float r) : _r(r) {
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
					 (Sint16) pos.x, (Sint16) pos.y, (Sint16) this->_r, 
					 this->_color);
}
