#ifndef LOGIC_FIEL_H
#define LOGIC_FIEL_H

#include <vector>

#include "Field.h"

#include "Snake.h"

#include "Apple.h"

class LogicField
{
private:

	std::vector<std::vector<int>> logicField;

	Snake* CurrentPawn = nullptr;

	std::string* currentMap = nullptr;

	int currentH = 30;

	int currentW = 30;

	// Check taleMap array and set wall on logic field
	void fillLogicMap();

	bool gameOver = false;

	Apple* curApple = nullptr;

	bool haveApple = false;


//____________________________________DEFAULT_PARAMS




public:

	bool isDeathCell(const int& X, const int& Y);

	LogicField();

	~LogicField();

	// Debug console out
	void drawField();

	// Take current snake coord and set it on logicField
	void setCurrentPawnCoord();

	bool appleOnBoard() const { return haveApple; }

	// Clear all logci field and set wall and dead cells only
	void clearLogicField();


//////////////////////////////////////////////
//_______________________________SET/GET_START

	void setApple(Apple* app);

	void setCurrentPawn(Snake* snake);

	//Is game over?
	bool getGameStatus() const { return gameOver; }

	void setTaleMap(std::string* taleMap);

	void setCurrentHeight(const int& H) { currentH = H; }

	void setCurrentWidth(const int& W) { currentW = W; }

	std::vector<std::vector<int>> getCurLogicField() const { return logicField; }

//_________________________________SET/GET_END
//////////////////////////////////////////////

	// Set "nullptr" for applePtr
	void clearApple();

	void defaultParams();
};


#endif // !LOGIC_FIEL_H