#include "SnakeBot.h"
#include <math.h>

#include <iostream>

#include <Windows.h>

#define MOVE_LOG(str) printf("CurrentMovement::%s\n", str)

SnakeBot::SnakeBot()
{

}

SnakeBot::~SnakeBot()
{
	currentPawn = nullptr;

}

bool SnakeBot::botWork()
{
	// Bot analys the map and search correct path to apple 1 time
	if (!pathFind)
	{
		if (!findPath(currentLogicField, snakePoint, applePoint))
		{
			MOVE_LOG("Cant find Way!!!");
			return false;
		}
		getDirection();
		return true;
	}
	else 
	{
		getDirection();
		return true;
	}
}

void SnakeBot::switchAppleSpawn()
{
	if (appleSpawn == true)
	{
		appleSpawn = false;

	}
}


bool SnakeBot::findPath(std::vector<std::vector<int>> &curLogField, sf::Vector2i& curHeadPoint, sf::Vector2i &appleP)
{
	std::vector<std::vector<int>> tempField = curLogField;

	int debug = 0;

	int succesCount = 0;

	bool findWay = false;

	int point = 5;

	tempField[curHeadPoint.y][curHeadPoint.x] = point;

	tempField[appleP.y][appleP.x] = 3;


	while (!findWay)
	{
		++point;
		for (int i = 1; i < 29; ++i) // Don't across the bounds of array
		{
			for (int j = 1; j < 29; ++j)
			{
				// For example, start cell contains number "5"...
				if (tempField[j][i] == (point - 1)) // ... if this cell is found...
				{
					// ...all cells that contain "0" around it is marked with a number greater by 1....
					if ((tempField[j + 1][i] != 1) && (tempField[j + 1][i] <= 0))
					{
						tempField[j + 1][i] = point;
						++succesCount;
					}
					else if ((tempField[j + 1][i] == 3))
					{
						// It means that we already got apple cell and path is finded //
						findWay = true;
						tempField[j + 1][i] = point;
						break;
					}

					if ((tempField[j - 1][i] != 1) && (tempField[j - 1][i] <= 0))
					{
						tempField[j - 1][i] = point;
						++succesCount;
					}
					else if ((tempField[j - 1][i] == 3))
					{
						findWay = true;
						tempField[j - 1][i] = point;
						break;
					}

					if ((tempField[j][i + 1] != 1) && (tempField[j][i + 1] <= 0))
					{
						tempField[j][i + 1] = point;
						++succesCount;
					}
					else if ((tempField[j][i + 1] == 3))
					{
						findWay = true;
						tempField[j][i + 1] = point;
						break;
					}

					if ((tempField[j][i - 1] != 1) && (tempField[j][i - 1] <= 0))
					{
						tempField[j][i - 1] = point;
						++succesCount;
					}
					else if ((tempField[j][i - 1] == 3))
					{
						findWay = true;
						tempField[j - 1][i] = point;
						break;
					}

					if (succesCount <= 0) //If less then 1 - can't find path
					{
						return false;
					}

				}//Check current point


			}//J_Cycle


		}//I_Cycle

		// ... on the next iteration point is increased and cycle repeat for number "6"

		//Isn't normal. No way to apple
		++debug;
		if (debug > 1000)
		{
			return false;
		}
	}
	//Temp point which will be change in comparePath()
	pathArr.clear();
	pathArr.push_back(appleP);

	comparePath(point, appleP, curHeadPoint, tempField);
	pathArrCount = pathArr.size() - 1;

	if (pathFind)
		return true;
	else
		return false;
}

void SnakeBot::comparePath(int point, sf::Vector2i& finishPoint,const sf::Vector2i& startPoint,std::vector<std::vector<int>> &tempField, int cycles)
{
	if (cycles > 1000)
	{
		std::cout << "Cycles over _1000_ in <comparePath()>\n";
		return;
	}

	if ((finishPoint.y == startPoint.y) && (finishPoint.x == startPoint.x))
	{
		//Comeback to the snake
		pathFind = true;
		return;
	}
	//Sleep(5);
	tempField[finishPoint.y][finishPoint.x] = 0;

	if (!pathFind)
	{
		// Need to check:
		// 1) Array out of bounds;
		// 2) Next cell number is lower then current;
		// 3) Next cell isn't empty;
		if ((finishPoint.y + 1 != 30) && ((tempField[finishPoint.y + 1][finishPoint.x] == point - 1) || (tempField[finishPoint.y + 1][finishPoint.x] == point - 2))
			&& (tempField[finishPoint.y + 1][finishPoint.x] != 0) /*&& (snakePoint.y >= finishPoint.y)*/)
		{
			--point;
			finishPoint.y += 1;
			pathArr.push_back(sf::Vector2i(finishPoint.x, finishPoint.y));
		}
		else if ((finishPoint.y - 1 != -1) && ((tempField[finishPoint.y - 1][finishPoint.x] == point - 1) || (tempField[finishPoint.y - 1][finishPoint.x] == point - 2))
			&& (tempField[finishPoint.y - 1][finishPoint.x] != 0) /*&& (snakePoint.y <= finishPoint.y)*/)
		{
			--point;
			finishPoint.y -= 1;
			pathArr.push_back(sf::Vector2i(finishPoint.x, finishPoint.y));
		}
		else if ((finishPoint.x + 1 != 30) && ((tempField[finishPoint.y][finishPoint.x + 1] == point - 1) || (tempField[finishPoint.y][finishPoint.x + 1] == point - 2))
			&& (tempField[finishPoint.y][finishPoint.x + 1] != 0) /*&& (snakePoint.x >= finishPoint.x)*/)
		{
			--point;
			finishPoint.x += 1;
			pathArr.push_back(sf::Vector2i(finishPoint.x, finishPoint.y));				
		}
		else if ((finishPoint.x - 1 != -1) && ((tempField[finishPoint.y][finishPoint.x - 1] == point - 1) || (tempField[finishPoint.y][finishPoint.x - 1] == point - 2))
			&& (tempField[finishPoint.y][finishPoint.x - 1] != 0) /*&& (snakePoint.x <= finishPoint.x)*/)
		{
			--point;
			finishPoint.x -= 1;
			pathArr.push_back(sf::Vector2i(finishPoint.x, finishPoint.y));
		}
	
		comparePath(point, finishPoint, startPoint, tempField);
	}
}

void SnakeBot::getDirection()
{
	if (currentPawn)
	{
		//Snake at the goal
		if (pathArrCount == 0)
		{
			return;
		}


		if ((snakePoint.x == pathArr[pathArrCount].x) &&
			(snakePoint.y == pathArr[pathArrCount].y))
		{
			--pathArrCount;
		}

		currentPawn->setHaveKeyEvent(false);
		//The apple point is...
		if (snakePoint.x < pathArr[pathArrCount].x) //...right?
		{
			currentPawn->rightDirectionMove();
		}
		else if (snakePoint.x > pathArr[pathArrCount].x) //...left?
		{
			currentPawn->leftDirectionMove();
		}
		else if (snakePoint.y > pathArr[pathArrCount].y) //...higher?
		{
			currentPawn->topDirection();
		}
		else if (snakePoint.y < pathArr[pathArrCount].y) //...lower?
		{
			currentPawn->botDirection();
		}
	}
}

