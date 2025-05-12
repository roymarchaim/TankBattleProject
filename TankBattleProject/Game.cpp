#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Game.h"
#include "Board.h"
#include "Utils.h"
#include "Tank.h"
#include "Shell.h"


void Game::run() 
{
    //  Initialize the game
    ShowConsoleCursor(false); // Hide the cursor for a better game experience
    clear_screen(); // Clear input buffer
    Board board;
    board.reset();  // Reset the board state
    board.print(); // Print the initial state of the board

    std::vector<Tank> livingTanks; // Vector to hold the tanks
    std::vector<int> deadTanks; // Vector to hold the dead tanks numbers to print their death message
    setTanksData(livingTanks, board); // Set the tanks data

    Shell shell;
    shell.setBoard(board);

    std::vector<Point> mines = board.getMines(); // Get the mines from the board

    int moveIndex = 0; // Index for the tank movement: move only when even
    bool esc_pressed = false;

    
    while (!isGameOver && !returnToMenu && !esc_pressed) // Phase 2: Main game loop
    {
        //  Input Handling
        for (int i = 0; i < INPUT_BUFFER_SIZE; ++i) 
        {
            Sleep(20);
            if (_kbhit()) 
            {
                char key = static_cast<char>(_getch());
                if (key == ESC) {
                    pauseGame();
                }

                if (!returnToMenu) {
                    for (auto& tank : livingTanks) {
                        tank.keyPressed(key);

                    }
                }
            }
        }
        
        //  Update Game State
        shell.removeBombingShells(board, livingTanks); // Remove shells that hit the tank
        shell.drawShellsVector(board); // Draw all shells

        for (auto& tank : livingTanks) {
            
            if (moveIndex % 2 == 0) // to make the shells move faster
            {
				tank.keysAnalsys(); // Analyze the keys pressed
                tank.move();
                tank.setIsDirChange(false);
                tank.setTankTracks();
            }
            if (tank.getCanonCoolDown() > 0) {
                tank.setCanonCoolDown(tank.getCanonCoolDown() - 1); // Decrease cooldown
            }
        }


        //  Check Game Over
        for (auto& minePoint : mines) 
        {
            for (auto& tank : livingTanks) {
                if (tank.getPosTank() == minePoint) {
                    tank.setTankDead(true); // Mark the tank as dead
                }
            }
       
            if (board.getChar(minePoint) == (char)CHARS::SPACE) {
                board.setSpecificChracter(minePoint, (char)CHARS::MINE); // Draw the mine on the board
            }
        }

        if (!returnToMenu) 
        {
           
            for (auto& tank : livingTanks) { // Check which tanks have died
                if (tank.isTankDead()) {
                    deadTanks.push_back(tank.getTankNumber());
                }
            }

			//if both died of shells/mines or both are cannon-less - declare a tie:
            if (deadTanks.size() == PLAYING_TANKS || (livingTanks[0].isCanonDead() && livingTanks[1].isCanonDead())) {
                MessageBox(NULL, L"Game is Over - returning to main menu", L"IT'S A TIE!", MB_OK);
				isGameOver = true; // Set the game over flag
            }
            else if (deadTanks.size() == UNIQUE_LOSER_DETECTED) {
                std::wstring deadTankMessage = L"tank" + std::to_wstring(deadTanks[0]) + L" LOST!";
                MessageBox(NULL, L"Game is Over - returning to main menu", deadTankMessage.c_str(), MB_OK);
                isGameOver = true; // Set the game over flag
            }

            if (deadTanks.size() > 0) {
                board.reset();
                clear_screen();
                isGameOver = true; // Set the game over flag
                break;
            }
        }

        moveIndex++; // Increment the move index
    }
}



void Game::pauseGame() //if ESC is pressed
{ 
    MessageBox(NULL, L"The game has been paused! Press OK and then press ESC again to continue or X to go back to the main menu.", L"Game Paused", MB_OK);
	bool flag = true; 
    
    while (flag) 
    {
        if (_kbhit()) 
        {
            char pressedKey = static_cast<char>(_getch());  // Get the pressed key if was pressed

            if (std::tolower(pressedKey) == EXIT) {
                returnToMenu = true; // Set the flag to return to the menu
				clear_screen(); // Clear the screen
                flag = false;
            }

            if (pressedKey == ESC) {
				returnToMenu = false; // Set the flag to return to the menu
                flag = false;
            }

        }
    }
}

void Game::setTanksData(std::vector<Tank>& tanks, Board& board) 
{
	Point lastTankLocation; // Initialize the last tank location
	for (int i = 0; i < PLAYING_TANKS; ++i) 
    {
		Tank tank;
		tank.setTankNumber((i + 1));
        tank.setBoard(board); // Set the board for tank1
        tank.setPos(board.findNextTankOnBoard(lastTankLocation)); //assume tank1 is the first tank (higher on screen)
		tanks.push_back(tank);
		lastTankLocation = tanks[i].getPosTank(); // Update the last tank location
	}
    tanks[0].setKeys("edqasw"); // Set the keys for tank1
    tanks[1].setKeys("olujki"); // Set the keys for tank2
}