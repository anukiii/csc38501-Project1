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


	std::vector<Cell> open;
	std::vector<Cell> closed;

	std::vector<Cell> neighbours;
	bool found = false;
	bool duplicate;
	bool inOpen;
	Cell tempCell = vectorOfCell.at(playerId);
	open.push_back(tempCell);
	int tempId;

	while (!found) {



		//Current becomes open tile with lowest F cost
		for(int i =0; i <open.size();i++){
			tempCell = (i == 0 ? open.at(0) : tempCell);
			tempCell = (tempCell.getFcost() > open.at(i).getFcost() ? open.at(i) : tempCell);

		}

		//Add to closed List aka. explored cells
		closed.push_back(tempCell);

		//Set Tempid to the Id of tempCell
		tempId= tempCell.getMazeId();

		//Checks if this is the target node
		found = (tempId == centerPoint ? true : false);



		inOpen = false;
		duplicate =false;
		neighbours.clear(); //get new set of neighbours;



		//Finds if nodes are valid and traversible. If statements needed to avoid out of bounds exceptions
		if (tempId - 1 > 0) {//left of it
			if (vectorOfCell.at(tempId - 1).getCurrentChar() == ' ') {
				neighbours.push_back(vectorOfCell.at(tempId - 1));
			}
		}
		if (tempId + 1 < mapSize * mapSize + mapSize) {//right of it
			if (vectorOfCell.at(tempId + 1).getCurrentChar() == ' ') {
				neighbours.push_back(vectorOfCell.at(tempId + 1));
			}
		}		
		if (tempId + mapSize + 1 < mapSize * mapSize + mapSize) {//bellow it
			if (vectorOfCell.at(tempId + mapSize + 1).getCurrentChar() == ' ') {
				neighbours.push_back(vectorOfCell.at(tempId + mapSize + 1));
			}
		}
		if (tempId - (mapSize + 1) > 0) {//bellow it
			if (vectorOfCell.at(tempId - (mapSize + 1)).getCurrentChar() == ' ') {
				neighbours.push_back(vectorOfCell.at(tempId - (mapSize + 1)));
			}
		}

		
		if (neighbours.empty()) {
			std::cout << "No valid neighbours, something's wrong";								//REMOVE LATER
			break;
		}


		//Finds neighbour with lowest F cost;
		for (int i = 0; i < neighbours.size(); i++) {
			
			
			for (int j = 0; j < closed.size(); j++) {
				duplicate = (neighbours.at(i).getMazeId()== closed.at(j).getMazeId() ? true:duplicate);
			}
			if (!duplicate) {
				for (int j = 0; j < open.size(); j++) {
					inOpen = (neighbours.at(i).getMazeId() == neighbours.at(j).getMazeId() ? true : inOpen);
				}
			}

			if (!inOpen && !duplicate) {
				neighbours.at(i).serParentId(tempId);
				open.push_back(neighbours.at(i));
			}

		}

		
	}

	while (tempId != playerId) {
		addToPath(tempId);
		tempId = tempCell.getParentId();
		tempCell = vectorOfCell.at(tempId);

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
