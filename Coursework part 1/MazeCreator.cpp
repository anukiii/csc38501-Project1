#include <iostream>
#include <fstream>
#include "MazeCreator.h"
#include <random>
#include <vector>
#include "Cell.h"

void MazeCreator::generateMap(int mapSize, int numExits) {

	std::cout << '\n';

	std::vector<Cell> cellVector = drawMap();
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


void MazeCreator::printOnScreen(std::vector<Cell> cellVector) {
	std::vector<Cell>::iterator it;
	for (it = cellVector.begin(); it != cellVector.end(); it++) {
		std::cout << it->getCurrentChar();
	}
}

std::vector<Cell> MazeCreator::drawMap() {
	std::vector<Cell> vectorOfCells;
	Cell tempCell;
	int idCounter = -1; //So first id is 0;
	char currentTile;
	int centerPoint = 0;

	for (int y = 0; y < mapSize; y++) {//Y co-ord
		for (int x = 0; x < mapSize; x++) {//X co-ord
			idCounter++;
			tempCell.setMazeId(idCounter);
			tempCell.setXPos(x);
			tempCell.setYPos(y);
			currentTile = '.'; //default for tile in board;

			//outside walls
			currentTile = (y == 0 ? 'X' : currentTile);
			currentTile = (y == mapSize - 1 ? 'X' : currentTile);
			currentTile = (x == 0 ? 'X' : currentTile);
			currentTile = (x == mapSize - 1 ? 'X' : currentTile);
	
			//centerPoint
			centerPoint = (x == (mapSize / 2) && y == (mapSize / 2) ? idCounter : centerPoint);
	
			tempCell.setCurrentChar(currentTile);

			vectorOfCells.push_back(tempCell);
			tempCell.clearConnections();
		}
		idCounter++;
		tempCell.setMazeId(-1);
		tempCell.setXPos(-1);
		tempCell.setYPos(-1);
		tempCell.setCurrentChar('\n');
		vectorOfCells.push_back(tempCell);
	}

	//Once empty maze is made, generate maze using a modified recursive backtracking alg.
	vectorOfCells = mazingAlg(vectorOfCells,centerPoint);
	vectorOfCells = mapFixer(vectorOfCells,centerPoint);
	vectorOfCells = pathfinding(vectorOfCells, centerPoint);




	return vectorOfCells;
}


std::vector<Cell> MazeCreator::pathfinding(std::vector<Cell> vectorOfCells, int centerpoint) {

	std::vector<int> exitPos;
	for (int i = 0; i < vectorOfCells.size(); i++) {
		if (vectorOfCells.at(i).getCurrentChar() == 'E') {
			exitPos.push_back(i);
		}
	}
	
	int failsafe = 0;
	int currentId;
	int currentY;
	int currentX;
	int destinationX = vectorOfCells.at(centerpoint).getXpos();
	int destinationY = vectorOfCells.at(centerpoint).getYpos();
	int currentDistance;
	int direction;
	int tries;
	int tempId = 0;
	bool valid;
	bool best;
	

	std::vector<int> path;
	for (int i = 0; i < exitPos.size(); i++) {
		currentId = exitPos.at(i);
		currentX =vectorOfCells.at(currentId).getXpos();
		currentY = vectorOfCells.at(currentId).getYpos();
		currentDistance = abs(currentX-destinationX) + abs(currentY-destinationY);
		path.push_back(currentId);
		while (currentDistance  > 1 && failsafe<1000) {
			failsafe++;
			//
			tries = 0;
			best = false;
			direction =RNG(3);
			while (tries < 10 && !best) {
				//currentDistance = abs(currentX - destinationX) + abs(currentY - destinationY);
				direction = RNG(3);
				tries++;
				valid = false;
				
				switch (direction) {
				case 0://up
					tempId = currentId - (mapSize+1);
					if (tempId<0) {
						break;
					}
					else if (vectorOfCells.at(tempId).getCurrentChar() == 'X') {
						break;
					}
					valid = true;
					break;
				case 1://down
					tempId = currentId + mapSize+1;
					if (tempId > mapSize * mapSize) {
						break;
					}
					else if (vectorOfCells.at(tempId).getCurrentChar() == 'X' ) {
						break;
					}
					valid = true;
					break;
				case 2://left
					tempId = currentId -1;
					if (tempId<0) {
						break;
					}
					else if (vectorOfCells.at(tempId).getCurrentChar() == 'X') {
						break;
					}
					valid = true;
					break;
				case 3://right
					tempId = currentId +1;
					if (tempId > mapSize * mapSize) {
						break;
					}
					else if (vectorOfCells.at(tempId).getCurrentChar() == 'X') {
						break;
					}
					valid = true;
					break;
				}



				if (valid && currentDistance > abs(destinationX - vectorOfCells.at(tempId).getXpos()) + abs(destinationY - vectorOfCells.at(tempId).getYpos())) {
					
					currentId = tempId;
					path.push_back(currentId);
					currentX = vectorOfCells.at(currentId).getXpos();
					currentY = vectorOfCells.at(currentId).getYpos();
					currentDistance = abs(currentX - destinationX) + abs(currentY - destinationY);
					vectorOfCells.at(currentId).setCurrentChar('o');
					best = true;
				}
				else if (valid &&vectorOfCells.at(tempId).getCurrentChar() == 'o') {
					best = true;
					for (int i = 0; i < path.size(); i++) {
						best = (path.at(i) == tempId ? false : best);
					}
					currentDistance = (best ? 0 : currentDistance);
				}


			}
			if (!best && !path.empty()) {
				
				currentId = path.at(path.size() - 1);
				path.pop_back();
				currentX = vectorOfCells.at(currentId).getXpos();
				currentY = vectorOfCells.at(currentId).getYpos();
				currentDistance = abs(currentX - destinationX) + abs(currentY - destinationY);

			}
			 









			//currentDistance = abs(currentX - destinationX) + abs(currentY - destinationY);
		}






	}



	return vectorOfCells;
}



std::vector<Cell> MazeCreator::mapFixer(std::vector<Cell> vectorOfCells, int centerPoint) {
	char currentTile;
	//replace p withh blanks and . with walls, put in s and space around it
	for (int i = 0; i < vectorOfCells.size(); i++) {
		currentTile = '\n';




		currentTile = (vectorOfCells.at(i).getCurrentChar() == 'p' ? ' ' : currentTile);
		currentTile = (vectorOfCells.at(i).getCurrentChar() == '.' ? 'X' : currentTile);
		currentTile = (vectorOfCells.at(i).getCurrentChar() == 'X' ? 'X' : currentTile);
		currentTile = (vectorOfCells.at(i).getCurrentChar() == 'E' ? 'E' : currentTile);


		//Inner 3x3 blank, checks for range of distance of 1 unit in all directions of midpoint and makes it blank
		currentTile = ((mapSize / 2) - 1 <= vectorOfCells.at(i).getYpos() && vectorOfCells.at(i).getYpos() <= (mapSize / 2) + 1 && (mapSize / 2) - 1 <= vectorOfCells.at(i).getXpos() && vectorOfCells.at(i).getXpos() <= (mapSize / 2) + 1 ? ' ' : currentTile);

		currentTile = (vectorOfCells.at(i).getMazeId() == centerPoint ? 'S' : currentTile);
		vectorOfCells.at(i).setCurrentChar(currentTile);
	}
	return vectorOfCells;
}



//Method isn't great and is very long. can't find a way to split it into subfunctions but works at the moment.
//If time allows, I'll try optimize this function better also uses a lot of if statememnts for checking, idk how to change this
std::vector<Cell> MazeCreator::mazingAlg(std::vector<Cell> cellVector, int centerPoint) {
	
	std::vector<int>path;
	int currentId = centerPoint;
	int direction;
	int tempId;
	bool valid;
	bool backtrack;
	int tries = 0;
	int totalRuns =0;
	int exitCounter = 0;
	path.push_back(centerPoint);

	do {
		totalRuns++;
		valid = false;
		tries = 0;
		while (tries < 10 && !valid) {
			backtrack = true;
			tries++;
			direction = RNG(3);


			switch (direction) {

			case 0: // up - mapsize twice
				tempId = currentId - (mapSize +1);
				if (tempId < 0) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'p' || cellVector.at(tempId).getCurrentChar() == 'E') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						exitCounter++;
					}
					break;
				}
					//currentId = tempId;
					cellVector.at(currentId - (mapSize+1)).setCurrentChar('p');


				tempId -= mapSize +1;
				if (tempId < 0) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'p' || cellVector.at(tempId).getCurrentChar() == 'E') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						exitCounter++;
					}
					break;
				}

					for (int i = 0; i < path.size(); i++) {
						backtrack = (path.at(i) == tempId ? false : backtrack);
						
					}
				if (backtrack) {
					cellVector.at(currentId - (mapSize+1) * 2).setCurrentChar('p');
					currentId = tempId;
					path.push_back(currentId);
					valid = true;

				}

				
				break;


			case 1: //down +mapsize twice
				
				tempId = currentId + (mapSize + 1);
				if (tempId > mapSize*mapSize+mapSize) {
					break;
				}
				else if ( cellVector.at(tempId).getCurrentChar() == 'p' || cellVector.at(tempId).getCurrentChar() == 'E') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						exitCounter++;
					}
					break;
				}
					cellVector.at(currentId + (mapSize + 1)).setCurrentChar('p');


				tempId += mapSize + 1;
				if (tempId >mapSize*mapSize +mapSize) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'p' || cellVector.at(tempId).getCurrentChar() == 'E') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						exitCounter++;
					}
					break;
				}

					for (int i = 0; i < path.size(); i++) {
						backtrack = (path.at(i) == tempId ? false : backtrack);

					}

				if (backtrack) {
					cellVector.at(currentId + (mapSize + 1) * 2).setCurrentChar('p');
					currentId = tempId;
					path.push_back(currentId);
					valid = true;

				}

				break;

			case 2: //left -1 twice
				
				tempId = currentId - 1;
				if (tempId < 0) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'p' || cellVector.at(tempId).getCurrentChar() == 'E') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						exitCounter++;
					}
					break;
				}

					cellVector.at(currentId -1).setCurrentChar('p');
				


				tempId -=1;
				if (tempId < 0) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'p' || cellVector.at(tempId).getCurrentChar() == 'E') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						exitCounter++;
					}
					break;
				}

					for (int i = 0; i < path.size(); i++) {
						backtrack = (path.at(i) == tempId ? false : backtrack);

					}
				
				if (backtrack) {
					cellVector.at(currentId - 2).setCurrentChar('p');
					currentId = tempId;
					path.push_back(currentId);
					valid = true;

				}
				
				break;

			case 3://right +1 twice
				tempId = currentId + 1;
				if (tempId >mapSize *mapSize +mapSize) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'p' || cellVector.at(tempId).getCurrentChar() == 'E') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						exitCounter++;
					}
					break;
				}

					cellVector.at(currentId + 1).setCurrentChar('p');
				


				tempId += 1;
				if (tempId > mapSize*mapSize+mapSize) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'p'||cellVector.at(tempId).getCurrentChar()=='E') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						exitCounter++;
					}
					break;
				}
				

					for (int i = 0; i < path.size(); i++) {
						backtrack = (path.at(i) == tempId ? false : backtrack);

					}
				
				if (backtrack) {
					cellVector.at(currentId +2).setCurrentChar('p');
					currentId = tempId;
					path.push_back(currentId);
					valid = true;

				}



				break;
			}
		}

		if (!valid && !path.empty()) {
			currentId = path.at(path.size() - 1);
			path.pop_back();
		}


	} while (exitCounter < numExits||totalRuns < mapSize*mapSize/5);

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
		std::cout << "Choose number of Exits (less than size of map) : ";
		std::cin >> numExits;

		while (std::cin.fail()||numExits<1||numExits>=mapSize) {
			std::cout << "Error:Please insert an integer Value less than mapsize : " << std::endl;
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