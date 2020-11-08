#pragma once
#include <vector>
#include "Cell.h"
class Player
{
private:
	std::vector<int> path;
	int xPos;
	int yPos;
	int cellId;
	int playerId;


	//Private pathfinding functions
	int findLowestFcost(std::vector<int> openPositions,std::vector<Cell> vectorOfCells);
	std::vector<int> findValidNeighbours(std::vector<Cell> vectorOfCells, int currentPoistion,int mapSize);

public:
	//Setters 
	void setXpos(int xPosNew);
	void setYpos(int yPosNew);
	void setCellId(int cellIdNew);
	void addToPath(int nextCell);
	void setPlayerId(int playerIdNew);


	//Getters
	std::vector<int> getPath();
	int getXPos();
	int getYpos();
	int getCellId();
	int getPlayerId();
	int getNextPos();
	
	//Other
	void pathFinding(std::vector<Cell> vectorOfCell,int centerPoint, int mapSize);
	void advancePath();



};

