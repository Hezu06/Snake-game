#include "Header.h"
#include "Graphics.h"
#include "Render.h"
#include "Snake.h"
#include "Globals.h"
#include "GameEngine.h"
#include "Music.h"

int main(int argc, char* args[]) {
	if (!init()) {
		std::cout << "Failed" << std::endl;
	}
	else {
		SDL_Window* window = initSDL();
		SDL_Renderer* renderer = createRenderer(window);
		bool start = false;

		while (!start) {
			renderStartScreen(window, renderer);
			renderPressStart(renderer);
			std::cout << "Waiting for player to start the game" << std::endl;
			SDL_Event event;
			while (SDL_WaitEvent(&event)) {
				if (event.type == SDL_QUIT) {
					running = false;
					start = true;
					break;
				}
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {

					drawGameplayBackground(window, renderer);
					SDL_RenderPresent(renderer);
					Snake snake(300, 300);
					SDL_Point food = generateFood(snake.getBody());
					SDL_RenderClear(renderer);
					// game loop
					Uint32 lastMoveTime = 0;
					const float snakeSpeed = 120;

					while (running) {
						if (!paused) {
							Uint32 currentTime = SDL_GetTicks();
							handleInput(snake, renderer);
							if (snake.eatFood(food)) {
								food = generateFood(snake.getBody());
								score += 10; // update score if snake eats food
							}
							if (currentTime - lastMoveTime >= snakeSpeed) {
								snake.move();
								lastMoveTime = currentTime;

								if (snake.checkCollision()) {
									showGameOver(renderer, snake, score);
								}

								SDL_RenderClear(renderer);
								drawGameplayBackground(window, renderer);
								renderFood(renderer, food);
								snake.render(renderer);
								renderPauseButton(renderer);
								renderPlayerScore(renderer, score);
								SDL_RenderPresent(renderer);
							}
						}
						else {
							handleInput(snake, renderer);
						}
					}
					start = true;
					break;
				}
			}
		}

		cleanUp(window, renderer);
	}
	return 0;
}