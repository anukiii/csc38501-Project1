#include "MazeGeneratorMain.h"
#include"MazeCreator.h"

int main() {
	MazeCreator m;
	//user input for size & exits
	m.getInputMapSize();
	m.getInputNumExits();

	//Creates the map
	m.generateMap(m.getMapSize(),m.getNumExits());

}
