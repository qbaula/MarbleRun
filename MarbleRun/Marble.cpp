#include <SDL2_gfxPrimitives.h>
#include <Box2D\Box2D.h>
#include "Marble.h"
#include "Game.h"
#include "Graphics.h"
#include "Logging.h"

Marble::Marble() {}

Marble::Marble(b2World *world, float x, float y, float r) : _r(r) {
	b2BodyDef *bd = new b2BodyDef();
	bd->position.Set(x, y);			 	 // set position
	bd->type = b2_dynamicBody;			 // dynamic type, since it moves
	this->_body = world->CreateBody(bd); // create the body

	// define the fixture i.e. the phyiscal properties
	b2FixtureDef *fd = new b2FixtureDef();
	// make fixture circular
	b2CircleShape *cs = new b2CircleShape();
	cs->m_radius = r;
	fd->shape = cs;

	// parameters that affect physics
	fd->density = 1;
	fd->friction = 0.01;
	fd->restitution = 0.3;

	// attach fixture to body
	this->_body->CreateFixture(fd);
	this->_body->SetUserData(this);
}

void Marble::draw(Graphics &g) {
	SDL_Renderer *rend = g.getRenderer();
	b2Vec2 pos = this->_body->GetPosition();

	filledCircleRGBA(rend, 
					 (Sint16) pos.x, (Sint16) pos.y, (Sint16) this->_r, 
					 0, 0, 0, 255);
}

void Marble::update(int elapsedTime) {
}