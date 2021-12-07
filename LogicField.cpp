#include "LogicField.h"
#include <iostream>

#define ERROR(funcName, message) printf("ERROR::%s::%s\n", #funcName, #message)

void LogicField::drawField()
{
	std::cout << std::string(100, '\n');
	for (int i = 0; i < currentH; ++i)
	{
		for (int j = 0; j < currentW; ++j)
		{
			std::cout << logicField[i][j] << " ";
		}
		std::cout << '\n';
	}
	
}

LogicField::~LogicField()
{

}

LogicField::LogicField()
{

}

void LogicField::fillLogicMap()
{
	logicField.clear();
		for (int i = 0; i < currentH; ++i)
		{
			std::vector<int> temp2;
			for (int j = 0; j < currentW; ++j)
			{
				if (currentMap[i][j] == 'B' || currentMap[i][j] == 'D' || currentMap[i][j] == 'R' || currentMap[i][j] == 'W')
				{
					temp2.push_back(1);
				}
				else
				{
					temp2.push_back(0);
				}
			}
			logicField.push_back(temp2);
		}
}


void LogicField::setApple(Apple* app)
{
	if (currentMap)
	{
		if (logicField[app->getCurY()][app->getCurX()] != 0)
		{
			return;
		}
	}
	curApple = app;
	haveApple = true;
}

void LogicField::setCurrentPawn(Snake* snake)
{
	if (snake)
	{
		CurrentPawn = snake;
	}
}

void LogicField::setCurrentPawnCoord()
{
	if (!CurrentPawn)
	{
		ERROR("setCurrentPawnCoord", "CurrenPawn not found!");
		return;
	}

	snakeCoord skss = CurrentPawn->getParticleCoord(0);
	if (isDeathCell(skss.xCoord, skss.yCoord))
	{
		return;
	}

	clearLogicField();

	if (haveApple)
	{
		logicField[curApple->getCurY()][curApple->getCurX()] = 3;
	}

	for (int snakePart = 0; snakePart < CurrentPawn->getSnakeSize(); ++snakePart)
	{
		snakeCoord SK = CurrentPawn->getParticleCoord(snakePart);

		if (logicField[SK.yCoord][SK.xCoord] == 0)
		{
			if (snakePart == 0)
			{
				logicField[SK.yCoord][SK.xCoord] = 5;
			}
			else
			{
				logicField[SK.yCoord][SK.xCoord] = 2;
			}
		}
	}


	if (logicField[CurrentPawn->getCurY()][CurrentPawn->getCurX()] == 3)
	{
		CurrentPawn->growUp();
		clearApple();
		setCurrentPawnCoord();
	}
}

void LogicField::setTaleMap(std::string* taleMap)
{
	currentMap = taleMap;
	fillLogicMap();
}

void LogicField::clearLogicField()
{
	for (int i = 0; i < currentH; ++i)
	{
		for (int j = 0; j < currentW; ++j)
		{
			if (currentMap[i][j] == 'B' || currentMap[i][j] == 'D' || currentMap[i][j] == 'R' || currentMap[i][j] == 'W')
			{
				logicField[i][j] = 1;
			}
			else
			{
				logicField[i][j] = 0;
			}
		}
	}
}

void LogicField::defaultParams()
{
	clearApple();
	clearLogicField();
	gameOver = false;
}

void LogicField::clearApple()
{
	curApple = nullptr;
	haveApple = false;
}

bool LogicField::isDeathCell(const int& X, const int& Y)
{
	if (logicField[Y][X] == 1 || logicField[Y][X] == 2)
	{
		gameOver = true;
		return true;
	}
	return false;
}