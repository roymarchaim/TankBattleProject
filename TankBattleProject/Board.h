#pragma once

#include "Point.h"
#include "Utils.h"
#include "Shell.h"
#include <vector>

class Board {

    static constexpr int MAX_X = 80;
    static constexpr int MAX_Y = 25;

	char CurrCanonChar = (char)CHARS::SPACE;
	int canon_dir = 0;
    Point locationOnBoard;

    const char* originalBoard[MAX_Y] = {
        // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
          "                                                                                ", // 0
          "             #             #                     #                    |         ", // 1
          "             #             ######                #                    O         ", // 2
          "             #                                   #                              ", // 3
          "             #                                                                  ", // 4
          "             #                                                                  ", // 5
          "                          ##########     @                                      ", // 6
          "                                   #             #################              ", // 7
          "                                   #             #        #                     ", // 8
          "####################               #             #        #                     ", // 9
          "                           @       ##########    #        #                     ", // 10
          "                                            #             #           ##########", // 11
          "                                            #             #           #         ", // 12
          "               ###########                  #             #           #         ", // 13
          "                     #                      ###############           #         ", // 14
          "                     #                #               #               #         ", // 15
          "############         #                #     @         #               #         ", // 16
          "                     #                #               #        @                ", // 17
          "                     #                #               #                         ", // 18
          "                     #       #        #################                         ", // 19
          "       ###############       #             #                  ##################", // 20
          "                             #             #                                    ", // 21
          "    |                        #             #                                    ", // 22
          "    O                        #             #                                    ", // 23
          "                                                                                "  // 24
    };


    char currentBoard[MAX_Y][MAX_X + 1] = {}; // +1 for null terminator
    std::vector <Shell> shells;

public:

    char getChar(Point location) const { return currentBoard[location.getY()][location.getX()]; }
   
	void setSpecificChracter(Point p, char c) {
		currentBoard[p.getY()][p.getX()] = c;
		gotoxy(p.getX(), p.getY());
		std::cout << currentBoard[p.getY()][p.getX()];
	}

    void setLocationOnBoard(const Point& newLocation) { locationOnBoard = newLocation; }
    
    char getCurrCanonChar() const { return CurrCanonChar; }

    void setCurrCanonChar(char newChar) {CurrCanonChar = newChar; }

    int getCanonDir() const { return canon_dir; }

    void setCanonDir(int newDir) { canon_dir = newDir; }

    std::vector<Shell>& getShells() { return shells; }

    void setShells(const std::vector<Shell>& newShells) { shells = newShells; }
    std::vector<Point> getMines() const {
        std::vector<Point> mines;
        for (int y = 0; y < MAX_Y; ++y) {
            for (int x = 0; x < MAX_X; ++x) {
                if (originalBoard[y][x] == (char)CHARS::MINE) {
                    mines.push_back(Point(x, y));
                }
            }
        }
        return mines;
    }

	bool startingShellIsValid(Point location) const{ //true is valid , false is invalid
		int shellX = location.getX(), shellY = location.getY();
        return currentBoard[shellY][shellX] == (char)CHARS::SPACE || currentBoard[shellY][shellX] == (char)CHARS::MINE;
	}

    void reset(); //reset board to its original state
    void print() const;

    Point findNextTankOnBoard(Point& lastTankLocation);

};

