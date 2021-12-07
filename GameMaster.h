#ifndef GM_H
#define GM_H

#include <SFML/Graphics.hpp>

#include "LogicField.h"
#include "Field.h"
#include "Snake.h"
#include "SnakeBot.h"


enum GameMode
{
	MAIN_MENU,
	GAME,
	PAUSE,
	SETTINGS_MENU,
	CONSTRUCTOR,
	END_GAME,
	TO_CLOSE,
	CONSTRUCTOR_MODE
};

class GameMaster
{
public:

	GameMaster();

	~GameMaster();

	//Render movement, wall and other objects. 
	void gameProcess();

	//Speak for itself
	void mainProcessOfAllRender();

private:

	void mainMenuProcess();

	//Restart or exit buttons
	void gameOverProcess();

	void drawButtons();

	sf::Clock timer;

	const float startGameSpeed = 0.5;
	float currentGameSpeed = startGameSpeed;

	std::vector<std::string*> customLVLs;

	bool snakeBotFailedEvent = false;

/////////////////////////////////////////////////////////////////
//__________________________________________LVL_CONSTRUCTOR_START

	void constructorMode();

	//Resize window, set empty tale map and others settings for construct
	void goToConstruct();

	//Default settings for game window
	void backFromConstruct();

	void setStartPosition(std::string* taleMap);



	LogicField* logicField = nullptr;

	Snake* snake = nullptr;

	Field* GUIField = nullptr;

	void eventHandler();

	//Arg need for pressed/realease switch
	void mouseHandler(int modePR);

	bool GameOver = false;

	bool toExit = false;
	
	GameMode currentGM = MAIN_MENU;

	void backToDefaultParams();

	void switchTaleMap(const int& map);

	sf::Vector2i spawnPosition;

//Apple

	Apple* currentApple = nullptr;

	void setApple();

	void destroyApple();


//SnakeBot
	
	SnakeBot* snakeBot = nullptr;

	bool snakeBotOn = false;

	void activateSnakeBot();

	void deActivateSnakeBot();

	void snakeBotWork();


//Egs

	void setNewSprites();

	void setOriginSprites();

	bool evaMode = false;
};







#endif
