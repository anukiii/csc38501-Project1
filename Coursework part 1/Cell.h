#pragma once
#include <vector>
class Cell
{
private:
	int xPos;// X position in the map
	int yPos;// Y position in the map
	int mazeId; //used for connections
	std::vector<int> connections; //-1 means no connection
	char currentChar;//E = exit, X = wall, Space is empty, S is start point
public:
	//Getters
	int getXpos();
	int getYpos();
	int getMazeId();
	std::vector<int> getConnections();
	char getCurrentChar();

	//Setters
	void setXPos(int xPosNew);
	void setYPos(int yPosNew);
	void setMazeId(int mazeIdNew);
	void setCurrentChar(int currentCharNew);
	void addConnection(int newConnection);

	//Other
	void clearConnections();

};

