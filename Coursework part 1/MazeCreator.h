#pragma once
class MazeCreator
{
private:
	int mapSize;
	int numExits;
	int RNG(int range); // generates a random number between 0 and range
			
public:
	int generateMap(int mapSize, int numExits);//creates and populates maze file
	int getInputMapSize();//gets user input for map size in tiles
	int getInputNumExits();//gets user input for number of exits
	int getMapSize(); // returns mapSize var.
	int getNumExits();// returns numExits var.


};

