#include "MazeCreator.h"
#include <iostream>


int main() {


	std::cout << MazeCreator::generateMap<<'\n';


	return 0;
}



int MazeCreator::generateMap() {
	int mapSize;
	int numExits;

	std::cout << "Choose map size between 3-50"<<'\n';
	std::cin >> mapSize;
	std::cout << "Choose number of Exits" << '\n';
	std::cin >> numExits;



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

