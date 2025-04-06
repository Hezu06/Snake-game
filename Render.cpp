#include "Render.h"



void drawGameplayBackground(SDL_Window* window, SDL_Renderer* renderer) {
	// render background
	SDL_Rect background{};
	background.x = 0;
	background.y = 0;
	background.w = SCREEN_WIDTH;
	background.h = SCREEN_HEIGHT;
	SDL_SetRenderDrawColor(renderer, 76, 106, 73, 0);
	SDL_RenderFillRect(renderer, &background);

	// render pham vi tro choi
	SDL_SetRenderDrawColor(renderer, 31, 51, 29, 0);
	SDL_RenderDrawLine(renderer, 200, 100, 700, 100); // canh tren
	SDL_RenderDrawLine(renderer, 200, 100, 200, 600); // canh ben trai
	SDL_RenderDrawLine(renderer, 200, 600, 700, 600); // canh duoi
	SDL_RenderDrawLine(renderer, 700, 100, 700, 600); // canh ben phai

	for (int i = 225; i <= 675; i += 25) {
		SDL_SetRenderDrawColor(renderer, 69, 92, 67, 0);
		SDL_RenderDrawLine(renderer, i, 100, i, 600);
	}
	for (int j = 125; j <= 575; j += 25) {
		SDL_SetRenderDrawColor(renderer, 69, 92, 67, 0);
		SDL_RenderDrawLine(renderer, 200, j, 700, j);
	}
}

void renderStartScreen(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load("Src/Start_Screen.jpg");
	if (surface == nullptr) logErrorAndExit("IMG_Load", IMG_GetError());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == nullptr) logErrorAndExit("CreateTexture", SDL_GetError());

	SDL_FreeSurface(surface);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
}

void renderPressStart(SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont("Font/font.ttf", 24);
	if (!font) {
		SDL_Log("Failed to load font: %s", TTF_GetError());
		return;
	}

	SDL_Color textColor = { 0, 0, 0 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "PRESS SPACE TO PLAY", textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_Rect textRect = { SCREEN_WIDTH / 2 - textSurface->w / 2, SCREEN_HEIGHT - 100, textSurface->w, textSurface->h };
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_RenderPresent(renderer);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);
}

void renderPauseButton(SDL_Renderer* renderer) {
	SDL_Surface* surface = IMG_Load("Src/pauseButton.png");
	if (surface == nullptr) {
		logErrorAndExit("IMG_Load", IMG_GetError());
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		logErrorAndExit("CreateTexture", SDL_GetError());
	}

	SDL_Rect des = { 850, 0, 50, 50 };
	SDL_RenderCopy(renderer, texture, NULL, &des);


	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void renderPauseScreen(SDL_Renderer* renderer) {
	SDL_RenderClear(renderer);
	TTF_Font* font = TTF_OpenFont("Font/font.ttf", 36);
	if (!font) {
		SDL_Log("Failed to load font: %s", TTF_GetError());
		return;
	}

	SDL_Color textColor = { 255, 255, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Paused", textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_Rect textRect = { SCREEN_WIDTH / 2 - textSurface->w / 2, SCREEN_HEIGHT / 2 - textSurface->h / 2, textSurface->w, textSurface->h };
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);


	SDL_Surface* playSurface = IMG_Load("Src/playButton.png");
	if (!playSurface) {
		logErrorAndExit("IMG_Load", IMG_GetError());
	}
	SDL_Texture* playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
	if (!playTexture) {
		logErrorAndExit("CreateTexture", SDL_GetError());
	}
	SDL_Rect playDes = { 400, 400, 100, 100 };
	SDL_RenderCopy(renderer, playTexture, NULL, &playDes);

	SDL_Surface* restartSurface = IMG_Load("Src/restartButton.png");
	if (!restartSurface) {
		logErrorAndExit("IMG_Load", IMG_GetError());
	}
	SDL_Texture* restartTexture = SDL_CreateTextureFromSurface(renderer, restartSurface);
	if (!restartTexture) {
		logErrorAndExit("CreateTexture", SDL_GetError());
	}
	SDL_Rect restartDes = { 400, 500, 100, 100 };
	SDL_RenderCopy(renderer, restartTexture, NULL, &restartDes);


	SDL_RenderPresent(renderer);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
	TTF_CloseFont(font);
}

void renderFood(SDL_Renderer* renderer, SDL_Point food) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect foodRect = { food.x, food.y, 25, 25 };
	SDL_RenderFillRect(renderer, &foodRect);
}

void renderPlayerScore(SDL_Renderer* renderer, int& score) {
	TTF_Font* font = TTF_OpenFont("Font/font.ttf", 24);
	if (!font) {
		SDL_Log("Failed to load font : %s", TTF_GetError());
		return;
	}

	std::string point = "Score: " + std::to_string(score);

	SDL_Color textColor = { 6, 43, 19 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, point.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect = { 600, 50, textSurface->w, textSurface->h };
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void showGameOver(SDL_Renderer* renderer, Snake& snake, int& score, SDL_Point food)
{
	TTF_Font* font = TTF_OpenFont("Font/font.ttf", 24);
	if (!font) {
		SDL_Log("Failed to load font : %s", TTF_GetError());
		return;
	}

	SDL_Rect popupRect = { 200, 200, 500, 200 };
	SDL_SetRenderDrawColor(renderer, 12, 13, 12, 255);
	SDL_RenderFillRect(renderer, &popupRect);

	SDL_Color textColor = { 255, 255, 255 };
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game Over", textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect = { 355, 250, textSurface->w, textSurface->h };
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	SDL_Rect restartButton = { 280, 300, 175, 50 };
	SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
	SDL_RenderFillRect(renderer, &restartButton); // render green rect for restart

	SDL_Rect exitButton = { 510, 300, 100, 50 };
	SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
	SDL_RenderFillRect(renderer, &exitButton); // render red rect for exit

	SDL_Surface* restartSurface = TTF_RenderText_Solid(font, "Restart", textColor);
	SDL_Texture* restartTexture = SDL_CreateTextureFromSurface(renderer, restartSurface);
	SDL_Rect restartTextRect = { 286, 315, restartSurface->w, restartSurface->h };
	SDL_RenderCopy(renderer, restartTexture, NULL, &restartTextRect);

	SDL_Surface* exitSurface = TTF_RenderText_Solid(font, "Exit", textColor);
	SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
	SDL_Rect exitTextRect = { 515, 315, exitSurface->w, exitSurface->h };
	SDL_RenderCopy(renderer, exitTexture, NULL, &exitTextRect);

	SDL_RenderPresent(renderer);

	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(restartSurface);
	SDL_FreeSurface(exitSurface);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(restartTexture);
	SDL_DestroyTexture(exitTexture);
	TTF_CloseFont(font);

	SDL_Event wait;

	while (true) {
		SDL_WaitEvent(&wait);
		if (wait.type == SDL_QUIT) {
			running = false;
			break;
		}
		if (wait.type == SDL_MOUSEBUTTONDOWN) {
			if (wait.button.x >= 280 && wait.button.x <= 455 && wait.button.y >= 300 && wait.button.y <= 350) { // restart
				score = 0; // reset score
				snake = Snake(300, 300); // reset snake
				food = generateFood(snake.getBody());
				break;
			}
			else if (wait.button.x >= 510 && wait.button.x <= 610 && wait.button.y >= 300 && wait.button.y <= 350) { // exit
				running = false;
				break;
			}
		}
	}
}