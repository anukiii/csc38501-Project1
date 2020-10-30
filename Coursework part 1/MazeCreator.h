#pragma once
class MazeCreator
{
private:
	int mapSize;
	int numExits;
			
public:
	int generateMap(int mapSize, int numExits);
	int getInputMapSize();
	int getInputNumExits();
	


};

