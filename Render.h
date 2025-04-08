#pragma once
#include "Header.h"
#include "Globals.h"
#include "Snake.h"
#include "Music.h"
#include"defs.h"

void logErrorAndExit(const char* msg, const char* error);

SDL_Window* initSDL();

SDL_Renderer* createRenderer(SDL_Window* window);

void drawGameplayBackground(SDL_Window* window, SDL_Renderer* renderer);

void renderStartScreen(SDL_Window* window, SDL_Renderer* renderer);

void renderPressStart(SDL_Renderer* renderer);

void renderPauseButton(SDL_Renderer* renderer);

void renderPauseScreen(SDL_Renderer* renderer);

SDL_Point generateFood(const std::vector <SDL_Point>& snakeBody);

void renderFood(SDL_Renderer* renderer, SDL_Point food);

void renderPlayerScore(SDL_Renderer* renderer, int& score);

void renderHighScore(SDL_Renderer* renderer, int& highScore);

void showGameOver(SDL_Renderer* renderer, Snake& snake, int& score, SDL_Point food);