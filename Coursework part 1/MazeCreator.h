#pragma once
#include<list>
#include<string>
class MazeCreator
{
private:
	int mapSize;
	int numExits;
	std::string fileName;

	int RNG(int range); // generates a random number between 0 and range
	std::list<int> allocateExits(int numExits, std::list<int> exitList);
	int DrawMap(std::string fileNameComplete, int mapSize, std::list<int> exitPos);

public:
	int generateMap(int mapSize, int numExits);//creates and populates maze file
	void setInputMapSize();//gets user input for map size in tiles
	void setInputNumExits();//gets user input for number of exits
	void setInputFileName(); //asks user what name they want to save the file
	
	int getMapSize(); // returns mapSize var.
	int getNumExits();// returns numExits var.

};

