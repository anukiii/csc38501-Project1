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
	std::cout << "\n\nPlease select one of the following options:\n1:Save empty Maze to .txt file\n2:Run Maze\n3:Return to main menu\n4:Exit\n";
	std::cin >> choice;
	while (std::cin.fail() || choice < 1 || choice > 4) {
		std::cout << "Error:Please Type a valid option " << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "\n\nPlease select one of the following options:\n1:Save Maze to .txt file\n2:Run Maze\n3:Return to main menu\n4:Exit\n";
		std::cin >> choice;
	}
	switch (choice) {
	case 1:
		drawToFile(cellVector);
		break;
	case 2:
		runMaze(cellVector);
		break;
	
	case 3:
		startMenu();
		break;
	case 4:
		std::cout << "Bye Bye";
		break;

	}
 }


void MazeCreator::statistics() {
	std::vector<Cell> VectorOfCells;
	setInputMapSize();				
	setInputNumberPlayers();			//Change these to ask different stuff
	std::cout << '\n';
	int maxMapSize = mapSize;
	int maxNumExits = numExits;
	double averagePathSize;
	double avergageCurrentPathSize;
	for (int map = 5; map <= maxMapSize; map++) { //Min mapSize of 4
		for (int pl = 1; pl <= maxNumExits; pl++) { //Min 1 player
			mapSize = map;
			numExits = pl;
			averagePathSize = 0;
			for(int j=0;j<100;j++){
				avergageCurrentPathSize=0;
				std::vector<Cell> cellVector = drawMap();

				for (int i = 0; i < listofPlayers.size(); i++) {
					avergageCurrentPathSize += listofPlayers.at(i).getPath().size();
				}
				//std::cout << "averageCurrentPathSize = " << avergageCurrentPathSize << '\n';
			averagePathSize += avergageCurrentPathSize / listofPlayers.size();
			listofPlayers.clear();
			}
			//averagePathSize = avergageCurrentPathSize;
			
			std::cout << "For a mapsize of " << mapSize << " with " << numExits << " players, player had to do " << averagePathSize/100 << " moves to find the exit\n\n";
			
		}


	}


}




void MazeCreator::runMaze(std::vector<Cell> vectorOfCells) {

	for (int i = 0; i < listofPlayers.size(); i++) {
		//std::cout << "Player's ID is" << listofPlayers.at(i).getPlayerId() << "|| and their current position is " << listofPlayers.at(i).getCellId() << "|| and the size of their path is " << listofPlayers.at(i).getPath().size() << '\n';
		vectorOfCells.at(listofPlayers.at(i).getCellId()).setCurrentChar(' ');
		listofPlayers.at(i).advancePath();
		if (vectorOfCells.at(listofPlayers.at(i).getCellId()).getCurrentChar() != 'p') {
			vectorOfCells.at(listofPlayers.at(i).getCellId()).setCurrentChar('p');

		}
	}
		//std::cout << vectorOfCells.at(listofPlayers.at(0).getCellId()).getFcost() << '\n';
	
	
	printOnScreen(vectorOfCells);
	int choice;
	std::cout << "\n1:Continue to next turn\n2:Return to main menu\n3:Exit\n";
	std::cin >> choice;
	while (std::cin.fail() || choice < 1 || choice > 3) {
		std::cout << "Error:Please Type a valid option " << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "\n\nPlease select one of the following options:\n1:Continue to next turn\n2 : Return to main menu\n3 : Exit\n";
	}

	switch (choice) {

	case 1:
		runMaze(vectorOfCells);
		break;
	case 2:
		startMenu();
		break;
	case 3:
		std::cout << "Bye bye";
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
	//vectorOfCells = pathfinding(vectorOfCells, centerPoint);
	//std::cout << "Size of listOfPlayers vector : " << listofPlayers.size() << '\n';

	for (int i = 0; i < listofPlayers.size(); i++) {
		//std::cout << "StartPoint for this one is : " << listofPlayers.at(i).getCellId()<<'\n';
		listofPlayers.at(i).pathFinding(vectorOfCells, centerPoint, mapSize);
		//	std::cout << "Size of player path after : " << listofPlayers.at(i).getPath().size()<<'\n';
	}




	return vectorOfCells;
}


void MazeCreator::addPlayer(int StartCellId)
{
	//std::cout << "Player Being Added\n";
	Player p;
	p.setCellId(StartCellId);
	p.setPlayerId(listofPlayers.size());
	listofPlayers.push_back(p);

}


std::vector<int> MazeCreator::findExits(std::vector<Cell> vectorOfCells) {
	std::vector<int> exitPos;
	for (int i = 0; i < vectorOfCells.size(); i++) {
		if (vectorOfCells.at(i).getCurrentChar() == 'E') {
			exitPos.push_back(i);
		}
	}

	return exitPos;
}


bool MazeCreator::validPath(int direction, int tempId, int currentId,std::vector<Cell> vectorOfCells) {
	switch (direction) {
	case 0://up
		tempId = currentId - (mapSize + 1);
		if (tempId < 0) {
			break;
		}
		else if (vectorOfCells.at(tempId).getCurrentChar() == 'X') {
			break;
		}
		return true;
		break;
	case 1://down
		tempId = currentId + mapSize + 1;
		if (tempId > mapSize * mapSize) {
			break;
		}
		else if (vectorOfCells.at(tempId).getCurrentChar() == 'X') {
			break;
		}
		return  true;
		break;
	case 2://left
		tempId = currentId - 1;
		if (tempId < 0) {
			break;
		}
		else if (vectorOfCells.at(tempId).getCurrentChar() == 'X') {
			break;
		}
		return  true;
		break;
	case 3://right
		tempId = currentId + 1;
		if (tempId > mapSize * mapSize) {
			break;
		}
		else if (vectorOfCells.at(tempId).getCurrentChar() == 'X') {
			break;
		}
		return true;
		break;
	}
	return false;
}



std::vector<Cell> MazeCreator::mapFixer(std::vector<Cell> vectorOfCells, int centerPoint) {
	char currentTile;
	//replace p withh blanks and . with walls, put in s and space around it
	for (int i = 0; i < vectorOfCells.size(); i++) {
		currentTile = '\n';




		currentTile = (vectorOfCells.at(i).getCurrentChar() == '-' ? ' ' : currentTile);
		currentTile = (vectorOfCells.at(i).getCurrentChar() == '.' ? 'X' : currentTile);
		currentTile = (vectorOfCells.at(i).getCurrentChar() == 'X' ? 'X' : currentTile);
		currentTile = (vectorOfCells.at(i).getCurrentChar() == 'E' ? 'E' : currentTile);
		currentTile = (vectorOfCells.at(i).getCurrentChar() == 'P' ? 'P' : currentTile);


		//Inner 3x3 blank, checks for range of distance of 1 unit in all directions of midpoint and makes it blank
		currentTile = ((mapSize / 2) - 1 <= vectorOfCells.at(i).getYpos() && vectorOfCells.at(i).getYpos() <= (mapSize / 2) + 1 && (mapSize / 2) - 1 <= vectorOfCells.at(i).getXpos() && vectorOfCells.at(i).getXpos() <= (mapSize / 2) + 1 ? ' ' : currentTile);
		currentTile = (vectorOfCells.at(i).getMazeId() == centerPoint ? 'F' : currentTile);
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
				else if (cellVector.at(tempId).getCurrentChar() == '-' || cellVector.at(tempId).getCurrentChar() == 'E'|| cellVector.at(tempId).getCurrentChar() == 'P') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						cellVector.at(tempId + (mapSize + 1)).setCurrentChar('P');
						addPlayer(tempId + (mapSize + 1));

						exitCounter++;
					}
					break;
				}
				
					//currentId = tempId;
					cellVector.at(currentId - (mapSize + 1)).setCurrentChar('-');

				tempId -= (mapSize +1);
				if (tempId < 0) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == '-' || cellVector.at(tempId).getCurrentChar() == 'E'|| cellVector.at(tempId).getCurrentChar() == 'P') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						cellVector.at(tempId +(mapSize + 1)).setCurrentChar('P');
						addPlayer(tempId + mapSize + 1);
						exitCounter++;
					}
					break;
				}

					for (int i = 0; i < path.size(); i++) {
						backtrack = (path.at(i) == tempId ? false : backtrack);
						
					}
				if (backtrack) {
					cellVector.at(currentId - (mapSize+1) * 2).setCurrentChar('-');
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
				else if ( cellVector.at(tempId).getCurrentChar() == '-' || cellVector.at(tempId).getCurrentChar() == 'E'|| cellVector.at(tempId).getCurrentChar() == 'P') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						cellVector.at(tempId - (mapSize + 1)).setCurrentChar('P');
						addPlayer(tempId - (mapSize + 1));
						exitCounter++;
					}
					break;
				}
					cellVector.at(currentId + (mapSize + 1)).setCurrentChar('-');


				tempId += mapSize + 1;
				if (tempId >mapSize*mapSize +mapSize) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == '-' || cellVector.at(tempId).getCurrentChar() == 'E'|| cellVector.at(tempId).getCurrentChar() == 'P') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						cellVector.at(tempId - (mapSize + 1)).setCurrentChar('P');
						addPlayer(tempId - (mapSize + 1));
						exitCounter++;
					}
					break;
				}

					for (int i = 0; i < path.size(); i++) {
						backtrack = (path.at(i) == tempId ? false : backtrack);

					}

				if (backtrack) {
					cellVector.at(currentId + (mapSize + 1) * 2).setCurrentChar('-');
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
				else if (cellVector.at(tempId).getCurrentChar() == '-' || cellVector.at(tempId).getCurrentChar() == 'E'|| cellVector.at(tempId).getCurrentChar() == 'P') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						cellVector.at(tempId +1 ).setCurrentChar('P');
						addPlayer(tempId + 1);
						exitCounter++;
					}
					break;
				}

					cellVector.at(currentId -1).setCurrentChar('-');
				


				tempId -=1;
				if (tempId < 0) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == '-' || cellVector.at(tempId).getCurrentChar() == 'E'|| cellVector.at(tempId).getCurrentChar() == 'P') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						cellVector.at(tempId + 1).setCurrentChar('P');
						addPlayer(tempId + 1);
						exitCounter++;
					}
					break;
				}

					for (int i = 0; i < path.size(); i++) {
						backtrack = (path.at(i) == tempId ? false : backtrack);

					}
				
				if (backtrack) {
					cellVector.at(currentId - 2).setCurrentChar('-');
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
				else if (cellVector.at(tempId).getCurrentChar() == '-' || cellVector.at(tempId).getCurrentChar() == 'E'|| cellVector.at(tempId).getCurrentChar() == 'P') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						cellVector.at(tempId - 1).setCurrentChar('P');
						addPlayer(tempId - 1);
						exitCounter++;
					}
					break;
				}

					cellVector.at(currentId + 1).setCurrentChar('-');
				


				tempId += 1;
				if (tempId > mapSize*mapSize+mapSize) {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == '-'||cellVector.at(tempId).getCurrentChar()=='E'|| cellVector.at(tempId).getCurrentChar() == 'P') {
					break;
				}
				else if (cellVector.at(tempId).getCurrentChar() == 'X') {
					if (exitCounter < numExits) {
						cellVector.at(tempId).setCurrentChar('E');
						cellVector.at(tempId - 1).setCurrentChar('P');
						addPlayer(tempId - 1);
						exitCounter++;
					}
					break;
				}
				

					for (int i = 0; i < path.size(); i++) {
						backtrack = (path.at(i) == tempId ? false : backtrack);

					}
				
				if (backtrack) {
					cellVector.at(currentId +2).setCurrentChar('-');
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
	
		std::cout << "Choose map size (minimum 5, maximum 100) : ";
		std::cin >> mapSize;

		while (std::cin.fail()|| mapSize<5 || mapSize>100) {
			std::cout << "Error:Please exter a valid integer value: " << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> mapSize;
		}



	;
}

void MazeCreator::setInputNumberPlayers()
{
		std::cout << "Choose number of players (less than size of map) : ";
		std::cin >> numExits;//Just one variable as its the same, one exit per player

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

//using file name, translates the text into the 
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

//Start menu user selection
void MazeCreator::startMenu() {
	int choice;
	std::cout << "Please select one of the following options\n1:New Maze\n2:Load Maze \n3:Generate Maze info\n4:Exit\n";
	std::cin >> choice;
	while (std::cin.fail() || choice < 1 || choice > 3) {
		std::cout << "Error:Please Type a valid option " << std::endl;
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cout << "Please select one of the following options\n1:New Maze\n2:Load Maze \n3:Generate Maze info\n4:Exit\n";
		std::cin >> choice;
	}

	listofPlayers.clear();
	switch (choice) {
	case 1:
		setInputMapSize();
		setInputNumberPlayers();
		generateMap(mapSize, numExits);
		break;
	case 2:
		readFromFile();
		break;
	case 3:
		statistics();
		break;
	
	case 4:
		std::cout << "Bye Bye";
		break;

	}


}