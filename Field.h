#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>

#include "Buttons.h"

#include <vector>

class LogicField;

class Field
{
private:

	sf::RenderWindow* mainWindow = nullptr;

	const int startMapH = 30;
	int MapH = 30;

	const int startMapW = 30;
	int MapW = 30;

	std::string* levelTaleMap = nullptr;

	bool isGameOver = false;

	sf::Text* pointsText;

	sf::Text* debugText;

	sf::Font textFont;

	//0 - is wall(kirpi4)(B)
	//1 - is dirt(G)
	//2 - is rock(
	//3 - is tree(
	//4 - is water(D)
	std::vector<sf::Sprite*> spriteBox;


	const int startWallSprite = 2;
	int currentWallSprite = 2;

	const int startGroundSprite = 1;
	int currentGroundSprite = 1;

	const int startWaterSprite = 4;
	int currentWaterSprite = 4;

	int spriteHeight = 40;

	int spriteWidth = 40;

	bool constrMode = false;

////////////////////////////////////////////////////////
//_________________________________________BUTTONS_START


	std::vector<Button*> buttonsLayout;

public:
	//Refill "buttonsLayout". 
	//1 - MainMenu buttons, 2 - settings buttons, 3 - pause buttons, 4 - endGame buttons
	void changeBtnLayout(int layout);

private:

//___________________________________________BUTTONS_END
////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
//_________________________________________MenuModes_START

	bool snakeModeOn = false;

//___________________________________________MenuModes_END
//////////////////////////////////////////////////////////

public:
	Field();

	~Field();

	std::string buttonsHandler(int mode = 1);

///////////////////////////////////////////////////////////////
//_________________________________________DRAW_PROCESSES_START

	//Environmet draw process
	void drawWalls();

	//Draw mainMenu btns
	void drawButtons();

	void drawConstructField();

	//Mode '0' - is text about current points in game process
	//Mode '1' - is text after game over
	void drawPoints(const int points, const int mode = 0);

//___________________________________________DRAW_PROCESSES_END
///////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
//_________________________________________GET/SET_START

	void setConstructorMode(const bool value) { constrMode = value; }

	void setSpriteWidth(const int iW) { spriteWidth = iW; }

	void setSpriteHeight(const int iH) { spriteHeight = iH; }

	int getSpriteWidth() const { return spriteWidth; }

	int getSpriteHeight() const { return spriteHeight; }

	void setLevelTales(std::string *LTL);

	//Copy constEmptyLVL to workEmptyLVL taleMap
	void setLVLEmptyMap();

	std::string* getLevelTalse() const { return levelTaleMap; }

	int getMapH() const { return MapH; }

	void setMapH(const int iH) { MapH = iH; }

	int getMapW() const { return MapW; }

	void setMapW(const int iW) { MapW = iW; }

	void setGameOver(const bool val) { isGameOver = val; }

	sf::RenderWindow* getMainWindow() const { return mainWindow; }

	std::string* getCurrentTaleMap() { return levelTaleMap; }

	void setSnakeMod(const bool value) { snakeModeOn = value; }

//___________________________________________GET/SET_END
////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//__________________________________________LVL_CONSTRUCTOR_START

	//For drag and drop sprites on window
	void constructorMode();

	void saveMap(std::string* map);

	void reScaleSprites(const float Y, const float X);

private:

	
	
	bool takeTitle = false;

	void alreadyHaveStartPoint();

	void correctPositionStartPoint();

	//Current drag title
	sf::Sprite* curSprite = nullptr;

	//For ex, water is 'D', earth is 'G', rock is 'R'.
	//Need for location titles on titleMap
	char curSpriteName = ' ';

	std::string *newLVL = nullptr;

	//Empty taleMap for constructor
	std::string emptyTaleMap[30] =
	{ "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              ",
	 "                              " };

	const std::string constEmptyTaleMap[30] =
	{ "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //G////R//",
	 "                              //////////",
	 "                              //W////D//",
	 "                              //////////",
	 "                              /////S////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////",
	 "                              //////////" };
	
	bool customLVL = false;

//__________________________________________LVL_CONSTRUCTOR_END
/////////////////////////////////////////////////////////////////

public: 

	

	//Message about snakeBot
	void drawDebugMessage(std::string message);


//Eggs
	void goToEva();

	void goToDefault();

};

















#endif // !FIELD_H

