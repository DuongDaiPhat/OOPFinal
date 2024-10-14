#include "BaseFunction.h"
static bool createWindow(SDL_Window* window) {
	window = SDL_CreateWindow("Viu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		cout << "Khoi tao cua so that bai" << endl;
		return false;
	}
	return true;
}
static bool createRenderer(SDL_Window *window, SDL_Renderer *screen) {
	screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (screen == nullptr) {
		cout << "Khoi tao man hinh that bai" << endl;
		return false;
	}
	return true;
}
bool initGame(SDL_Window* window, SDL_Renderer* screen) {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		cout << "Khong the khoi tao tro choi" << endl;
		return false;
	}
	if (!createWindow(window)) {
		SDL_DestroyWindow(window);
		return false;
	}
	if (!createRenderer(window,screen)) {
		SDL_DestroyRenderer(screen);
		SDL_DestroyWindow(window);
		return false;
	}
	return true;
}