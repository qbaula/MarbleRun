#include <SDL.h>
#include "Graphics.h"

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, NULL, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Marble Run");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
}

void Graphics::flip() {
	SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
	return this->_renderer;
}