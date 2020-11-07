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
	double fCost;// gcost + h Cost
	double hCost;//used in case fCost parity
	int parentId;//Used in a*


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
	void calcFcost(int startPointX, int startPointY, int endPointX, int endPointY);//Calculates F cost
	void calcHcost(int endPointX, int endPointY);//calculated H cost
	int getFcost(); // used to set F cost;

	void serParentId(int parentIdNew);
	int getParentId();

};

