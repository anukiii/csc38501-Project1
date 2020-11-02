#include <iostream>
#include <fstream>
#include "MazeCreator.h"
#include <random>
#include <list>
#include "Cell.h"

int MazeCreator::generateMap(int mapSize, int numExits) {
	std::list<int> exitPos;
	std::cout << numExits << '\n';
	std::cout << mapSize << '\n';
	while ((int)exitPos.size() < numExits) {
		exitPos = allocateExits(numExits,exitPos);
		exitPos.size();
		//breakout statement??
	}


	drawToFile(fileName + ".txt",exitPos);


	return 0;
}

std::list<int> MazeCreator::allocateExits(int numExits, std::list<int> exitPos) {
	for (int i = 0; i < numExits; i++) {
		exitPos.push_back(RNG(mapSize * 4)); // chooses possible exits	
	}
	exitPos.unique(); //removes duplicates
	return exitPos;
}


std::list<Cell> MazeCreator::drawMap(std::list<int> exitPos) {
	std::list<Cell> listOfCells;
	Cell tempCell;
	int idCounter = 0;
	char currentTile;
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



			tempCell.setCurrentChar(currentTile);

			listOfCells.push_back(tempCell);
		}
		tempCell.setMazeId(-1);
		tempCell.setXPos(-1);
		tempCell.setYPos(-1);
		tempCell.setCurrentChar('n');
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

void MazeCreator::drawToFile(std::string fileNameComplete, std::list<int> exitPos)
{
	std::ofstream file(fileNameComplete);
	int xCoord = 0;
	int yCoord = 0;
	int wallCounter = 0;//where to put exits
	char currentTile;
	//Map is drawn in Rows, starting top left and going down
	for (int i = 0; i < mapSize; i++) { //vertical, AKA Y axis
		for (int j = 0; j < mapSize; j++) {//horizontal, AKA X AXIS
			currentTile = 'p';

			//ALGORITHM GOES HERE


			//Inner 3x3 blank, checks for range of distance of 1 unit in all directions of midpoint and makes it blank			
			currentTile = ((mapSize / 2) - 1 <= i && i <= (mapSize / 2) + 1 && (mapSize / 2) - 1 <= j && j <= (mapSize / 2) + 1 ? ' ' : currentTile);



			//outside walls
			currentTile = (i == 0 ? 'X' : currentTile);
			currentTile = (i == mapSize - 1 ? 'X' : currentTile);
			currentTile = (j == 0 ? 'X' : currentTile);
			currentTile = (j == mapSize - 1 ? 'X' : currentTile);

			//centerpoint
			currentTile = (j == (mapSize / 2) && i == (mapSize / 2) ? 'S' : currentTile);




			file << currentTile;

			xCoord++;//go down a row
		}
		file << '\n';
		yCoord++;//next collumn
	}

}

