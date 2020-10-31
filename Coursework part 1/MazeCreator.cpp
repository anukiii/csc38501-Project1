#include <iostream>
#include <fstream>
#include "MazeCreator.h"
#include <random>
#include <list>

int MazeCreator::generateMap(int mapSize, int numExits) {
	std::ofstream newMapFile(fileName +".txt");
	//newMapFile << "bumpis"<<'\n';
	//std::cout << RNG(mapSize);
	std::list<int> exitPos;
	std::cout << numExits << '\n';
	std::cout << mapSize << '\n';
	while ((int)exitPos.size() < numExits) {
		exitPos = allocateExits(numExits,exitPos);
		exitPos.size();
		//breakout statement??
	}


	return 0;
}

std::list<int> MazeCreator::allocateExits(int numExits, std::list<int> exitList) {
	for (int i = 0; i < numExits; i++) {
		exitList.push_back(RNG(mapSize * 4)); // chooses possible exits	
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
void MazeCreator::setInputMapSize()
{
	std::cout << "Choose map size (minimum 4) : ";
	std::cin >> mapSize;
	//return mapSize;
}

void MazeCreator::setInputNumExits()
{
	std::cout << "Choose number of Exits : ";
	std::cin >> numExits;
	//return numExits;
}


void MazeCreator::setInputFileName()
{
	std::cout << "What name would you like to save the file to? : ";
	//std::cin >> fileName;
	std::cin.get();
	std::getline(std::cin, fileName);
	std::cout << "File will be saved as " << fileName << ".txt" << '\n';
	//std::cout << fileName << '\n';
}

//Getters --
int MazeCreator::getMapSize()
{
	return mapSize;
}


int MazeCreator::getNumExits() {
	return numExits;
}

