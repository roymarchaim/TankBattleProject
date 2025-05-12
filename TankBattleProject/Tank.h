#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "Point.h"
#include "Shell.h"


class Tank {

    static constexpr int TANK_SIZE = 2;
    static constexpr int RESET_CANON_COOLDOWN = 5; // number of iterations before canon can shoot again
    static constexpr int DIRECTIONS_AMOUNT = 8; // Number of directions
    static constexpr char symbols[] = { '|', '/', '\\','-' };

    enum DirNames { U, UR, R, DR, D, DL, L, UL, S };
    enum class KEYS { RIGHT_TRACK_FORWARD, RIGHT_TRACK_BACKWARD, LEFT_TRACK_FORWARD, LEFTT_TRACK_BACKWARD, STAY, SHOOT };
    enum class MOVEMENT { DOWN = -1, STAY, UP }; //change enum name to MOVEMENT_CHANGE
    enum class STATE { MOVING_FORWARD, MOVING_BACKWARD, STAY }; //can shoot only when stay

    char tankChar = (char)CHARS::TANK;
    
    int Size = TANK_SIZE;
    Point body[TANK_SIZE];
    Direction dir=Direction::UP;
    Direction prevDir = Direction::UP;
    int tankNumber = 0; // Default tank id
    int canonCoolDown = RESET_CANON_COOLDOWN; // current Cooldown for canon
    std::string keys = "";
 
    MOVEMENT movement = MOVEMENT::STAY; // Use the correct type for movement
    STATE tankState = STATE::STAY; // Use the correct type for tankState

    Board* board = nullptr; // Pointer to the board object

    bool isDirChange = false; // Initialize previous direction to UP

	bool canonDead = false; // Flag to check if canon is dead
	bool tankDead = false; // Flag to check if tank is dead

	bool leftBackward = false; // Flag to check if the tank is moving backwards
	bool rightBackward = false; // Flag to check if the tank is moving backwards
	
	bool leftForward = false; // Flag to check if the tank is moving forwards
	bool rightForward = false; // Flag to check if the tank is moving forwards

	bool isShoot = false; // Flag to check if the tank is shooting
	bool isStay = false; // Flag to check if the tank is stationary

public:

    void setSize(int newSize) { Size = newSize; }
    
    void setPos(const Point& p) {
        char canonChar = board->getCurrCanonChar(); // Get the canon character from the board
        movement = (MOVEMENT)board->getCanonDir(); // Get the canon direction from the board
        body[0] = p; // Set the position of the tank (not canon)
        Point canonDirection = convertDirToPoint(determineCanonDirection(movement, canonChar)); // Get the direction of the canon as a Point
        body[1] = Point(p.getX() + canonDirection.getX(), p.getY() + canonDirection.getY()); // Set the position of the tank body relative to the canon
    }
    void setChar(char canon) {
        body[1].setChar(canon);
		body[0].setChar(tankChar);
    }
    void setKeys(const char* karr) { keys = karr; }
    
    void setBoard(Board& newBoard) {
        board = &newBoard;  // Assign the new board reference
        board->setLocationOnBoard(body[0]); // Set the initial location of the tank on the board
    }

	Board& getBoard() const { return *board; }


	Point getPosCanon() const {	return body[1];}
	Point getPosTank() const {return body[0];} 

    bool getIsDirChange() const { return isDirChange; }
	void setIsDirChange(bool newDir) {isDirChange = newDir;}

    MOVEMENT getMovement() const {return movement;}

    void setMovement(MOVEMENT newMovement) {  movement = newMovement;}

    Direction getDir() const {   return dir; }

    void setDir() {
        Point curr;
        dir=convertPointToDir(curr.substructPoints(body[1], body[0]));
    }

    bool isCanonDead() const {  return canonDead; }

    void setCanonDead(bool isDead) { canonDead = isDead; }

    bool isTankDead() const { return tankDead; }

    void setTankDead(bool isDead) { tankDead = isDead; }
    int getCanonCoolDown() const { return canonCoolDown; }

    void setCanonCoolDown(int newCoolDown) { canonCoolDown = newCoolDown; }
	void setTankNumber(int name) { tankNumber = name; }
    int getTankNumber() const { return tankNumber; }
    char getSymbol(int index) { return symbols[index]; }
    char convertKeyToCHar(int key) { return keys[key]; }

    void setTankTracks() { rightBackward = rightForward = leftBackward = leftForward = isStay = isShoot = isDirChange = false; }

    void keysAnalsys();
    Point convertDirToPoint(Direction d);
    Direction convertPointToDir(Point p);
    Direction determineCanonDirection(MOVEMENT movement, char canon_Dir) const;
    char determineCanonSymbol() const;
    void move();
    void keyPressed(char c);
    bool isNextMoveValid(Point& p);
    bool isOneOfCanon(char symbol);
};

