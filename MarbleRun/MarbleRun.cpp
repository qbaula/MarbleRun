#include <SDL.h>
#include "Graphics.h"
#undef _main

int main(int argc, char* argv[])
{
	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	Graphics graphics;
	while (true) {}
	//Quit SDL
	SDL_Quit();
	return 0;
}