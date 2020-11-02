#include <iostream>
#include <fstream>
#include "MazeCreator.h"
#include <random>
#include <list>
#include "Cell.h"

int MazeCreator::generateMap(int mapSize, int numExits) {
	std::list<int> exitPos;
	while ((int)exitPos.size() < numExits) {
		exitPos = allocateExits(numExits,exitPos);
		exitPos.size();
		//breakout statement??
	}

	std::cout << '\n';

	std::list<Cell> cellList = drawMap(exitPos);
	printOnScreen(cellList);
	drawToFile(fileName + ".txt",cellList);


	return 0;
}

std::list<int> MazeCreator::allocateExits(int numExits, std::list<int> exitPos) {
	for (int i = 0; i < numExits; i++) {
		exitPos.push_back(RNG(mapSize * 4)); // chooses possible exits	
	}
	exitPos.unique(); //removes duplicates
	return exitPos;
}

void MazeCreator::printOnScreen(std::list<Cell> cellList) {
	std::list<Cell>::iterator it;
	for (it = cellList.begin(); it != cellList.end(); it++) {
		std::cout << it->getCurrentChar();
	}
}

std::list<Cell> MazeCreator::drawMap(std::list<int> exitPos) {
	std::list<Cell> listOfCells;
	Cell tempCell;
	int idCounter = 0;
	char currentTile;
	int wallExitCounter =0;
	std::list<int>::iterator exitIt;
	for (int y = 0; y < mapSize; y++) {//Y choord
		for (int x = 0; x < mapSize; x++) {//X choord
			idCounter++;
			tempCell.setMazeId(idCounter);
			tempCell.setXPos(x);
			tempCell.setYPos(y);
			currentTile = 'p'; //default for tile;

			//Inner 3x3 blank, checks for range of distance of 1 unit in all directions of midpoint and makes it blank			
			currentTile = ((mapSize / 2) - 1 <= y && y <= (mapSize / 2) + 1 && (mapSize / 2) - 1 <= x && x <= (mapSize / 2) + 1 ? ' ' : currentTile);

			//outside walls
			currentTile = (y == 0 ? 'X' : currentTile);
			currentTile = (y == mapSize - 1 ? 'X' : currentTile);
			currentTile = (x == 0 ? 'X' : currentTile);
			currentTile = (x == mapSize - 1 ? 'X' : currentTile);

			//centerpoint
			currentTile = (x == (mapSize / 2) && y == (mapSize / 2) ? 'S' : currentTile);

			//Exits
			wallExitCounter = (currentTile == 'X' ? wallExitCounter + 1 : wallExitCounter);
			//Iterates through list of Exits
			for (exitIt = exitPos.begin(); exitIt != exitPos.end(); exitIt++) {
				currentTile = (*exitIt == wallExitCounter ? 'E' : currentTile);
				*exitIt = (*exitIt == wallExitCounter ? -1 : *exitIt);//Sets it to -1 so it isn't checked again
			}
			
			tempCell.setCurrentChar(currentTile);

			listOfCells.push_back(tempCell);
		}
		tempCell.setMazeId(-1);
		tempCell.setXPos(-1);
		tempCell.setYPos(-1);
		tempCell.setCurrentChar('\n');
		listOfCells.push_back(tempCell);
	}


	return listOfCells;
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

void MazeCreator::drawToFile(std::string fileNameComplete, std::list<Cell> cellList)
{
	std::ofstream file(fileNameComplete);
	std::list<Cell>::iterator it;
	for (it = cellList.begin(); it != cellList.end();it++) {
		file << it->getCurrentChar();
	}

}

