#pragma once
#include "Header.h"

class Snake {
public:
	enum Direction { UP, DOWN, LEFT, RIGHT };

	// Khoi tao vi tri ban dau cua snake
	Snake(int startX, int startY) {
		body.push_back({ startX, startY });
		body.push_back({ startX - snakeSize, startY });
		direction = RIGHT;
	}
	std::vector <SDL_Point> getBody() {
		return body;
	}
	void move();

	void grow();

	bool eatFood(SDL_Point food);

	void setDirection(Direction newDirection);

	int getSnakeSpeed() const;

	void setSnakeSpeed(int speed);

	bool checkCollision();

	void render(SDL_Renderer* renderer);
private:
	std::vector <SDL_Point> body;
	Direction direction;
	bool hasEaten = false;
	static constexpr int snakeSize = 25;
	int snakeSpeed = 120;
};
