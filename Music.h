#pragma once
#include "defs.h"
#include "Globals.h"
#include "Header.h"

struct Music {
	Music();
	~Music();
	Mix_Chunk* eatSound = nullptr;
	Mix_Chunk* gameOverSound = nullptr;
};

