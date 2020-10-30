#include <iostream>
#include <fstream>
#include "MazeCreator.h"

int MazeCreator::generateMap(int mapSize, int numExits) {
	std::ofstream newMapFile("TestFile.txt");
	return 0;
}


int MazeCreator::getInputMapSize()
{
	int mapSize;
	std::cout << "Choose map size between 3-50" << '\n';
	std::cin >> mapSize;

	return mapSize;
}

int MazeCreator::getInputNumExits()
{
	int numExits;
	std::cout << "Choose number of Exits" << '\n';
	std::cin >> numExits;

	return numExits;
}

int MazeCreator::getMapSize()
{
	return mapSize;
}


int MazeCreator::getNumExits() {
	return numExits;
}

