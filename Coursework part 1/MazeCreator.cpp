#include <iostream>
#include "MazeCreator.h"

int MazeCreator::generateMap(int mapSize, int numExits) {

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

