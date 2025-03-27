#include "Graphics.h"

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		std::cout << "Failed" << SDL_GetError() << std::endl;
		success = false;
	}

	if (!(IMG_Init(IMG_INIT_PNG))) {
		std::cout << "Failed" << IMG_GetError() << std::endl;
		success = false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	return success;
}

void logErrorAndExit(const char* msg, const char* error)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
	SDL_Quit();
}

SDL_Window* initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		logErrorAndExit("SDL_Init", SDL_GetError());

	SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

	return window;
}

SDL_Renderer* createRenderer(SDL_Window* window)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	return renderer;
}

void cleanUp(SDL_Window* window, SDL_Renderer* renderer) {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}