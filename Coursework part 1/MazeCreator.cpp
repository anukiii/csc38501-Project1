#include <iostream>
#include <fstream>
#include "MazeCreator.h"
#include <random>
#include <vector>
#include "Cell.h"

void MazeCreator::generateMap(int mapSize, int numExits) {

	std::vector<int> exitPos;
	while ((int)exitPos.size() < numExits) {
		exitPos = allocateExits(numExits,exitPos);
		//exitPos.size();
		//breakout statement??
	}

	std::cout << '\n';

	std::vector<Cell> cellVector = drawMap(exitPos);
	printOnScreen(cellVector);
	int choice;
	std::cout << "\n\nPlease select one of the following options:\n1: Save Maze to .txt file\n2:Return to main menu\n3:Exit\n";
	std::cin >> choice;
	while (std::cin.fail() || choice < 1 || choice > 3) {
		std::cout << "Error:Please Type a valid option " << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "\n\nPlease select one of the following options:\n1: Save Maze to .txt file\n2:Return to main menu\n3:Exit\n";
		std::cin >> choice;
	}
	switch (choice) {
	case 1:
		drawToFile(cellVector);
		break;
	case 2:
		startMenu();
		break;
	case 3:
		std::cout << "Bye Bye";
		break;

	}
 }

std::vector<int> MazeCreator::allocateExits(int numExits, std::vector<int> exitPos) {
	for (int i = 0; i < numExits; i++) {
		exitPos.push_back(RNG(mapSize * 4)); // chooses possible exits	
	}
	//exitPos.; //removes duplicates
	int tempExit;
	int duplicates=0;
	for (int i = 0; i < exitPos.size(); i++) {
		tempExit = exitPos.at(i);
		for (int j = i + 1; j < exitPos.size(); j++) {
			duplicates = (tempExit == exitPos.at(j) ? duplicates + 1 : duplicates);
		}
	}
	
	if (duplicates > 0) {
		exitPos.clear(); //Duplicate has been found thus we must re-do;
	}


	return exitPos;
}

void MazeCreator::printOnScreen(std::vector<Cell> cellVector) {
	std::vector<Cell>::iterator it;
	for (it = cellVector.begin(); it != cellVector.end(); it++) {
		std::cout << it->getCurrentChar();
	}
}

std::vector<Cell> MazeCreator::drawMap(std::vector<int> exitPos) {
	std::vector<Cell> vectorOfCells;
	Cell tempCell;
	int idCounter = -1; //so first one is 0;
	char currentTile;
	int wallExitCounter =0;
	std::vector<int>::iterator exitIt;

	for (int y = 0; y < mapSize; y++) {//Y co-ord
		for (int x = 0; x < mapSize; x++) {//X co-ord
			idCounter++;
			tempCell.setMazeId(idCounter);
			tempCell.setXPos(x);
			tempCell.setYPos(y);
			currentTile = '.'; //default for tile in board;

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
			//Iterates through vector of Exits
			for (exitIt = exitPos.begin(); exitIt != exitPos.end(); exitIt++) {
				currentTile = (*exitIt == wallExitCounter ? 'E' : currentTile);
				*exitIt = (*exitIt == wallExitCounter ? -1 : *exitIt);//Sets it to -1 so it isn't checked again
			}

			tempCell.setCurrentChar(currentTile);

			vectorOfCells.push_back(tempCell);
			tempCell.clearConnections();
		}
		//idCounter--; //ignores walls
		tempCell.setMazeId(-1);
		tempCell.setXPos(-1);
		tempCell.setYPos(-1);
		tempCell.setCurrentChar('\n');
		vectorOfCells.push_back(tempCell);
	}

	vectorOfCells = binaryTree(vectorOfCells);
	for (int i = 0; i < vectorOfCells.size(); i++) {
		currentTile = (vectorOfCells.at(i).getCurrentChar() == '.' ? 'X' :vectorOfCells.at(i).getCurrentChar());
		vectorOfCells.at(i).setCurrentChar(currentTile);
	}

	return vectorOfCells;
}

std::vector<Cell> MazeCreator::binaryTree(std::vector<Cell> cellVector) {
	
	std::vector<int> visitedCells;
	int found = 0;//if exit is found will be equal to numExits
	int centerPointId = -1;//Where the S is;
	for (int i = 0; i < cellVector.size(); i++) {
		centerPointId = 200/*(cellVector.at(i).getCurrentChar() == 'S' ? cellVector.at(i).getMazeId():centerPointId)*/;
	}
	visitedCells.push_back(centerPointId);//start point
	int currentTileId = centerPointId;
	int direction; // 0 is N, 1 is E, 2 is S, 3 is W
	int addedToCurrnetId=0;
	int pathCounter=0;
	bool visited = false;
	int failsafe = 0;
	//untill exit is found
	while (found<numExits &&failsafe<1000) {
		
		pathCounter = 0;
		
		//Chooses a random direction and finds what that tile's ID would be.
		do {
			direction =RNG(3);
			addedToCurrnetId = (direction == 0 ? -mapSize: addedToCurrnetId);
			addedToCurrnetId = (direction == 1 ? 1 : addedToCurrnetId);
			addedToCurrnetId = (direction == 2 ? +mapSize : addedToCurrnetId);
			addedToCurrnetId = (direction == 3 ? -1 : addedToCurrnetId);
			pathCounter++;//checks if deadEnd
			//West by default
			visited = false;
			//Checks if the direction the cell wants to go is a wall or was already checked.
			for (int i = 0; i < visitedCells.size(); i++) {
				visited = (addedToCurrnetId + currentTileId < 0 || addedToCurrnetId + currentTileId>cellVector.size() ? true : visited);
				visited = (visited == true ||visitedCells.at(i) == currentTileId + addedToCurrnetId? true : visited);
				if (visited != true) {
					visited = (cellVector.at(currentTileId + addedToCurrnetId).getCurrentChar() == 'X' ? true : visited);
				}
				//std::cout << visited << '\n';
				

			}
			if (pathCounter == 10) {
			/*
				
				while (visited) {
					direction = RNG(3);
					addedToCurrnetId = (direction == 0 ? -mapSize : addedToCurrnetId);
					addedToCurrnetId = (direction == 1 ? 1 : addedToCurrnetId);
					addedToCurrnetId = (direction == 2 ? +mapSize : addedToCurrnetId);
					addedToCurrnetId = (direction == 3 ? -1 : addedToCurrnetId);
					if (addedToCurrnetId + currentTileId > 0 || addedToCurrnetId + currentTileId < cellVector.size()) {
						if (cellVector.at(addedToCurrnetId + currentTileId).getCurrentChar() != 'X') {
							visited = false;
						}

					}
				
				}
				*/

				currentTileId = visitedCells.at(visitedCells.size()-1);
				addedToCurrnetId = 0;
				visited = false;

				if (currentTileId == centerPointId) {
					visitedCells.clear();
				}
				//isited = false;
			
			}
			
		} while (visited);//10 is the breakout, in that case the backtracking will start
		
		if (pathCounter<10) {
			currentTileId += addedToCurrnetId;
			visitedCells.push_back(currentTileId);
			
			cellVector.at(currentTileId).setCurrentChar(' ');

			
			bool foundChecker = false;
			foundChecker = (cellVector.at(currentTileId - 1).getCurrentChar() == 'E' ? true : foundChecker);
			foundChecker = (cellVector.at(currentTileId + 1).getCurrentChar() == 'E' ? true: foundChecker);
			foundChecker = (cellVector.at(currentTileId - mapSize).getCurrentChar() == 'E' ? true : foundChecker);
			foundChecker = (cellVector.at(currentTileId + mapSize).getCurrentChar() == 'E' ? true : foundChecker);
			found = (foundChecker ? found + 1 : found);
			//if (foundChecker) {
				//currentTileId = centerPointId;
			//}
		}

		
		//cellVector.at(currentTileId).setCurrentChar('p');
		failsafe++;
		

		
		
		
		


	}


	std::cout << failsafe;

	return cellVector;
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



	;
}

void MazeCreator::setInputNumExits()
{
		std::cout << "Choose number of Exits : ";
		std::cin >> numExits;

		while (std::cin.fail()||numExits<1) {
			std::cout << "Error:Please insert an integer Value : " << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> numExits;
		}


}


void MazeCreator::setInputFileName()
{
	std::cout << "What's the File Name? (no .txt needed) : ";
	std::cin.get();
	std::getline(std::cin, fileName);
	fileName += ".txt";//saves it as a text file


}

//Getters --
int MazeCreator::getMapSize()
{
	return mapSize;
}


int MazeCreator::getNumExits() {
	return numExits;
}

void MazeCreator::drawToFile(std::vector<Cell> cellVector)
{
	setInputFileName();
	std::ofstream file(fileName);
	std::vector<Cell>::iterator it;
	for (it = cellVector.begin(); it != cellVector.end();it++) {
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

void MazeCreator::readFromFile() {

	setInputFileName();
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::string tempLine;
		while (std::getline(file, tempLine)) {
			std::cout << tempLine << '\n';
		}
		file.close();
	}
	else {
		std::cout << "Invalid file name, Please check if file is correctly named or present\nReturning you to main menu";

	}
	std::cout << "\nPress ENTER to return to main menu";
	std::cin.ignore();
	startMenu();


}




void MazeCreator::startMenu() {
	int choice;
	std::cout << "Please select one of the following options\n1:New Maze\n2:Load Maze \n3:Exit\n";
	std::cin >> choice;
	while (std::cin.fail() || choice < 1 || choice > 3) {
		std::cout << "Error:Please Type a valid option " << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please select one of the following options\n1:New Maze\n2:Load Maze \n3:Exit\n";
		std::cin >> choice;
	}

	switch (choice) {
	case 1:
		setInputMapSize();
		setInputNumExits();
		generateMap(mapSize, numExits);
		break;
	case 2:
		readFromFile();
		break;
	case 3:
		std::cout << "Bye Bye";
		break;

	}


}