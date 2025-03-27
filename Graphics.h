#pragma once
#include "Header.h"
#include "defs.h"

bool init();

void logErrorAndExit(const char* msg, const char* error);

SDL_Window* initSDL();

SDL_Renderer* createRenderer(SDL_Window* window);

void cleanUp(SDL_Window* window, SDL_Renderer* renderer);