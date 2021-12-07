#ifndef SNAKE_H
#define SNAKE_H


#include "SnakeParticle.h"

#include <vector>

#include <SFML/Graphics.hpp>

struct snakeCoord
{
	int xCoord = 0;
	int yCoord = 0;
};

enum CurrentDirection
{
	TOP,
	DOWN,
	RIGHT,
	LEFT
};

class Snake
{
private:

//________________________________DEFAULT_CONST_PARAMS
	const int defaultSnakePointX = 15;

	const int defaultSnakePointY = 15;
	const int startPoints = 0;
	const int startSnakeSize = 3;
	const int startSize = 3;

	int curPoints = 0;

	int currentCoord_X = 15;
	int currentCoord_Y = 15;

	int currentScores = 0;
	int currentSize = 3;


	int X_direction = 0;
	int Y_direction = 0;

	sf::Vector2i startPostion;

	bool firstMovement = false;

	std::vector<SnakeParticle*> snakeSize;

	CurrentDirection curDir;

public:
	Snake();

	~Snake();

	void drawSnake(sf::RenderWindow* mWindow);

/////////////////////////////////////////////////////////////////////
//______________________________________________________SET/GET_START

	int getDirX() const { return X_direction; }
	//void setDirX(const int &newX) { X_direction = newX; }

	int getDirY() const { return Y_direction; }
	//void setDirY(const int &newY) { Y_direction = newY; }

	void setCurX(const int newX) { currentCoord_X = newX; }
	int getCurX() const { return currentCoord_X; }

	void setCurY(const int newY) { currentCoord_Y = newY; }
	int getCurY() const { return currentCoord_Y; }

	int getSnakeSize() const { return snakeSize.size(); }

	snakeCoord getParticleCoord(int particleNum);

	int getCurPoints() const { return curPoints; }

	CurrentDirection getCurrentDirection() const { return curDir; }

	sf::Vector2i getCurrentHeadPosition() const;

	void setHaveKeyEvent(const bool value) { haveKeyEvent = value; }

	//Set new sprite for choisen particle
	void setNewSprite(const int particleNumber, const char* pathToTexture);

	void setOriginSprites();


	void setStartPosition(const int &x, const int &y);
//______________________________________________________SET/GET_END
/////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
//______________________________________________________MOVEMENT_START

	void moveEverTick();

	void stopMovement() { X_direction = 0; Y_direction = 0; }

	void leftDirectionMove();

	void rightDirectionMove();

	void topDirection();

	void botDirection();

//______________________________________________________MOVEMENT_END
/////////////////////////////////////////////////////////////////////

	void growUp();

	void backToDefaultParams();

private:

	//Чтобы змея не проходила сквозь себя при быстром нажатии клавиш
	bool haveKeyEvent = false;

	void fillSnakePart();
	
};

















#endif // !SNAKE_H