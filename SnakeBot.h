#ifndef SNAKEBOT_H
#define SNAKEBOT_H

#include "Snake.h"
#include "LogicField.h"
#include "SFML/Graphics.hpp"

#include <vector>



class SnakeBot
{
private:

	Snake* currentPawn = nullptr;



	std::vector<std::vector<int>> currentLogicField;

	sf::Vector2i snakePoint;
	sf::Vector2i applePoint;

	//If apple spawn on the same line
	bool appleSpawn = false;



	

public:

	SnakeBot();

	~SnakeBot();

	bool botWork();

/////////////////////////////////////////////////
//__________________________________GET/SET_START

	void setLogicField(const std::vector<std::vector<int>> &lf) { currentLogicField = lf; }

	void setCurrentPawn(Snake* pawn) { currentPawn = pawn; }

	void setAppleSpawn(const bool value) { appleSpawn = value; }

	//Set the points on logicField for apple and snake
	void setA_S_Points(const sf::Vector2i& snakeP,const sf::Vector2i& appleP) { snakePoint = snakeP; applePoint = appleP; }
	
	void setPathFind(const bool value) { pathFind = value; }

//___________________________________GET/SET_END
/////////////////////////////////////////////////

private:

	void switchAppleSpawn();

///////////////////////////////////////////////////////////
//___________________________________________WORK_ALG_START

public: 

	//Alg Lee finde path from snake to apple
	bool findPath(std::vector<std::vector<int>>& curLogField, sf::Vector2i& curHeadPoint, sf::Vector2i& applePoint);

	//Comeback from apple to snake and save X/Y coords each cell 
	void comparePath(int point, sf::Vector2i &finishPoint, const sf::Vector2i& startPoint,std::vector<std::vector<int>>& tempField, int cycles = 0);

	//Bot found the path and snake move to apple?
	bool pathFind = false;

	//Guide the snake on field from cell to cell until
	//it get the apple
	void getDirection();

	//Size of the path (quantity of cells)
	int pathArrCount = 1;

	//Temp logic field with snake,apple and dead cells 
	//std::vector<std::vector<int>> tempField;

	//Arr with X/Y correct cells coords 
	std::vector<sf::Vector2i> pathArr;

//___________________________________________WORK_ALG_END
/////////////////////////////////////////////////////////

};




























#endif // !SNAKEBOT_H






