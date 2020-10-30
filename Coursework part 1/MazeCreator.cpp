#include <iostream>
#include <fstream>
#include "MazeCreator.h"
#include <random>

int MazeCreator::generateMap(int mapSize, int numExits) {
	std::ofstream newMapFile("TestFile.txt");
	newMapFile << "bumpis"<<'\n';
	std::cout << RNG(mapSize);

	return 0;
}



int MazeCreator::RNG(int range) {
	//random number generation using random library
	std::random_device rd;
	std::mt19937 engine{ rd() }; //seed
	std::uniform_int_distribution<> dist(0, range); //between 0 and range
	auto random_number = dist(engine);
	return random_number;
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


//Getters--
int MazeCreator::getMapSize()
{
	return mapSize;
}


int MazeCreator::getNumExits() {
	return numExits;
}

