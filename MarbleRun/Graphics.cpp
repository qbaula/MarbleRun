#include <SDL.h>
#include "Graphics.h"

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(640, 480, NULL, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "MarbleRun");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
}