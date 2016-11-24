#include <SDL2_gfxPrimitives.h>
#include "Marble.h"
#include "Graphics.h"
#include "Logging.h"

Marble::Marble() {}

Marble::Marble(float x, float y, float r) :
	_x(x),
	_y(y),
	_r(r)
{

}

void Marble::draw(Graphics &g) {
	Logging::log(L"draw\n");
	SDL_Renderer *r = g.getRenderer();

	circleRGBA(r, 
			   this->_x, this->_y, this->_r, 
		       0, 0, 0, 255);
}

void Marble::update(int elapsedTime) {
	Logging::log(L"update %f\n", this->_y);
	this->_y += 0.01;
}