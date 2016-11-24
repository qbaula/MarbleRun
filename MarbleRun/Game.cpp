#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <Box2D\Box2D.h>

#include "Game.h"
#include "Graphics.h"
#include "Input.h"
#include "Logging.h"
#include "Marble.h"

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

b2World *Game::getWorld() {
	return this->_world;
}

void Game::gameLoop() {
	Graphics graphics; // creates SDL window and renderer
	SDL_Event event;   // stores information about key events
	Input input;	   // simplifies key event logic

	// setup box2d game world
	b2Vec2 gravity(0.0f, 0.1f);
	this->_world = new b2World(gravity);

	this->_marbles.push_back(new Marble(this->_world, 50, 50, 28));
	this->_marbles.push_back(new Marble(this->_world, 200,50, 28));

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
				Logging::log(L"Exiting...\n");
				return;
			}
		}

		if (input.wasKeyPressed(SDL_SCANCODE_SPACE)) {
			Logging::log(L"Scanning image\n");
		}

		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
			Logging::log(L"Exiting...\n");
			return;
		}

		
		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &g) {
	g.clear();

	for (Marble *m : this->_marbles) {
		m->draw(g);
	}

	pixelRGBA(g.getRenderer(),
			  0, 0,
			  255, 255, 255, 255);
	g.flip();
}

void Game::update(int elapsedTime) {
	Logging::log(L"elapsed %d\n", elapsedTime);
	this->_world->Step(0.02f, 100, 100);
	/*
	for (Marble *m : this->_marbles) {
		m->update(elapsedTime);
	}
	*/
}
