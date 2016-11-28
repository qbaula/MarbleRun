#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <Box2D\Box2D.h>

#include "Game.h"
#include "Graphics.h"
#include "Input.h"
#include "Level.h"
#include "Logging.h"
#include "Marble.h"

namespace {
	const int FPS = 60;
	const int MAX_FRAME_TIME = 1000 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_running = true;
	_level = nullptr;
	gameLoop();
}

Game::~Game() {
	SDL_Quit();
}

void Game::gameLoop() {
	Graphics graphics; // creates SDL window and renderer
	SDL_Event event;   // stores information about key events
	Input input;	   // simplifies key event logic

	_last_update_ms = SDL_GetTicks();
	while (_running) {
		input.beginNewFrame();
		recordKeyEvents(input, event);
		processKeyEvents(input);

		int elapsed = updateTime();
		update(std::min(elapsed, MAX_FRAME_TIME));
		draw(graphics);
	}
}

void Game::draw(Graphics &g) {
	g.clear();
	
	if (_level != nullptr) {
		_level->draw(g);
	}

	pixelRGBA(g.getRenderer(),
			  0, 0,
			  255, 255, 255, 255);
	g.flip();
}

void Game::update(int elapsedTime) {
	// Logging::log(L"elapsed %d\n", elapsedTime);
	if (_level != nullptr) {
		_level->update(elapsedTime);
	}
}

void Game::quit() {
	_running = false;
}

void Game::recordKeyEvents(Input &input, SDL_Event &event) {
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
		}
	}
}

void Game::processKeyEvents(Input &input) {
	if (input.wasKeyPressed(SDL_SCANCODE_SPACE)) {
		createNewLevel();
	}

	if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
		quit();
	}
}

void Game::createNewLevel() {
	Logging::log(L"Creating new level\n");
	if (this->_level != nullptr) {
		delete this->_level;
	}
	this->_level = new Level();
}

int Game::updateTime() {
	int current = SDL_GetTicks();
	int elapsed = current - _last_update_ms;
	_last_update_ms = current;

	return elapsed;
}
