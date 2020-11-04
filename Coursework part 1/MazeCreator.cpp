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
	int idCounter = -1; //So first id is 0;
	char currentTile;
	int wallExitCounter =0;
	std::vector<int>::iterator exitIt;
	int modValue = mapSize%2;
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
	

	/*
	
			//Inner 3x3 blank, checks for range of distance of 1 unit in all directions of midpoint and makes it blank
			currentTile = ((mapSize / 2) - 1 <= y && y <= (mapSize / 2) + 1 && (mapSize / 2) - 1 <= x && x <= (mapSize / 2) + 1 ? ' ' : currentTile);

			//centerpoint
			currentTile = (x == (mapSize / 2) && y == (mapSize / 2) ? 'S' : currentTile);

			//Exits
			wallExitCounter = (currentTile == 'X' ? wallExitCounter + 1 : wallExitCounter);
			//Iterates through vector of Exits
			for (exitIt = exitPos.begin(); exitIt != exitPos.end(); exitIt++) {
				currentTile = (*exitIt == wallExitCounter ? 'E' : currentTile);
				*exitIt = (*exitIt == wallExitCounter ? -1 : *exitIt);//Sets it to -1 so it isn't checked again
			}
		*/	

			//all the rest, generation alg is applied
			
			/*
			if (currentTile=='S') {
				tempCell.addConnection(idCounter - 2);
				tempCell.addConnection(idCounter + 2);
				tempCell.addConnection(idCounter - mapSize * 2);
				tempCell.addConnection(idCounter + mapSize * 2);
			}

			
			if (currentTile == '.' && x>=2 && x%2==modValue) {
				tempCell.addConnection(idCounter-2);//2 blocks to the left

			}
			if (currentTile == '.' && x<= mapSize*mapSize - 2&& x%2==modValue) {
				tempCell.addConnection(idCounter + 2);//2 blocks to the right
			}
			
			if (currentTile == '.' && y > mapSize*2&&y%2 ==1) {
				tempCell.addConnection(idCounter - mapSize*2); //two rows up
			}
			if (currentTile == '.' && y <mapSize*mapSize- (2*mapSize)&& y%2==1) {
				tempCell.addConnection(idCounter + mapSize*2);//two rows down
			}
			*/
			//currentTile = (RNG(2) == 1 && currentTile == '.' ? ' ' : currentTile);
			//currentTile = (currentTile == '.' ? 'X' : currentTile);
			
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



	//Once empty maze is made, generate inner walls with binary tree

	vectorOfCells = mazingAlg(vectorOfCells,centerPoint);

	return vectorOfCells;
}

std::vector<Cell> MazeCreator::mazingAlg(std::vector<Cell> cellVector, int centerPoint) {
	
	std::vector<int>path;
	int currentId = centerPoint;
	int direction;
	int tempId;
	bool valid;
	bool backtrack;
	int tries = 0;;
	path.push_back(centerPoint);

	do {

		valid = false;
		tries = 0;
		while (tries < 10 && !valid) {
			backtrack = true;
			tries++;
			direction = RNG(1);


			switch (direction) {

			case 0: // up - mapsize twice
				tempId = currentId - (mapSize +1);
				if (tempId < 0) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X'|| cellVector.at(tempId).getCurrentChar() == 'p') {
					break;
				}
				else {
					//currentId = tempId;
					cellVector.at(currentId - (mapSize+1)).setCurrentChar('p');
				}


				tempId -= mapSize +1;
				if (tempId < 0) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == ('X')||cellVector.at(tempId).getCurrentChar() == 'p') {
					break;
				}
				else {

					for (int i = 0; i < path.size(); i++) {
						backtrack = (path.at(i) == tempId ? false : backtrack);
						
					}
				}
				if (backtrack) {
					//cellVector.at(currentId - (mapSize+1)).setCurrentChar('p');
					cellVector.at(currentId - (mapSize+1) * 2).setCurrentChar('p');
					currentId = tempId;
					path.push_back(currentId);
					valid = true;

				}

				
				break;


			case 1: //down +mapsize twice
				
				tempId = currentId + (mapSize + 1);
				if (tempId > mapSize*mapSize) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X'|| cellVector.at(tempId).getCurrentChar() == 'p') {
					break;
				}
				else {
					//currentId = tempId;
					cellVector.at(currentId + (mapSize + 1)).setCurrentChar('p');
				}


				tempId += mapSize + 1;
				if (tempId >mapSize*mapSize +mapSize) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X'||cellVector.at(tempId).getCurrentChar() == 'p') {
					break;
				}
				else {

					for (int i = 0; i < path.size(); i++) {
						backtrack = (path.at(i) == tempId ? false : backtrack);

					}
					std::cout << backtrack << '\n';
				}
				if (backtrack) {
					//cellVector.at(currentId - (mapSize+1)).setCurrentChar('p');
					cellVector.at(currentId + (mapSize + 1) * 2).setCurrentChar('p');
					currentId = tempId;
					path.push_back(currentId);
					valid = true;

				}
				






				break;

			case 2: //left -1 twice
				break;

			case 3://right +1 twice
				break;
			}
		}
		if (!valid && !path.empty()) {
			currentId = path.at(path.size() - 1);
			path.pop_back();
			std::cout << "Pussy talented it do cartwheels: " << path.size() << '\n';

		}


	} while (currentId != centerPoint);



	/*
	char tempChar;
	std::vector<int> exitIds;
	std::vector<int> wallIds;
	std::vector<int>path;

	int currentId;
	int startId = 0;//for recursive backtracking
	//int found = 0; //used to exit if exit found.

	

	
	for (int i = 0; i < cellVector.size(); i++) {
		tempChar = (!cellVector.at(i).getConnections().empty() && cellVector.at(i).getCurrentChar() == '.' ? '|' : cellVector.at(i).getCurrentChar());
		cellVector.at(i).setCurrentChar(tempChar);
		if (cellVector.at(i).getCurrentChar() == 'E') {
			exitIds.push_back(cellVector.at(i).getMazeId()); // used for checking exits later
		}
		else if (cellVector.at(i).getCurrentChar() == 'X') {
			wallIds.push_back(cellVector.at(i).getMazeId());
		}
		else if (cellVector.at(i).getCurrentChar() == 'S') {
			startId = cellVector.at(i).getMazeId();
			
			//std::cout << i << ' ' << currentId << ' ' << cellVector.at(i).getConnections().size();
		}
	}
	
	currentId = startId;
	int tries;
	int numConnections;
	int tempId;
	int direction;
	bool found;
	int halfstep;
	//while (found < numExits) {
	/*
	do {
		tries = 0;//reset treis
		found = true;
		
		
		//if (cellVector.at(currentId).getConnections().empty()) {
			
		
		
		do {
			tries++;
			numConnections = cellVector.at(currentId).getConnections().size();

			direction = RNG(numConnections-1); //since RNG starts form 0
			std::cout << cellVector.at(currentId).getConnections().size()<<' '<<direction << '\n';
			tempId = cellVector.at(currentId).getConnections().at(direction);
			//halfstep = (tempId-currentId) / 2;
			
			//for (int i = 0; i < 2; i++) {
				//currentId += halfstep;
			
			for (int i = 0; i < path.size(); i++) {
				if (path.at(i) == tempId) {
					found = false;
				}
			}

			if (cellVector.at(tempId).getCurrentChar() == 'X') {
				found = false;
				}
			//}
			//options are +2, -2, +mapsize*2 -mapsize*2
			std::cout << found << '\n';
		} while (tries < 10 && !found);


			if (tries == 10 && !path.empty()) {
				currentId = path.at(path.size() - 1);
				path.pop_back();
				std::cout << "no path found"<<'\n';
			}
			else if (found) {
				currentId = tempId;
				cellVector.at(currentId).setCurrentChar('p');
				path.push_back(currentId);
				std::cout << "path found"<<'\n';
			}


		


	} while (currentId != startId);
		*/
		
		/*


		switch (direction)
		{
		case 0 : //go North
			if (currentId - mapSize > 0) {
				if (cellVector.at(currentId - mapSize).getCurrentChar() != 'X') {
					if (cellVector.at(currentId - mapSize).getCurrentChar() == 'E') {
						found++;
					}
					else {
						currentId += mapSize;
						cellVector.at(currentId).setCurrentChar('p');
					}
				}
				else {
					//currentId = path.at(path.size() - 1);
					//path.pop_back();
				}
			}
			else {
				//currentId = path.at(path.size() - 1);
				//path.pop_back();
			}
			if (currentId - mapSize*2 > 0) {
				if (cellVector.at(currentId - mapSize*2).getCurrentChar() != 'X') {
					if (cellVector.at(currentId - mapSize*2).getCurrentChar() == 'E') {
						found++;

					}
					else {
						cellVector.at(currentId).setCurrentChar('p');
					}
				}
				else {
					currentId = path.at(path.size() - 1);
					path.pop_back();
				}
			}
			else {
				currentId = path.at(path.size() - 1);
				path.pop_back();
			}
		


			break;
		}
		//up

		//down

		//left

		//right

		}
		*/

	

	





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