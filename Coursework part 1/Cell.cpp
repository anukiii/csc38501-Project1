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

void Cell::clearConnections() {
	connections.clear();
}
