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
	//for( int i = 0; i < vectorOfCell.size(); i++) {
	//	//if (vectorOfCell.at(i).getMazeId() != -1) {
	//		vectorOfCell.at(i).calcFcost(xPos, yPos, vectorOfCell.at(centerPoint).getXpos(), vectorOfCell.at(centerPoint).getYpos());
	//		std::cout << vectorOfCell.at(i).getFcost() << '\n';
	//	//}
	//}


	std::vector<Cell> open;
	std::vector<Cell> closed;

	std::vector<Cell> neighbours;
	bool found = false;
	bool duplicate;
	bool inOpen;
	int tempId = cellId;
	open.push_back(vectorOfCell.at(tempId));
	int openPositionToRemove =0;

	while (!found) {



		//Current becomes open tile with lowest F cost
		for(int i =0; i <open.size();i++){

			

			tempId = (i == 0 ? open.at(0).getMazeId() : tempId);
			openPositionToRemove = (i == 0 ? 0: openPositionToRemove);
			
			//openPositionToRemove = (vectorOfCell.at(tempId).getFcost() >= open.at(i).getFcost() ? i : openPositionToRemove);
			//tempId = (vectorOfCell.at(tempId).getFcost() >= open.at(i).getFcost() ? open.at(i).getMazeId() : tempId);
			
		}

		if (open.empty()) {
			found = true;
			break;
		}

		//Add to closed List aka. explored cells
		closed.push_back(vectorOfCell.at(tempId));


		//std::cout << open.size() << ' ' << openPositionToRemove<<'\n';
		
		std::cout<< "whats being removed " <<(open.begin() + openPositionToRemove)->getMazeId()<<"    What should be removed " <<tempId<<'\n';
		
		open.erase(open.begin() + openPositionToRemove); // removes the element from open
		//Set Tempid to the Id of tempCell

		//Checks if this is the target node
		found = (tempId == centerPoint ? true : false);
		
		std::cout << tempId << ' ' << centerPoint << "\n";


		inOpen = false;
		duplicate =false;
		neighbours.clear(); //get new set of neighbours;



		//Finds if nodes are valid and traversible. If statements needed to avoid out of bounds exceptions
		if (tempId - 1 > 0) {//left of it
			if (vectorOfCell.at(tempId - 1).getCurrentChar() != 'X' && vectorOfCell.at(tempId - 1).getCurrentChar() != '\n') {
				neighbours.push_back(vectorOfCell.at(tempId - 1));
			}
		}
		if (tempId + 1 < mapSize * mapSize + mapSize) {//right of it
			if (vectorOfCell.at(tempId + 1).getCurrentChar() != 'X'&& vectorOfCell.at(tempId +1).getCurrentChar() != '\n') {
				neighbours.push_back(vectorOfCell.at(tempId + 1));
			}
		}		
		if (tempId + mapSize + 1 < mapSize * mapSize + mapSize) {//bellow it
			if (vectorOfCell.at(tempId + mapSize + 1).getCurrentChar() != 'X'&& vectorOfCell.at(tempId +mapSize +1).getCurrentChar() != '\n') {
				neighbours.push_back(vectorOfCell.at(tempId + mapSize + 1));
			}
		}
		if (tempId - (mapSize + 1) > 0) {//above it
			if (vectorOfCell.at(tempId - (mapSize + 1)).getCurrentChar() != 'X'&& vectorOfCell.at(tempId -(mapSize+ 1)).getCurrentChar() != '\n') {
				neighbours.push_back(vectorOfCell.at(tempId - (mapSize + 1)));
			}
		}


		if (neighbours.empty()) {
			std::cout << "No valid neighbours, something's wrong";								//REMOVE LATER
			break;
		}

		std::cout << neighbours.size() << '\n';

		//up to here it works neighbor wise;

		for (int i = 0; i < neighbours.size(); i++) {
			
			
			

			//check if it's in closed vector
			for (int j = 0; j < closed.size(); j++) {
				duplicate = (closed.at(j).getMazeId() == neighbours.at(i).getMazeId() ? true : duplicate);
			}

			//check if it's in open
			for (int j = 0; j < open.size(); j++) {
				vectorOfCell.at(neighbours.at(i).getMazeId()).calcFcost(xPos,yPos,vectorOfCell.at(centerPoint).getXpos(), vectorOfCell.at(centerPoint).getYpos());
				inOpen = (open.at(j).getMazeId() == neighbours.at(i).getMazeId() ? true : inOpen);
			}

			if (!duplicate) {
				path.push_back(neighbours.at(i).getMazeId());										//Testing stuff
				vectorOfCell.at(neighbours.at(i).getMazeId()).serParentId(tempId);
				if (!inOpen) {
					open.push_back(vectorOfCell.at(neighbours.at(i).getMazeId()));
				}
			}

		}

		
	}
	

	
	/*while (tempId != cellId) {
		addToPath(tempId);
		tempId = tempCell.getParentId();
		tempCell = vectorOfCell.at(tempId);

	}*/



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
