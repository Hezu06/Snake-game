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
		Music music;
		bool backToMenu;

		std::ofstream scoreFile("score.txt"); // tao file score.txt
		if (scoreFile.is_open()) {
			scoreFile << 0 << "\n";
			scoreFile.close();
		}
		else {
			std::cerr << "Unable to open score file." << std::endl;
		}

		std::vector<int> scores;

		while (!start) {
			renderStartScreen(window, renderer);
			backToMenu = false;
			std::cout << "Waiting for player to start the game" << std::endl;
			int choice = showMenu(renderer);
			if (choice == 2) {
				return 0; 
			}
			else if (choice == 1) { // High Score
				bool inHighScore = true;
				int scrollOffset = 0;
				scores = sortScoresFromFile("score.txt");
				while (inHighScore) {
					renderHighScore(renderer, scores, scrollOffset);
					SDL_Event e;
					while (SDL_PollEvent(&e)) {
						if (e.type == SDL_QUIT) exit(0);

						if (e.type == SDL_KEYDOWN) {
							if (e.key.keysym.sym == SDLK_ESCAPE) {
								inHighScore = false;
							}
							else if (e.key.keysym.sym == SDLK_DOWN) {
								if (scrollOffset + 10 < scores.size()) scrollOffset++;
							}
							else if (e.key.keysym.sym == SDLK_UP) {
								if (scrollOffset > 0) scrollOffset--;
							}
						}

						if (e.type == SDL_MOUSEBUTTONDOWN) {
							int mx = e.button.x;
							int my = e.button.y;

							if (mx >= 620 && mx <= 660 && my >= 50 && my <= 90) { // chon nut X
								inHighScore = false;
							}
						}

						if (e.type == SDL_MOUSEWHEEL) {
							if (e.wheel.y > 0 && scrollOffset > 0) {
								scrollOffset--; // coun len
							}
							else if (e.wheel.y < 0 && scrollOffset + 10 < scores.size()) {
								scrollOffset++; // cuon xuong
							}
						}
					}
				}
			}
			else if (choice == 0) { // Play
				SDL_Event event;
				while (SDL_WaitEvent(&event)) {
					if (event.type == SDL_QUIT) {
						running = false;
						start = true;
						break;
					}
					drawGameplayBackground(window, renderer);
					SDL_RenderPresent(renderer);
					Snake snake(300, 300);
					SDL_Point food = generateFood(snake.getBody());
					SDL_RenderClear(renderer);

					

					// game loop
					Uint32 lastMoveTime = 0;

					while (running) {
						
						Uint32 frameStart = SDL_GetTicks();

						if (!paused) {
							int snakeSpeed = snake.getSnakeSpeed();
							if (backToMenu) {
								break;
							}
							Uint32 currentTime = SDL_GetTicks();
							handleInput(snake, renderer, backToMenu);
							if (snake.eatFood(food)) {
								Mix_PlayChannel(-1, music.eatSound, 0);
								food = generateFood(snake.getBody());
								score += 10;
								if (snakeSpeed >= 10 && score % 100 == 0) {
									snake.setSnakeSpeed(snakeSpeed - 10);
								}
							}
							if (currentTime - lastMoveTime >= snakeSpeed) {
								snake.move();
								lastMoveTime = currentTime;

								if (snake.checkCollision()) {
									Mix_PlayChannel(-1, music.gameOverSound, 0);
									updateScoreFile(score);
									if (score > highScore) {
										highScore = score;
									}
									showGameOver(renderer, snake, score, food);
								}

								SDL_RenderClear(renderer);
								drawGameplayBackground(window, renderer);
								renderFood(renderer, food);
								snake.render(renderer);
								renderPauseButton(renderer);
								renderPlayerScore(renderer, score);
								renderHighScore(renderer, highScore);
								SDL_RenderPresent(renderer);
								Mix_HaltChannel(-1);
							}
						}
						else {
							handleInput(snake, renderer, backToMenu);
							if (backToMenu) {
								break;
							}
						}

						Uint32 frameTime = SDL_GetTicks() - frameStart;
						if (frameTime < 8) {
							SDL_Delay(8 - frameTime);
						}
					}
					if (backToMenu) {
						break;
					}
					else {
						start = true;
						break;
					}
				}
			}
		}
		music.~music();
		//remove("score.txt");
		cleanUp(window, renderer);
	}
	return 0;
}