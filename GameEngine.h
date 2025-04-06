#pragma once
#include "Header.h"
#include "Globals.h"
#include "Snake.h"
#include "Render.h"

SDL_Point generateFood(const std::vector <SDL_Point>& snakeBody);

void handleInput(Snake& snake, SDL_Renderer* renderer);

void updateScoreFile(int score);