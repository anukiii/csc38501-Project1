#include <iostream>
#include <fstream>
#include "MazeCreator.h"
#include <random>
#include <list>

int MazeCreator::generateMap(int mapSize, int numExits) {
	std::ofstream newMapFile("TestFile.txt");
	//newMapFile << "bumpis"<<'\n';
	//std::cout << RNG(mapSize);
	std::list<int> exitPos;
	std::cout << numExits << '\n';
	std::cout << mapSize << '\n';
	while ((int)exitPos.size() < numExits) {
		allocateExits(numExits,exitPos);
		//breakout statement??
	}

	for (int i = 0; i < mapSize; i++) {

	}

	return 0;
}

std::list<int> MazeCreator::allocateExits(int numExits, std::list<int> exitList) {
	for (int i = 0; i < numExits; i++) {
		int temp = RNG(mapSize * 4);
		exitList.push_back(temp); // chooses possible exits	
	}
	exitList.unique(); //removes duplicates
	return exitList;
}



//Random number Generation --
int MazeCreator::RNG(int range) {
	std::random_device rd;
	std::mt19937 engine{ rd() }; //seed
	std::uniform_int_distribution<> dist(0, range); //between 0 and range
	auto random_number = dist(engine);
	return random_number;
}


//User input functions --
int MazeCreator::getInputMapSize()
{
	std::cout << "Choose map size between 3-50" << '\n';
	std::cin >> mapSize;
	return mapSize;
}

int MazeCreator::getInputNumExits()
{
	std::cout << "Choose number of Exits" << '\n';
	std::cin >> numExits;
	return numExits;
}

//Getters --
int MazeCreator::getMapSize()
{
	return mapSize;
}


int MazeCreator::getNumExits() {
	return numExits;
}

