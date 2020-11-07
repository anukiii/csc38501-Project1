#include "Cell.h"
#include <vector>;

int Cell::getXpos() {
	return xPos;
}

int Cell::getYpos() {
	return yPos;
}

int Cell::getMazeId() {
	return mazeId;
}

std::vector<int> Cell::getConnections() {
	return connections;
}

char Cell::getCurrentChar() {
	return currentChar;
}

void Cell::setXPos(int xPosNew)
{
	xPos = xPosNew;
}

void Cell::setYPos(int yPosNew)
{
	yPos = yPosNew;
}

void Cell::setMazeId(int mazeIdNew)
{
	mazeId = mazeIdNew;

}

void Cell::setCurrentChar(int currentCharNew)
{
	currentChar = currentCharNew;
}

void Cell::addConnection(int newConnection)
{
	connections.push_back(newConnection);

}


int Cell::getFcost()
{
	return fCost;
}

void Cell::serParentId(int parentIdNew)
{
	parentId = parentIdNew;
}

int Cell::getParentId()
{
	return parentId;
}

void  Cell::calcFcost(int startPointX, int startPointY,int endPointX, int endPointY) {

	calcHcost(endPointX, endPointY); //always needed when using F cost
	
	fCost = sqrt(pow((double)xPos - (double)startPointX, 2) + pow((double)yPos - (double)startPointY, 2)); + hCost;
	

}

void Cell::calcHcost(int endPointX, int endPointY)
{
	hCost = sqrt(pow((double)xPos - (double)endPointX, 2) + pow((double)yPos - (double)endPointY, 2));
}
