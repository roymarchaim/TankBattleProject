#pragma once
#include "Board.h"

class Game
{
	static constexpr int ESC = 27; //ASCII value of the ESC key
	static constexpr char EXIT = 'x'; // Key to exit the game
	static constexpr int UNIQUE_LOSER_DETECTED = 1; // Unique loser detected
	static constexpr int INPUT_BUFFER_SIZE = 10; // Size of the input buffer
	static constexpr int PLAYING_TANKS = 2; // Maximum number of tanks
	bool returnToMenu = false; // Flag to indicate if the game should return to the menu
	bool isGameOver = false; // Flag to indicate if the game is over
	

public:
	
	void run(); //controls main game loop
	void pauseGame(); //when pressed ESC
	void setTanksData(std::vector<Tank>& tanks, Board& board); // Set the data for the tanks


};

