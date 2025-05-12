#pragma once

#include <windows.h>

//UTILITY FUNCTIONS:
void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);
void clear_screen();



enum class Direction {
    UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT
};



enum class CHARS {
	WALL = '#',
	SPACE = ' ',
	TANK = 'O',
	MINE = '@',
	SHELL = '*',
	WEAK_WALL = '=',
};


