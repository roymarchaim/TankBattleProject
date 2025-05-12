#pragma once

#include "Point.h"
#include "Utils.h"
#include <iostream>
#include <vector>

class Tank; // Forward declaration of Tank class
class Board; // Forward declaration of Board class

class Shell
{
	Point location;
	Point prevLocation;
	Board* board = nullptr;

	Direction dir;

public:

	bool operator==(const Shell& other) const {
		return location == other.location && dir == other.dir;
	}

	Shell() : location(0, 0), dir(Direction::UP) {} // Default constructor

	Shell(Point p, Direction d, Point prev) : location(p), dir(d), prevLocation(prev) {} // Constructor with parameters

	void setBoard(Board& newBoard) {board = &newBoard;}

	void setLocation(Point p) {location = p;}
	Point getLocation() const {return location;}

	Direction getDir() const {return dir;}
	void setDir(Direction newDir) {dir = newDir;}

	void removeBombingShells(Board& board, std::vector <Tank>& tanks);
	void drawShellsVector(Board& board);
	void eraseAllShells(Board& board);
	void move(Board& currBoard);
	void draw();
	void erase();
};

