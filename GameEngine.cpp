#include "GameEngine.h"

SDL_Point generateFood(const std::vector <SDL_Point>& snakeBody) {
	SDL_Point food{};
	bool valid;
	do {
		valid = true;
		food.x = 200 + (rand() % 20) * 25;
		food.y = 100 + (rand() % 20) * 25;
		for (SDL_Point point : snakeBody) {
			if (point.x == food.x && point.y == food.y) {
				valid = false;
				break;
			}
		}
	} while (!valid);
	return food;
}

void handleInput(Snake& snake, SDL_Renderer* renderer) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_w: case SDLK_UP:
				snake.setDirection(Snake::UP);
				break;
			case SDLK_s: case SDLK_DOWN:
				snake.setDirection(Snake::DOWN);
				break;
			case SDLK_a: case SDLK_LEFT:
				snake.setDirection(Snake::LEFT);
				break;
			case SDLK_d: case SDLK_RIGHT:
				snake.setDirection(Snake::RIGHT);
				break;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.x >= 850 && event.button.x <= 900 && event.button.y >= 0 && event.button.y <= 50) { // pause button
				if (!paused) {
					renderPauseScreen(renderer);
					paused = true;
				}
			}
			else if (paused && event.button.x >= 400 && event.button.x <= 500 && event.button.y >= 400 && event.button.y <= 500) { // resume button
				paused = false;
			}
			else if (paused && event.button.x >= 400 && event.button.x <= 500 && event.button.y >= 500 && event.button.y <= 600) { // restart button
				paused = false;
				snake.setSnakeSpeed(120);
				score = 0; // reset score
				snake = Snake(300, 300); // reset snake
			}
		}
	}
}