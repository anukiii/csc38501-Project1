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
	int choice;
	std::cout << "\n\nPlease select one of the following options:\n1: Save Maze to .txt file\n2:Return to main menu\nExit\n";
	std::cin >> choice;
	while (std::cin.fail() || choice < 1 || choice > 3) {
		std::cout << "Error:Please Type a valid option " << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "\n\nPlease select one of the following options:\n1: Save Maze to .txt file\n2:Return to main menu\nExit\n";
		std::cin >> choice;
	}
	switch (choice) {
	case 1:
		drawToFile(cellList);
		break;
	case 2:
		startMenu();
		break;
	case 3:
		std::cout << "Bye Bye";
		break;

	}






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

		while (std::cin.fail()|| mapSize<4) {
			std::cout << "Error:Please insert an integer Value less than 4: " << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> mapSize;
		}

		//return mapSize;

	;
}

void MazeCreator::setInputNumExits()
{
	//do {
		std::cout << "Choose number of Exits : ";
		std::cin >> numExits;

		while (std::cin.fail()||numExits<1) {
			std::cout << "Error:Please insert an integer Value : " << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> numExits;
		}


//	}while
}


void MazeCreator::setInputFileName()
{
	std::cout << "What name would you like to save the file to? : ";
	std::cin.get();
	std::getline(std::cin, fileName);
	fileName += ".txt";//saves it as a text file
	std::cout << "File will be saved as " << fileName << ".txt" << '\n\n';

}

//Getters --
int MazeCreator::getMapSize()
{
	return mapSize;
}


int MazeCreator::getNumExits() {
	return numExits;
}

void MazeCreator::drawToFile(std::list<Cell> cellList)
{
	setInputFileName();
	std::ofstream file(fileName);
	std::list<Cell>::iterator it;
	for (it = cellList.begin(); it != cellList.end();it++) {
		file << it->getCurrentChar();
	}
	file.close();

	int choice;
	std::cout << "Please select one of the following options\n1:Return to main menu\n2:Exit\n";
	std::cin >> choice;
	while (std::cin.fail() || choice < 1 || choice >2) {
		std::cout << "Error:Please Type a valid option " << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please select one of the following options\n1:Return to main menu\n2:Exit\n";
		std::cin >> choice;
	}

	switch (choice) {
	case 1:
		startMenu();
		break;
	case 2:
		std::cout << "Bye Bye\n";
		break;


	}

}


void MazeCreator::startMenu() {
	int choice;
	std::cout << "Please select one of the following options\n1: New Maze\n2:Load Maze \n3:Exit";
	std::cin >> choice;
	while (std::cin.fail() || choice < 1 || choice > 3) {
		std::cout << "Error:Please Type a valid option " << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please select one of the following options\n1: New Maze\n2:Load Maze \n3:Exit\n";
		std::cin >> choice;
	}

	switch (choice) {
	case 1:
		setInputMapSize();
		setInputNumExits();
		generateMap(mapSize, numExits);
		break;
	case 2:
		std::cout << "This feature has to still be implemented \n\n";
		startMenu();
		break;
	case 3:
		std::cout << "Bye Bye";
		break;

	}


}