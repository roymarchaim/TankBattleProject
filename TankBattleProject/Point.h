#pragma once
#include <cmath>
#include <iostream>
#include "utils.h"

class Point {
	int x = 1, y = 1;
	char ch = (char)CHARS::SPACE; 
	enum { MIN_X = 0, MIN_Y = 0, MAX_X = 79, MAX_Y = 24 }; //special border values for returning the point to the board

public:
	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;// && ch == other.ch;
	}

	Point() : x(0), y(0), ch((char)CHARS::SPACE) {}

	Point(int newX, int newY) : x(newX), y(newY) {}

	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void set(int x1, int y1) {
		x = x1;
		y = y1;
	}
	void setChar(char c) {
		ch = c;
	}
	char getChar() const {
		return ch;
	}

	void move(Direction d);


	Point addPoints(Point p1, Point p2) {
		x = (MAX_X+p1.x + p2.x)%MAX_X;
		y = (MAX_Y+p1.y + p2.y)%MAX_Y;
		return Point(x, y);
	}

	Point substructPoints(Point p1, Point p2) {
		x = ( p1.x - p2.x + MAX_X)%MAX_X; 
		y = ( p1.y - p2.y + MAX_Y)%MAX_Y;
		return Point(x, y);
	}

};

