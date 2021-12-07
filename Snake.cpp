#include "Snake.h"

#include <iostream>

Snake::Snake()
{
	fillSnakePart();
}

Snake::~Snake()
{

}

void Snake::drawSnake(sf::RenderWindow* mWindow)
{
	for (SnakeParticle* part : snakeSize)
	{
		part->drawSprite(mWindow);
	}
}

/////////////////////////////////////////////////////////////////////
//_____________________________________________________movement_start

void Snake::moveEverTick()
{

	if (X_direction != 0 || Y_direction != 0)
	{
		std::cout << X_direction << " " << Y_direction << '\n';
		for (int i = snakeSize.size() - 1; i > 0; --i)
		{
			int X = snakeSize[i - 1]->getCurX();
			int Y = snakeSize[i - 1]->getCurY();

			snakeSize[i]->changeLocation(X, Y);
		}

		currentCoord_X += X_direction;
		currentCoord_Y += Y_direction;
		if (currentCoord_X > 29)
		{
			currentCoord_X = 0;
		}
		else if (currentCoord_X < 0)
		{
			currentCoord_X = 29;
		}
		if (currentCoord_Y > 29)
		{
			currentCoord_Y = 0;
		}
		else if (currentCoord_Y < 0)
		{
			currentCoord_Y = 29;
		}
		snakeSize[0]->changeLocation(currentCoord_X, currentCoord_Y);

		haveKeyEvent = false;
	}
}

void Snake::leftDirectionMove()
{
	if (!haveKeyEvent)
	{
		if (X_direction != -1 && X_direction != 1)
		{
			Y_direction = 0;
			X_direction = -1;
		}
		haveKeyEvent = true;
		curDir = LEFT;

		if (!firstMovement)
		{
			firstMovement = true;
		}
	}
}

void Snake::rightDirectionMove()
{
	if (!haveKeyEvent)
	{
		if (X_direction != 1 && X_direction != -1)
		{
			Y_direction = 0;
			X_direction = 1;
		}
		haveKeyEvent = true;
		curDir = RIGHT;

		if (!firstMovement)
		{
			firstMovement = true;
		}
	}
}

void Snake::topDirection()
{
	if (!haveKeyEvent)
	{
		if (Y_direction != -1 && Y_direction != 1)
		{
			Y_direction = -1;
			X_direction = 0;
		}
		haveKeyEvent = true;
		curDir = TOP;

		if (!firstMovement)
		{
			firstMovement = true;
		}
	}
}

void Snake::botDirection()
{
	if (!firstMovement)
	{
		return;
	}
	


	if (!haveKeyEvent)
	{
		if (Y_direction != 1 && Y_direction != -1)
		{
			Y_direction = 1;
			X_direction = 0;
		}
		haveKeyEvent = true;
		curDir = DOWN;
	}

}

//_____________________________________________________movement_end
/////////////////////////////////////////////////////////////////////


void Snake::growUp()
{
	const char* path = "resources\\snakeTorso.png";
	SnakeParticle* part = new SnakeParticle(path);

	int X = snakeSize[snakeSize.size() - 1]->getCurX();
	int Y = snakeSize[snakeSize.size() - 1]->getCurY();
	
	part->changeLocation(X, Y);
	snakeSize.push_back(part);

	++curPoints;
}

void Snake::backToDefaultParams()
{
	//currentCoord_X = defaultSnakePointX;
	//currentCoord_Y = defaultSnakePointY;
	currentSize = startSnakeSize;

	currentCoord_X = startPostion.x;
	currentCoord_Y = startPostion.y;

	X_direction = 0;
	Y_direction = 0;
	firstMovement = false;
	curPoints = startPoints;

	fillSnakePart();
}

void Snake::fillSnakePart()
{
	snakeSize.clear();
	const char* path;
	for (int i = 0; i < currentSize; ++i)
	{
		if (i == 0)
		{
			path = "resources\\snakeHead.png";
		}
		else
		{
			path = "resources\\snakeTorso.png";
		}

		SnakeParticle* part = new SnakeParticle(path);
		part->changeLocation(currentCoord_X, currentCoord_Y + i);
		snakeSize.push_back(part);
	}
}

snakeCoord Snake::getParticleCoord(int particleNum)
{
	if (particleNum < 0 || particleNum > snakeSize.size())
	{
		return snakeCoord();
	}

	snakeCoord SK;

	SK.xCoord = snakeSize[particleNum]->getCurX();
	SK.yCoord = snakeSize[particleNum]->getCurY();

	return SK;
}

sf::Vector2i Snake::getCurrentHeadPosition() const
{
	sf::Vector2i curHead;
	curHead.x = snakeSize[0]->getCurX();//getCurX();
	curHead.y = snakeSize[0]->getCurY();//getCurY();

	return sf::Vector2i(snakeSize[0]->getCurX(), snakeSize[0]->getCurY());
}

void Snake::setNewSprite(const int particleNumber, const char* pathToTexture)
{
	if (particleNumber > snakeSize.size() || particleNumber < 0)
	{
		return;
	}

	snakeSize[particleNumber]->setNewSprite(pathToTexture);

}

void Snake::setOriginSprites()
{
	for (SnakeParticle* snake : snakeSize)
	{
		snake->setOriginSprite();
	}
}

void Snake::setStartPosition(const int& x, const int& y)
{
	for (int i = 0; i < snakeSize.size(); ++i)
	{
		if (i == 0)
		{
			currentCoord_X = x;
			currentCoord_Y = y;

			startPostion.x = x;
			startPostion.y = y;
		}
		snakeSize[i]->changeLocation(y, x + i);
	}
}