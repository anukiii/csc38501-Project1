#pragma once
#include<vector>
#include<string>
#include "Cell.h"
class MazeCreator
{
private:
	int mapSize;
	int numExits;
	std::string fileName;

	int RNG(int range); // generates a random number between 0 and range
	std::vector<Cell> drawMap();
	void drawToFile(std::vector<Cell> cellvector);
	std::vector<Cell> mapFixer(std::vector<Cell> vectorOfCells, int centerPoint);
	void printOnScreen(std::vector<Cell> cellvector);
public:
	void generateMap(int mapSize, int numExits);//creates and populates maze file
	void setInputMapSize();//gets user input for map size in tiles
	void setInputNumExits();//gets user input for number of exits
	void setInputFileName(); //asks user what name they want to save the file
	void startMenu(); //Start Menu
	int getMapSize(); // returns mapSize var.
	int getNumExits();// returns numExits var.
	void readFromFile();
	std::vector<Cell> pathfinding(std::vector <Cell> vectorOfCells, int centerPoint);
	std::vector<Cell> mazingAlg(std::vector<Cell>vectorOFCells, int centerPoint);


};

