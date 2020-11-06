#pragma once
#include <vector>
class Player
{
private:
	std::vector<int> path;
	int xPos;
	int yPos;
	int cellId;
	bool waiting;


public:
	void setXpos(int xPosNew);
	void setYpos(int yPosNew);
	void setCellId(int cellIdNew);
	
	void wait();
	void stopWait();

	void addToPath(int nextCell);


	std::vector<int> getPath();
	int getXPos();
	int getYpos();
	int getCellId();
	bool waitStatus();

};

