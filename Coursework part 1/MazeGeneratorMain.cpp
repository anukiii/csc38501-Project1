#include "MazeGeneratorMain.h"
#include"MazeCreator.h"
#include <iostream>

int main() {
	MazeCreator m;
	//user input for size & exits
	m.setInputMapSize();
	m.setInputNumExits();
	m.setInputFileName();

	//Creates the map
	m.generateMap(m.getMapSize(),m.getNumExits());



}
