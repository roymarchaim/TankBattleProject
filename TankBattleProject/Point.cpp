#include <iostream>
#include "Point.h"
#include "Tank.h"

void Point::move(Direction d) {
	switch (d) {
	case Direction::UP:
		y = (MAX_Y + (y - 1)) % MAX_Y;
		break;
	case Direction::LEFT:
		x = (MAX_X + (x - 1)) % MAX_X;
		break;
	case Direction::DOWN:
		y = (y + 1) % MAX_Y;
		break;
	case Direction::RIGHT:
		x = (x + 1) % MAX_X;
		break;
	case Direction::UP_LEFT:
		x = (MAX_X + (x - 1)) % MAX_X;
		y = (MAX_Y + (y - 1)) % MAX_Y;
		break;
	case Direction::UP_RIGHT:
		x = (x + 1) % MAX_X;
		y = (MAX_Y + (y - 1)) % MAX_Y;
		break;
	case Direction::DOWN_LEFT:
		x = (MAX_X + (x - 1)) % MAX_X;
		y = (y + 1) % MAX_Y;
		break;
	case Direction::DOWN_RIGHT:
		x = (x + 1) % MAX_X;
		y = (y + 1) % MAX_Y;
		break;
	
	}
}
