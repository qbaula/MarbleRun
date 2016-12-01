#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <Box2D\Box2D.h>

#include "Camera.h"
#include "Color.h"
#include "Game.h"
#include "Graphics.h"
#include "Input.h"
#include "Level.h"
#include "Logging.h"
#include "Marble.h"
#include "Surface.h"
#include "Spawner.h"

namespace {
	const int FPS = 60;
	const int MAX_FRAME_TIME = 1000 / FPS;
}

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

Game::Game() {
	_running = true;
	_level = nullptr;
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

Game::~Game() {
	quit();
	SDL_Quit();
}

void Game::gameLoop() {
	Camera camera;
	Graphics graphics; // creates SDL window and renderer
	SDL_Event event;   // stores information about key events
	Input input;	   // simplifies key event logic
	_camera = &camera;

	if (!camera.isConnected()) {
		Logging::log(L"No device connected\n");
		return;
	}

	_last_update_ms = SDL_GetTicks();
	while (_running) {
		processInput(input, event);
		camera.updateDisplay();

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
	//Logging::log(L"elapsed %d\n", elapsedTime);
	if (_level != nullptr) {
		_level->update(elapsedTime);
	}
}

void Game::quit() {
	_running = false;
}

void Game::processInput(Input &input, SDL_Event &event) {
	input.beginNewFrame();
	recordKeyEvents(input, event);
	processKeyEvents(input);
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

	if (input.wasKeyPressed(SDL_SCANCODE_LEFT)) {
		_camera->bbLeft();
	}

	if (input.wasKeyPressed(SDL_SCANCODE_RIGHT)) {
		_camera->bbRight();
	}

	if (input.wasKeyPressed(SDL_SCANCODE_UP)) {
		_camera->bbUp();
	}

	if (input.wasKeyPressed(SDL_SCANCODE_DOWN)) {
		_camera->bbDown();
	}

	if (input.wasKeyPressed(SDL_SCANCODE_KP_PLUS)) {
		_camera->bbIncreaseSize();
	}

	if (input.wasKeyPressed(SDL_SCANCODE_KP_MINUS)) {
		_camera->bbDecreaseSize();
	}
}

void Game::createNewLevel() {
	//Logging::log(L"Creating new level\n");
	if (_level != nullptr) {
		delete _level;
	}
	_level = new Level();
	_camera->getContours();

	// convert contours to b2Vec2* vectors
	std::vector<std::vector<b2Vec2 *>> vertices;
	for (size_t i = 0; i < _camera->_contours.size(); i++) {
		std::vector<b2Vec2 *> c;
		for (size_t j = 0; j < _camera->_contours[i].size(); j++) {
			c.push_back(new b2Vec2((float)_camera->_contours[i][j].x, 
								   (float)_camera->_contours[i][j].y));
		}
		vertices.push_back(c);
	}

	// scale vertices to match screen size
	int bb_w = _camera->getBBWidth();
	int bb_h = _camera->getBBHeight();
	for (auto iterCont = vertices.begin(); iterCont < vertices.end(); iterCont++) {
		if (iterCont->size() > 3) {
			for (auto iterVert = iterCont->begin(); iterVert < iterCont->end(); iterVert++) {
				(*iterVert)->x = ((float)(*iterVert)->x / bb_w) * SCREEN_WIDTH;
				(*iterVert)->y = ((float)(*iterVert)->y / bb_h) * SCREEN_HEIGHT;
			}
		}
 	}

	// create objects based on color
	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].size() > 3) {
			switch (_camera->_colors[i].mostColor()) {
			case MOSTLY_RED:
				_level->addSpawner(new Spawner(_level, vertices[i]));
				i++;
				break;
			case MOSTLY_GREEN:
			default:
				_level->addSurface(new BouncySurface(_level->getWorld(), vertices[i]));
				break;
			case MOSTLY_BLUE:
				_level->addSurface(new StandardSurface(_level->getWorld(), vertices[i]));
				break;
			}
		}
	}
}

void Game::createObject(std::vector<b2Vec2*> vertices) {
}

int Game::updateTime() {
	int current = SDL_GetTicks();
	int elapsed = current - _last_update_ms;
	_last_update_ms = current;

	return elapsed;
}
