#include "Music.h"

Music::Music() {
	eatSound = Mix_LoadWAV("Music/food.mp3");
	if (!eatSound) {
		std::cout << "Failed to load eat sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}
	gameOverSound = Mix_LoadWAV("Music/gameover.mp3");
	if (!gameOverSound) {
		std::cout << "Failed to load game over sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}
}

Music::~Music() {
	Mix_FreeChunk(eatSound);
	Mix_FreeChunk(gameOverSound);
}