#include <iostream>
#include <cstring>
#include "Board.h"

void Board::reset() { //reset the board to its original state
    for (int i = 0; i < MAX_Y; i++) {
        memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
    }
}

void Board::print() const { //print the current board state
    for (int i = 0; i < MAX_Y - 1; i++) {
        std::cout << currentBoard[i] << '\n';
    }
    std::cout << currentBoard[MAX_Y - 1];
}

//this function finds the next tank that appears on the board given the last location it already found one for efficiency
//the 1st tank search starts at (0,0) and the last tank at (MAX_X-1, MAX_Y-1):
Point Board::findNextTankOnBoard(Point& lastTankLocation)
{  
   int startX = lastTankLocation.getX();  
   int startY = lastTankLocation.getY();  

   for (int y = startY; y < MAX_Y; ++y) {  
       for (int x = (y == startY ? startX + 1 : 0); x < MAX_X; ++x) {  
           if (currentBoard[y][x] == (char)CHARS::TANK) {  
               // Check surrounding characters for canon  
               if (y > 0 && (currentBoard[y - 1][x] == '|' || currentBoard[y - 1][x] == '/' || currentBoard[y - 1][x] == '-' || currentBoard[y - 1][x] == '\\')) {  
                   setCurrCanonChar(currentBoard[y - 1][x]);  
                   setCanonDir(1);  
               }  
               else if (y < MAX_Y - 1 && (currentBoard[y + 1][x] == '|' || currentBoard[y + 1][x] == '/' || currentBoard[y + 1][x] == '-' || currentBoard[y + 1][x] == '\\')) {  
                   setCurrCanonChar(currentBoard[y + 1][x]);  
                   setCanonDir(-1);  
               }  
               else if (x > 0 && (currentBoard[y][x - 1] == '|' || currentBoard[y][x - 1] == '/' || currentBoard[y][x - 1] == '-' || currentBoard[y][x - 1] == '\\')) {  
                   setCurrCanonChar(currentBoard[y][x - 1]);  
                   setCanonDir(-1);  
               }  
               else if (x < MAX_X - 1 && (currentBoard[y][x + 1] == '|' || currentBoard[y][x + 1] == '/' || currentBoard[y][x + 1] == '-' || currentBoard[y][x + 1] == '\\')) {  
                   setCurrCanonChar(currentBoard[y][x + 1]);  
                   setCanonDir(1);  
               }  
               else if (x > 0 && y > 0 && (currentBoard[y - 1][x - 1] == '|' || currentBoard[y - 1][x - 1] == '/' || currentBoard[y - 1][x - 1] == '-' || currentBoard[y - 1][x - 1] == '\\')) {  
                   setCurrCanonChar(currentBoard[y - 1][x - 1]);  
                   setCanonDir(-1);  
               }  
               else if (x < MAX_X - 1 && y > 0 && (currentBoard[y - 1][x + 1] == '|' || currentBoard[y - 1][x + 1] == '/' || currentBoard[y - 1][x + 1] == '-' || currentBoard[y - 1][x + 1] == '\\')) {  
                   setCurrCanonChar(currentBoard[y - 1][x + 1]);  
                   setCanonDir(1);  
               }  
               else if (x > 0 && y < MAX_Y - 1 && (currentBoard[y + 1][x - 1] == '|' || currentBoard[y + 1][x - 1] == '/' || currentBoard[y + 1][x - 1] == '-' || currentBoard[y + 1][x - 1] == '\\')) {  
                   setCurrCanonChar(currentBoard[y + 1][x - 1]);  
                   setCanonDir(-1);  
               }  

               return { x, y };  
           }  
       }  
   }  

   // If no 'O' is found, return an invalid position  
   setCanonDir(0);  
   return { -1, -1 };  
}

