#pragma once
#include <list>
class Cell
{
private:
	int xPos;// X position in the map
	int yPos;// Y position in the map
	int mazeId; //used for connections
	std::list<int> connections; //-1 means no connection
	char currentChar;//E = exit, X = wall, Space is empty, S is start point
public:
	int getXpos() { return xPos; }
	int getYpos() { return yPos; }
	int getMazeId() { return mazeId; }
	std::list<int> getConnections() { return connections; }
	char getCurrentChar(){ return currentChar; }
	void setXPos(int xPosNew) { xPos = xPosNew; }
	void setYPos(int yPosNew) { yPos = yPosNew; }
	void setMazeId(int mazeIdNew) { mazeId = mazeIdNew; }
	void setCurrentChar(int currentCharNew) { currentChar = currentCharNew; }
	void addConnection(int newConnection) { connections.push_back(newConnection); }
};

