#include "Snake.h"

void Snake::move() {
	SDL_Point head = body.front();

	switch (direction) {
	case UP:
		head.y -= snakeSize;
		break;
	case DOWN:
		head.y += snakeSize;
		break;
	case LEFT:
		head.x -= snakeSize;
		break;
	case RIGHT:
		head.x += snakeSize;
		break;
	}
	body.insert(body.begin(), head);
	if (!hasEaten) {
		body.pop_back();
	}
	else {
	hasEaten = false;
	}
}
void Snake::grow() {
	hasEaten = true;
}
bool Snake::eatFood(SDL_Point food) {
	SDL_Point head = body.front();
	if (head.x == food.x && head.y == food.y) {
		grow();
		return true;
	}
	return false;
}

void Snake::setDirection(Direction newDirection) {
	if (newDirection == UP && direction != DOWN) {
		direction = newDirection;
	}
	else if (newDirection == DOWN && direction != UP) {
		direction = newDirection;
	}
	else if (newDirection == LEFT && direction != RIGHT) {
		direction = newDirection;
	}
	else if (newDirection == RIGHT && direction != LEFT) {
		direction = newDirection;
	}
}

bool Snake::checkCollision() {
	SDL_Point head = body.front();
	if (head.x < 200 || head.x >= 700 || head.y < 100 || head.y >= 600) {
		return true;
	}

	for (int i = 1; i < body.size(); i++) {
		if (head.x == body[i].x && head.y == body[i].y) {
			return true;
		}
	}
	return false;
}

void Snake::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 5, 38, 22, 255);
	for (SDL_Point point : body) {
		SDL_Rect rect = { point.x, point.y, snakeSize, snakeSize };
		SDL_RenderFillRect(renderer, &rect);
	}
}
