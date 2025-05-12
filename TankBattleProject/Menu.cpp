#include <iostream>
#include <string>
#include "Utils.h"
#include <conio.h>
#include "Menu.h"
#include "Game.h"

using namespace std;

// display the main menu
void Menu::displayMenu() {
    cout << "===========================\n";
    cout << "    Tank Battle Menu\n";
    cout << "===========================\n";
    cout << "1. Start a New Game\n";
    cout << "8. Instructions and Movement Keys\n";
    cout << "9. Exit\n";
    cout << "Please select one of these options: ";
}

// display game instructions
void Menu::displayInstructions() {
    clear_screen();
    cout << "\nInstructions:\n";
    cout << "1. Use the movement keys to move your character (O).\n";
    cout << "2. Avoid shells (*) thrown by your enemy tank.\n";
    cout << "3. Avoid mines (@) and shoot walls (#) and your enemy down!\n\n";
    cout << "=============================================\n";
    cout << "|               Keys                        |\n";
    cout << "=============================================\n";
    cout << "| Action                    | Player 1 | Player 2 |\n";
    cout << "---------------------------------------------\n";
    cout << "| RIGHT track forward       |    E     |    O     |\n";
    cout << "| RIGHT track backwards     |    D     |    L     |\n";
    cout << "| LEFT track forward        |    Q     |    U     |\n";
    cout << "| LEFT track backwards      |    A     |    J     |\n";
    cout << "| STAY                      |    S     |    K     |\n";
    cout << "| Shoot                     |    W     |    I (i) |\n";
    cout << "=============================================\n";
    cout << "Press ENTER to return to the menu...\n";
    cin.get();  // Wait for a key press to return
    clear_screen();
}


void Menu::startMenu() // Main navigating menu function
{
    char choice;  // get choice as char to handle invalid input
    bool flag = true; // Flag to check if the menu is displayed
    
    while (flag) 
    {
        displayMenu();

        choice = static_cast<char>(_getch());  // Read a single character input without pressing Enter

        switch (choice) {
        case '1': {
            cout << "\nStarting a new game...\n";
			Game().run(); // Start the game
			clear_screen(); // Clear the screen after the game ends
            break;
        }
        case '8':
            displayInstructions();
            break;
        case '9':
            clear_screen();
            cout << "\nExiting the game. Goodbye!\n";
            flag = false;  // Exit the program
            break;
        default:
            clear_screen(); // Handle invalid input
        }
    }
}


