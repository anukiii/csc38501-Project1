#include "Player.h"

void Player::setXpos(int xPosNew)
{
	xPos = xPosNew;
}

void Player::setYpos(int yPosNew)
{
	yPos = yPosNew;
}

void Player::setCellId(int cellIdNew)
{
	cellId = cellIdNew;
}

void Player::wait()
{
	waiting = true;
}

void Player::stopWait()
{
	waiting = false;
}

void Player::addToPath(int nextCell)
{
	path.push_back(nextCell);
}

std::vector<int> Player::getPath()
{
	return path;
}

int Player::getXPos()
{
	return xPos;
}

int Player::getYpos()
{
	return yPos;
}

int Player::getCellId()
{
	return cellId;
}

bool Player::waitStatus()
{
	return waiting;
}

void Player::setPlayerId(int playerIdNew)
{
	playerId = playerIdNew;
}

int Player::getPlayerId()
{
	return playerId;
}
