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
	//set Current f and h values for a*
	for( int i = 0; i < vectorOfCell.size(); i++) {
		vectorOfCell.at(i).calcFcost(xPos, yPos,vectorOfCell.at(centerPoint).getXpos(),vectorOfCell.at(centerPoint).getYpos());
	}

	std::vector<Cell> neighbours;
	bool found = false;
	bool duplicate;
	int tempId = cellId;
	addToPath(tempId);
	Cell tempCell;

	while (!found) {
		duplicate =false;
		neighbours.clear(); //get new set of neighbours;

		if (tempId - 1 > 0) {//left of it
			neighbours.push_back(vectorOfCell.at(tempId - 1));
		}
		if (tempId + 1 < mapSize * mapSize + mapSize) {//right of it
			neighbours.push_back(vectorOfCell.at(tempId +1));
		}		
		if (tempId + mapSize +1 < mapSize * mapSize + mapSize) {//bellow it
			neighbours.push_back(vectorOfCell.at(tempId +mapSize+1));
		}
		if (tempId - (mapSize +1) >0) {//bellow it
			neighbours.push_back(vectorOfCell.at(tempId -(mapSize+1)));
		}
		
		if (neighbours.empty()) {
			std::cout << "No valid neighbours, something's wrong";								//REMOVE LATER
			break;
		}

		//Finds neighbour with lowest F cost;
		for (int i = 0; i < neighbours.size(); i++) {
			tempCell = (i == 0 ? vectorOfCell.at(0) : tempCell);
			tempCell = (tempCell.getFcost() > vectorOfCell.at(i).getFcost() ? vectorOfCell.at(i) : tempCell);

		}


		
		for (int i = 0; i < path.size(); i++) {
			duplicate = (path.at(i) == tempCell.getMazeId() ? true : duplicate);			//Dunno if we need this
		}











		found = (tempId == centerPoint ? true : false);
	}





}

void Player::setPlayerId(int playerIdNew)
{
	playerId = playerIdNew;
}

int Player::getPlayerId()
{
	return playerId;
}
