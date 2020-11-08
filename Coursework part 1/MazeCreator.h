#pragma once
#include<vector>
#include<string>
#include "Cell.h"
#include "Player.h"
class MazeCreator
{
private:
	int mapSize;//Size of the map
	int numExits;//Number of exits/players
	std::string fileName;//Name of the file read or saved to 
	std::vector<Player> listofPlayers; // Current maze Layout
	std::vector < std::vector < Cell>> fullList; //used when player traverses maze

	//Setters
	void setInputMapSize();//gets user input for map size in tiles
	void setInputNumberPlayers();//gets user input for number of exits
	void setInputFileName(); //asks user what name they want to save the file
	void addPlayer(int StartCellId);
	
	//Getters
	int getMapSize(); // returns mapSize var.
	int getNumExits();// returns numExits var.
	
	//Statistics
	int RNG(int range); // generates a random number between 0 and range

	//Maze generation and drawing the maze map
	void generateMap(int mapSize, int numExits);//creates and populates maze file
	std::vector<Cell> mapFixer(std::vector<Cell> vectorOfCells, int centerPoint);//puts the apropriate ascii charachters to display
	std::vector<Cell> mazingAlg(std::vector<Cell>vectorOFCells, int centerPoint);//maze generation algorithm (recursive backtracker)
	std::vector<Cell> drawMap();//generates the maze in the form of a cell vector file
	void printOnScreen(std::vector<Cell> cellvector);//prints vector of cells in cmd

	//Related to players interacting with maze
	void runMaze(std::vector<Cell> vectorOfCells);//Used to run players through the maze
	void statistics();//Runs many mazes to get statistics of how many moves needed on average to get out of maze
	
	//Related to files
	void saveRanMazeToFile(); //Used to save larger maze to txt file
	void readFromFile();//reads maze from file
	void drawToFile(std::vector<Cell> cellvector);//translates cell vector to text file
	


public:

	void startMenu(); //Start Menu


};

