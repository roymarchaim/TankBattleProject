#include "Shell.h"
#include "Tank.h"
#include <vector>


void Shell::draw() {
    board->setSpecificChracter(location, (char)CHARS::SHELL); // Draw the shell on the board
}
void Shell::erase() {
    board->setSpecificChracter(location, (char)CHARS::SPACE); // Remove the canon from the board
}


void Shell::drawShellsVector(Board& currBoard) {
    for (auto& shell : currBoard.getShells()) {
        currBoard.setSpecificChracter(shell.prevLocation, (char)CHARS::SPACE);
        currBoard.setSpecificChracter(shell.location, (char)CHARS::SHELL);
		shell.prevLocation = shell.location; // Update the previous location
    }
}

void Shell::eraseAllShells(Board& currBoard){
    for (auto& shell : currBoard.getShells())
    {
        currBoard.setSpecificChracter(shell.location, (char)CHARS::SPACE); // Remove the canon from the board
    }
}  


void Shell::move(Board& currBoard) {
    location.move(dir);
    currBoard.setSpecificChracter(location, (char)CHARS::SHELL); // Draw the shell on the board
}


void Shell::removeBombingShells(Board& currBoard, std::vector<Tank>& tanks) {
    auto& shells = currBoard.getShells();
    std::vector<Shell*> shellsToRemove; // Collect shells to remove

    for (auto& s : shells) {
        Point nextPos;
        nextPos.addPoints(s.getLocation(), tanks[0].convertDirToPoint(s.getDir()));
        char obj = currBoard.getChar(nextPos);

        if (obj == (char)CHARS::TANK) {
            for (auto& tank : tanks) {
                if (tank.getPosTank() == nextPos) {
                    currBoard.setSpecificChracter(tank.getPosCanon(), (char)CHARS::SPACE);
                    currBoard.setSpecificChracter(tank.getPosTank(), (char)CHARS::SHELL);
                    Sleep(5);
                    currBoard.setSpecificChracter(tank.getPosTank(), (char)CHARS::SPACE);
                    tank.setTankDead(true);
                }
            }
            shellsToRemove.push_back(&s);
        }
        else if (tanks[0].isOneOfCanon(obj)) {
            for (auto& tank : tanks) {
                if (tank.getPosCanon() == nextPos) {
                    tank.setCanonDead(true);
                    currBoard.setSpecificChracter(tank.getPosCanon(), (char)CHARS::SHELL);
                    Sleep(5);
                    currBoard.setSpecificChracter(tank.getPosCanon(), (char)CHARS::SPACE);
                    tank.setSize(1);
                    break;
                }
            }
            shellsToRemove.push_back(&s);
        }
        else if (obj == (char)CHARS::WALL) {
            currBoard.setSpecificChracter(nextPos, (char)CHARS::WEAK_WALL);
            shellsToRemove.push_back(&s);
        }
        else if (obj == (char)CHARS::WEAK_WALL) {
            currBoard.setSpecificChracter(nextPos, (char)CHARS::SPACE);
            shellsToRemove.push_back(&s);
        }
        else if (obj == (char)CHARS::SHELL ) {
            for (auto& shell : shells) {
                if (&s != &shell && shell.location == nextPos) {
                    board->setSpecificChracter(shell.location, (char)CHARS::SPACE);
                    shellsToRemove.push_back(&shell);
                }
            }
            shellsToRemove.push_back(&s);
        }
        else {
            s.move(currBoard);
        }
    }

    // Remove all collected shells
    for (auto* shell : shellsToRemove) {
        currBoard.setSpecificChracter(shell->prevLocation, (char)CHARS::SPACE);
		currBoard.setSpecificChracter(shell->location, (char)CHARS::SPACE);
        shells.erase(std::remove(shells.begin(), shells.end(), *shell), shells.end());
    }
}

