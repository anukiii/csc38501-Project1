#include "Player.h"
#include <iostream>

void Player::setXpos(int xPosNew)
{
	xPos = xPosNew;
}

void Player::setYpos(int yPosNew)
{
	yPos = yPosNew;
}

void Player::setCellId(int cellIdNew)
{
	cellId = cellIdNew;
}

void Player::wait()
{
	waiting = true;
}

void Player::stopWait()
{
	waiting = false;
}

void Player::addToPath(int nextCell)
{
	path.push_back(nextCell);
}

std::vector<int> Player::getPath()
{
	return path;
}

int Player::getXPos()
{
	return xPos;
}

int Player::getNextPos() {

	return path.at(path.size() - 1);
}

int Player::getYpos()
{
	return yPos;
}

int Player::getCellId()
{
	return cellId;
}

bool Player::waitStatus()
{
	return waiting;
}

void Player::pathFinding(std::vector<Cell> vectorOfCell, int centerPoint,int mapSize)
{


	bool found = false; //check if current position is the centerpoint
	std::vector<int> openPositions;
	std::vector<int> closedPositions;
	std::vector<int> neighbours;
	int currentPos = cellId;
	int destX = vectorOfCell.at(centerPoint).getXpos();
	int destY = vectorOfCell.at(centerPoint).getYpos();
	vectorOfCell.at(currentPos).calcFcost(xPos,yPos,destX,destY); // calc first f cost
	openPositions.push_back(currentPos); // first thing in open
	bool inClosed;
	bool inOpen;



	while(!found) {

		
		//Find lowest Fcost in openPositions vector
		currentPos = openPositions.at(findLowestFcost(openPositions, vectorOfCell));


		//Remove from open and add to close
		//std::cout <<"CurrentPosition is: "<<currentPos <<"|| Size of openPositions is: "<<openPositions.size()<<'\n';
		openPositions.erase(openPositions.begin() + findLowestFcost(openPositions, vectorOfCell));
		closedPositions.push_back(currentPos);

		//Check if we're currently on the destination
		found = (currentPos == centerPoint ? true : found);


		//Create list of valid neighbours
		neighbours = findValidNeighbours(vectorOfCell, currentPos, mapSize);
		//std::cout <<"CurrentPosition is: "<<currentPos<<"|| Size of neighbours Vector is: " << neighbours.size() << "\n";

		for (int i = 0; i<neighbours.size(); i++) {
			inClosed = false;
			inOpen = false;
			//See if neighbours are in closed vector
			
			
			for (int j = 0; j < closedPositions.size(); j++) {
				inClosed = (neighbours.at(i) == closedPositions.at(j) ? true : inClosed);
			}

			
			//if not, calculate F cost and add tempPos as parent node

			if (!inClosed) {
				vectorOfCell.at(neighbours.at(i)).calcFcost(xPos, yPos, destX, destY);
				vectorOfCell.at(neighbours.at(i)).serParentId(currentPos);
				for (int j = 0; j < openPositions.size(); j++) {
					inOpen = (neighbours.at(i) == openPositions.at(j) ? true : inOpen);
				}
				//if not in open, add to open
				if (!inOpen) {
					openPositions.push_back(neighbours.at(i));
				}

			}
			

		}

	}

	//Once we've found position, create the path, backtracking 

	do {
		path.push_back(currentPos);
		currentPos = vectorOfCell.at(currentPos).getParentId();
	} while (currentPos != cellId);



}


int Player::findLowestFcost(std::vector<int> openPositions, std::vector<Cell> vectorOfCells) {
	int lowestPosition =0;
	for (int i = 0; i < openPositions.size(); i++) {
		lowestPosition = (vectorOfCells.at(i).getFcost() < vectorOfCells.at(lowestPosition).getFcost() ? i : lowestPosition);
	}

	return lowestPosition;


}


std::vector<int> Player::findValidNeighbours(std::vector<Cell> vectorOfCells, int currentPosition, int mapSize) {

	std::vector<int> Neighours;

	//left
	if (currentPosition - 1 > 0) {
		if (vectorOfCells.at(currentPosition - 1).getCurrentChar() != 'X' && vectorOfCells.at(currentPosition -1).getCurrentChar()!='\n' && vectorOfCells.at(currentPosition - 1).getCurrentChar() != 'E') {
			Neighours.push_back(currentPosition - 1);
		}
	}
	//right
	if (currentPosition + 1 < mapSize*mapSize) {
		if (vectorOfCells.at(currentPosition + 1).getCurrentChar() != 'X' && vectorOfCells.at(currentPosition + 1).getCurrentChar() != '\n' && vectorOfCells.at(currentPosition + 1).getCurrentChar() != 'E'){
			Neighours.push_back(currentPosition + 1);
		}
	}
	//up
	if (currentPosition - (mapSize + 1) >mapSize) {
		if (vectorOfCells.at(currentPosition - (mapSize + 1)).getCurrentChar() != 'X' && vectorOfCells.at(currentPosition -(mapSize+ 1)).getCurrentChar() != '\n' && vectorOfCells.at(currentPosition - (mapSize + 1)).getCurrentChar() != 'E') {
			Neighours.push_back(currentPosition - (mapSize + 1));
		}
	}
	//down
	if (currentPosition + mapSize + 1 < mapSize * mapSize) {
		if (vectorOfCells.at(currentPosition + mapSize + 1).getCurrentChar() != 'X' && vectorOfCells.at(currentPosition + mapSize + 1).getCurrentChar() != '\n' && vectorOfCells.at(currentPosition + mapSize + 1).getCurrentChar() != 'E') {
			Neighours.push_back(currentPosition + mapSize + 1);
		}
	}

	return Neighours;

}


void Player::setPlayerId(int playerIdNew)
{
	playerId = playerIdNew;
}

int Player::getPlayerId()
{
	return playerId;
}

void Player::advancePath()
{
	if (!path.empty()) {
		cellId = path.at(path.size() - 1);
		path.pop_back();
	}
}
