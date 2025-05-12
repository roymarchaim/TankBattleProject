#include "Tank.h"
#include "Shell.h"

void Tank::move() {
	if (tankState != STATE::STAY) {
		Point dirAsPoint = convertDirToPoint(dir);
		Point nextPos;

		// Calculate the next position based on the tank's state
		if (tankState == STATE::MOVING_FORWARD)
			nextPos.addPoints(body[Size - 1], dirAsPoint);
		else
			nextPos.substructPoints(body[0], dirAsPoint);

		// Validate the next position for the cannon
		if (!isNextMoveValid(nextPos)) {
			// If the next position is invalid, stop the tank
			tankState = STATE::STAY;
			return;
		}

		// Erase the tank from the board
		for (int i = Size - 1; i >= 0; --i) {
			board->setSpecificChracter(body[i], (char)CHARS::SPACE);
		}

		// Update the tank's body positions
		if (!isDirChange) {
			if (Size == TANK_SIZE) {
				if (tankState == STATE::MOVING_FORWARD) {
					body[Size - 2].set(body[Size - 1].getX(), body[Size - 1].getY());
				}
				else {
					Point temp = body[Size - 2];
					body[Size - 2].set(nextPos.getX(), nextPos.getY());
					nextPos.set(temp.getX(), temp.getY());
				}
			}
		}
		else {
			nextPos.addPoints(body[0], dirAsPoint);
		}

		// Update the cannon's position
		body[Size - 1].set(nextPos.getX(), nextPos.getY());

		// Redraw the tank on the board
		for (int i = Size - 1; i >= 0; --i) {
			body[i].setChar(i == TANK_SIZE - 1 ? determineCanonSymbol() : tankChar);
			board->setSpecificChracter(body[i], body[i].getChar());
		}
	}
}

void Tank::keyPressed(char pressed) {
	int index = 0;
	for (char k : keys) {
		if (std::tolower(pressed) == k) {
			switch (index) {
			case (int)KEYS::RIGHT_TRACK_FORWARD:

				rightForward = true;

				break;

			case (int)KEYS::LEFT_TRACK_FORWARD:

				leftForward = true;

				break;

			case (int)KEYS::RIGHT_TRACK_BACKWARD:

				rightBackward = true;

				break;

			case (int)KEYS::LEFTT_TRACK_BACKWARD:

				leftBackward = true;

				break;

			case (int)KEYS::STAY:
				isStay = true;
				break;

			case (int)KEYS::SHOOT:

				isShoot = true;
				break;

			default:
				break;
			}
		}
		++index;
	}
}

void Tank::keysAnalsys() {
	bool TankRotate = false;
	Point rotateDes;

	if (isShoot && canonCoolDown == 0 && !canonDead)
	{
		Point initialShell;
		Shell s1(initialShell.addPoints(body[Size - 1], convertDirToPoint(dir)), dir, initialShell.addPoints(body[Size - 1], convertDirToPoint(dir)));

		char target = board->getChar(s1.getLocation());
		if (target == (char)CHARS::WALL || target == (char)CHARS::WEAK_WALL)
		{
			getBoard().setSpecificChracter(s1.getLocation(), (char)CHARS::SHELL);
			Sleep(5); //for explosion animation
			if (target == (char)CHARS::WALL)
				getBoard().setSpecificChracter(s1.getLocation(), (char)CHARS::WEAK_WALL);
			else
				getBoard().setSpecificChracter(s1.getLocation(), (char)CHARS::SPACE);
		}
		else //shooting range is clear
		{
			if (this->getBoard().startingShellIsValid(s1.getLocation()))
			{
				s1.setLocation(initialShell);
			}
			std::vector<Shell>& shells = board->getShells();
			shells.push_back(s1); // Create a new shell at the tank's position
			getBoard().setSpecificChracter(shells[shells.size() - 1].getLocation(), (char)CHARS::SHELL);
			Sleep(5);
		}
		canonCoolDown = RESET_CANON_COOLDOWN; // Reset cooldown
	}
	if (isStay) {
		tankState = STATE::STAY;
	}
	else if (rightBackward || rightForward || leftBackward || leftForward) //if any of the keys are pressed
	{
		if (tankState == STATE::STAY)
		{
			tankState = STATE::MOVING_FORWARD;
		}
		TankRotate = true;
		isDirChange = true;

		if (rightForward && leftBackward)
		{
			dir = Direction(((int)(dir)-2 + DIRECTIONS_AMOUNT) % DIRECTIONS_AMOUNT);
		}
		else if (rightForward && leftForward) {
			tankState = STATE::MOVING_FORWARD;
			TankRotate = false;
			isDirChange = false;
		}
		else if (rightBackward && leftForward)
		{
			dir = Direction(((int)(dir)+2) % DIRECTIONS_AMOUNT);
		}
		else if (rightBackward && leftBackward) {
			tankState = STATE::MOVING_BACKWARD;
			isDirChange = false;
			TankRotate = false;
		}
		else if (rightForward)
		{
			dir = Direction(((int)(dir)-1 + DIRECTIONS_AMOUNT) % DIRECTIONS_AMOUNT);
		}
		else if (rightBackward) {
			dir = Direction(((int)(dir)+1) % DIRECTIONS_AMOUNT);
		}
		else if (leftForward)
		{
			dir = Direction(((int)(dir)+1) % DIRECTIONS_AMOUNT);
		}
		else if (leftBackward) {
			dir = Direction(((int)(dir)-1 + DIRECTIONS_AMOUNT) % DIRECTIONS_AMOUNT);
		}
	}
	Point dirAsPoint = convertDirToPoint(dir);
	Point nextPos;

	if (tankState == STATE::MOVING_FORWARD) {
		nextPos.addPoints(body[Size - 1], dirAsPoint);
	}
	else if (tankState == STATE::MOVING_BACKWARD)
		nextPos.substructPoints(body[0], dirAsPoint);
	else //STAY
		nextPos.addPoints(body[0], dirAsPoint);
	if (TankRotate)
	{
		if (tankState == STATE::MOVING_FORWARD || tankState == STATE::STAY)
			rotateDes.addPoints(body[0], dirAsPoint);
		else
			rotateDes.substructPoints(body[0], dirAsPoint);
		if (!isNextMoveValid(nextPos) || !isNextMoveValid(rotateDes)) {
			dir = prevDir;
			isDirChange = false;
			tankState = STATE::STAY;
		}
		else
			prevDir = dir;
	}
	else
	{
		if (!isNextMoveValid(nextPos)) {
			dir = prevDir;
			isDirChange = false;
			tankState = STATE::STAY;
		}
		else
			prevDir = dir;
	}
}

Point Tank::convertDirToPoint(Direction d) {
	switch (d) {
	case Direction::UP: return Point(0, -1);
	case Direction::DOWN: return Point(0, 1);
	case Direction::LEFT: return Point(-1, 0);
	case Direction::RIGHT: return Point(1, 0);
	case Direction::UP_LEFT: return Point(-1, -1);
	case Direction::UP_RIGHT: return Point(1, -1);
	case Direction::DOWN_LEFT: return Point(-1, 1);
	case Direction::DOWN_RIGHT: return Point(1, 1);
	default: return Point(0, 0);
	}
}

Direction Tank::convertPointToDir(Point p) {
	if (p.getX() == 0 && p.getY() == -1) return Direction::UP;
	if (p.getX() == 0 && p.getY() == 1) return Direction::DOWN;
	if (p.getX() == -1 && p.getY() == 0) return Direction::LEFT;
	if (p.getX() == 1 && p.getY() == 0) return Direction::RIGHT;
	if (p.getX() == -1 && p.getY() == -1) return Direction::UP_LEFT;
	if (p.getX() == 1 && p.getY() == -1) return Direction::UP_RIGHT;
	if (p.getX() == -1 && p.getY() == 1) return Direction::DOWN_LEFT;
	if (p.getX() == 1 && p.getY() == 1) return Direction::DOWN_RIGHT;
	else
		std::cout << "tank and canon are never on the same spot" << std::endl;
	return Direction::UP; // Default return value
}

Direction Tank::determineCanonDirection(MOVEMENT currMovement, char canon_Dir) const
{
	switch (canon_Dir)
	{
	case '-':
		board->setCurrCanonChar('-'); // Set canon character
		if (currMovement == MOVEMENT::UP) //right
			return Direction::RIGHT;
		else if (currMovement == MOVEMENT::DOWN) //left
			return Direction::LEFT;

		break;
	case '|':
		board->setCurrCanonChar('|'); // Set canon character
		if (currMovement == MOVEMENT::UP) //up
			return Direction::UP;
		else if (currMovement == MOVEMENT::DOWN) //down
			return Direction::DOWN;
		break;
	case '/':
		board->setCurrCanonChar('/'); // Set canon character
		if (currMovement == MOVEMENT::UP) //up
			return Direction::UP_RIGHT;
		else if (currMovement == MOVEMENT::DOWN) //down
			return Direction::DOWN_LEFT;
		break;
	case '\\':
		board->setCurrCanonChar('\\'); // Set canon character
		if (currMovement == MOVEMENT::UP) //up
			return Direction::UP_LEFT;
		else if (currMovement == MOVEMENT::DOWN) //down
			return Direction::DOWN_RIGHT;
		break;

	default:
		break;
	}
	return Direction::UP; // Default case
}

char Tank::determineCanonSymbol() const {
	switch (dir)
	{
	case Direction::UP:
		return symbols[0];
	case Direction::DOWN:
		return symbols[0];
	case Direction::UP_RIGHT:
		return symbols[1];
	case Direction::DOWN_LEFT:
		return symbols[1];
	case Direction::UP_LEFT:
		return symbols[2];
	case Direction::DOWN_RIGHT:
		return symbols[2];
	case Direction::LEFT:
		return symbols[3];
	case Direction::RIGHT:
		return symbols[3];
	default:
		return ' '; // Default case
	}
}

bool Tank::isNextMoveValid(Point& p)
{
	char ch = board->getChar(p);
	// Allow movement only into empty spaces, mines, or shells
	return (ch == (char)CHARS::SPACE || ch == (char)CHARS::MINE || ch == (char)CHARS::SHELL);
}

bool Tank::isOneOfCanon(char symbol)
{
	bool flag = false;
	for (int i = 0; i < 4; i++)
	{
		if (symbol == getSymbol(i))
		{
			flag = true;
		}
	}
	return flag;
}