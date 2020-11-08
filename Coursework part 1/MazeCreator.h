#pragma once
#include<vector>
#include<string>
#include "Cell.h"
#include "Player.h"
class MazeCreator
{
private:
	int mapSize;
	int numExits;
	std::string fileName;
	std::vector<Player> listofPlayers;


	int RNG(int range); // generates a random number between 0 and range
	std::vector<Cell> drawMap();//generates the maze in the form of a cell vector file
	void drawToFile(std::vector<Cell> cellvector);//translates cell vector to text file
	std::vector<Cell> mapFixer(std::vector<Cell> vectorOfCells, int centerPoint);//puts the apropriate ascii charachters to display
	void printOnScreen(std::vector<Cell> cellvector);//prints vector of cells in cmd
	void generateMap(int mapSize, int numExits);//creates and populates maze file
	void setInputMapSize();//gets user input for map size in tiles
	void setInputNumberPlayers();//gets user input for number of exits
	void setInputFileName(); //asks user what name they want to save the file
	int getMapSize(); // returns mapSize var.
	int getNumExits();// returns numExits var.
	void readFromFile();//reads maze from file
	std::vector<Cell> mazingAlg(std::vector<Cell>vectorOFCells, int centerPoint);//mazze generation algorithm (recursive backtracker)
	void runMaze(std::vector<Cell> vectorOfCells);
	
	
	
	void addPlayer(int StartCellId);


	std::vector<int> findExits(std::vector<Cell> vectorOfCells);
	bool validPath(int direction, int tempId, int currentId, std::vector<Cell> vectorOfCells);

public:

	void startMenu(); //Start Menu


};

