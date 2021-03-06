#pragma once

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();

	/* 
	 * Renders everything to the screen
	 */
	void flip();

	/* 
	 * Clears the screen
	 */
	void clear();

	SDL_Renderer * getRenderer() const;

private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
};