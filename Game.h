#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "SDL_image.h"
#include "Hex.h"
#include <iostream>

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update(Hex** g, int XG, int YG, int x, int y, bool lv);
	void render(Hex** g, int XG, int YG);
	void clean();

	bool running() { return isRunning; }


private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif // GAME_H