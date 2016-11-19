#include <SDL.h>
#include <Windows.h>
#include "Game.h"
#include "Graphics.h"
#include "Input.h"
#include "Logging.h"

namespace {
	const int FPS = 60;
	const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game() {
	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() {
	//Quit SDL
	SDL_Quit();
}

void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;
	Logging log;

	int LAST_UPDATE_TIME = SDL_GetTicks();
	while (true) {
		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
				break;

			case SDL_KEYUP:
				input.keyUpEvent(event);
				break;

			case SDL_QUIT:
				log.log(L"Exiting...\n");
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_SPACE)) {
			log.log(L"Scanning image\n");
		}

		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
			log.log(L"Exiting...\n");
			return;
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		this->update(min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

	}
}

void Game::draw(Graphics &g) {

}

void Game::update(int elapsedTime) {

}