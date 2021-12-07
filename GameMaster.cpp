#include "GameMaster.h"
#include "DefaultLevels.h"
#include <iostream>

#define CONSOLELOG(str) printf("GameMaster::Log::%s\n", str)

GameMaster::GameMaster()
{

	snake = new Snake();

	GUIField = new Field();

	logicField = new LogicField();

	if (snake)
	{
		logicField->setCurrentPawn(snake);
	}
	switchTaleMap(1);
	logicField->setCurrentHeight(GUIField->getMapH());
	logicField->setCurrentWidth(GUIField->getMapW());

	GUIField->changeBtnLayout(1);
}

GameMaster::~GameMaster()
{
	delete snake;
	delete GUIField;
	delete logicField;

	CONSOLELOG("Goodby:)");
	delete this;
	
}

void GameMaster::mainProcessOfAllRender()
{
	while (!toExit)
	{
		mainMenuProcess();

		gameProcess();

		gameOverProcess();

		constructorMode();
	}	
}

void GameMaster::drawButtons()
{
	GUIField->drawButtons();
}

void GameMaster::mainMenuProcess()
{
	if (currentGM == MAIN_MENU || currentGM == SETTINGS_MENU)
	{

		if (GUIField->getMainWindow()->isOpen())
		{
			GUIField->getMainWindow()->clear();
			GUIField->drawWalls();
			drawButtons();
			GUIField->getMainWindow()->display();

			eventHandler();
		}
	}
}

void GameMaster::gameOverProcess()
{
	if (currentGM == END_GAME)
	{
		if (GUIField->getMainWindow()->isOpen())
		{
			eventHandler();
			GUIField->getMainWindow()->clear();

			GUIField->drawWalls();
			snake->drawSnake(GUIField->getMainWindow());
			drawButtons();
			GUIField->drawPoints(snake->getCurPoints(), 1);

			GUIField->getMainWindow()->display();

		}
	}
}

void GameMaster::switchTaleMap(const int& map)
{
	switch (map)
	{
	case (1):
		GUIField->setLevelTales(DefaultLevelsTales::perimetrTaleMap);
		logicField->setTaleMap(DefaultLevelsTales::perimetrTaleMap);
		setStartPosition(DefaultLevelsTales::perimetrTaleMap);
		break;

	case(2):
		GUIField->setLevelTales(DefaultLevelsTales::midleTaleMap);
		logicField->setTaleMap(DefaultLevelsTales::midleTaleMap);
		setStartPosition(DefaultLevelsTales::midleTaleMap);
		break;

	case(3):
		GUIField->setLevelTales(DefaultLevelsTales::hardTaleMap);
		logicField->setTaleMap(DefaultLevelsTales::hardTaleMap);
		setStartPosition(DefaultLevelsTales::hardTaleMap);
		break;

	case(4):
		GUIField->setLevelTales(DefaultLevelsTales::emptyTaleMap);
		logicField->setTaleMap(DefaultLevelsTales::emptyTaleMap);
		setStartPosition(DefaultLevelsTales::emptyTaleMap);
	}
}

void GameMaster::setStartPosition(std::string* taleMap)
{
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if (taleMap[j][i] == 'S')
			{
				if (snake)
				{	
					snake->setStartPosition(i, j);
				}
			}
		}
	}
}

void GameMaster::gameProcess()
{
	if (currentGM != GAME)
	{
		return;
	}
	sf::Clock cl;
	cl.restart();

	while (GUIField->getMainWindow()->isOpen() && currentGM != MAIN_MENU)
	{
		if (evaMode)
		{
			setNewSprites();
		}

		eventHandler();

		if (toExit)
		{
			return;
		}


		//{ LogicProcess
		setApple();
		logicField->setCurrentPawnCoord();

		if ((cl.getElapsedTime().asSeconds() > currentGameSpeed) && (currentGM == GAME) && currentApple)
		{
			snake->moveEverTick();
			cl.restart();	
		}

		if (snakeBotOn)
		{
			snakeBotWork();
		}
		// } LogicProcess

		// { Rende processes
		if (!logicField->getGameStatus() && currentApple)
		{
			GUIField->getMainWindow()->clear();

			GUIField->drawWalls();
			snake->drawSnake(GUIField->getMainWindow());

			if (currentApple)
			{
				currentApple->drawApple(GUIField->getMainWindow());
			}

			GUIField->drawPoints(snake->getCurPoints());

			if (currentGM == PAUSE)
			{
				drawButtons();
			}

			if (snakeBotFailedEvent && snakeBotOn)
			{
				GUIField->drawDebugMessage("SnakeBot cant find \n   the way and \n   deactivated!");
			}

			GUIField->getMainWindow()->display();

		} // } RenderProcess
		else
		{
			GameOver = true;
			currentGM = END_GAME;
			GUIField->changeBtnLayout(4);
			return;
		}
	}
}

void GameMaster::eventHandler()
{
	if (GUIField)
	{
		if (GUIField->getMainWindow())
		{
			sf::Event event;

			while (GUIField->getMainWindow()->pollEvent(event))
			{
				

				if (event.type == sf::Event::Closed)
				{
					toExit = true;
				}


				if (event.type == sf::Event::KeyPressed)
				{
					if (snakeBotFailedEvent)
					{
						snakeBotFailedEvent = false;
					}

					switch (event.key.code)
					{
					case sf::Keyboard::Left:
						snake->leftDirectionMove();
						break;

					case sf::Keyboard::Right:
						snake->rightDirectionMove();
						break;

					case sf::Keyboard::Up:
						snake->topDirection();
						break;

					case sf::Keyboard::Down:
						snake->botDirection();
						break;

					case sf::Keyboard::Space:
						//snake->growUp();
						break;

					case sf::Keyboard::Escape:
						GUIField->changeBtnLayout(3);
						currentGM = PAUSE;
						break;

					case sf::Keyboard::P:
						GUIField->changeBtnLayout(3);
						currentGM = PAUSE;
						break;

					default:
						break;
					}
				}

				if (event.type == sf::Event::MouseButtonPressed)
				{
					switch (event.mouseButton.button)
					{
					case sf::Mouse::Left:
						mouseHandler(1);
						break;


					default:
						break;
					}
				}
				if (event.type == sf::Event::MouseButtonReleased)
				{
					switch (event.mouseButton.button)
					{
					case sf::Mouse::Left:
						mouseHandler(0);
						break;

					default:
						break;
					}
				}
			}
		}
	}
}

void GameMaster::backToDefaultParams()
{
	destroyApple();
	snake->setHaveKeyEvent(false);
	GameOver = false;
	toExit = false;
	currentGameSpeed = startGameSpeed;
	currentGM = GAME;
}

void GameMaster::mouseHandler(int modePR)
{
	std::string btnText = "";
	if (modePR == 1)
	{
		CONSOLELOG("Mouse left click");
		btnText = GUIField->buttonsHandler(modePR);
	}
	else
	{
		CONSOLELOG("Mouse left realease");
		btnText = GUIField->buttonsHandler(modePR);
	}
	


	if (currentGM == MAIN_MENU)
	{
		if (btnText == "Start")
		{
			snake->backToDefaultParams();
			logicField->defaultParams();
			backToDefaultParams();
		}
		else if (btnText == "Params")
		{
			GUIField->changeBtnLayout(2);
			currentGM = SETTINGS_MENU;
		}
		else if (btnText == "Exit")
		{
			currentGM = TO_CLOSE;
			toExit = true;
		}
		else if (btnText == "Constructor")
		{
			goToConstruct();
		}
	}

	if (currentGM == SETTINGS_MENU)
	{
		if (btnText == "LVL#1")
		{
			if (evaMode)
			{
				setOriginSprites();
				GUIField->goToDefault();
				evaMode = false;
			}
			switchTaleMap(1);
		}
		else if (btnText == "LVL#2")
		{
			if (evaMode)
			{
				setOriginSprites();
				GUIField->goToDefault();
				evaMode = false;
			}

			switchTaleMap(2);
		}
		else if (btnText == "LVL#3")
		{
			if (!evaMode)
			{
				GUIField->goToEva();
				evaMode = true;
			}
			switchTaleMap(3);
		}
		else if (btnText == "Back")
		{
			GUIField->changeBtnLayout(1);
			currentGM = MAIN_MENU;
		}
		else if (btnText == "CustomLVL")
		{
			switchTaleMap(4);
		}
		else if (btnText == "SnakeBotON")
		{
			GUIField->setSnakeMod(true);
			activateSnakeBot();
		}
		else if (btnText == "SnakeBotOFF")
		{
			GUIField->setSnakeMod(false);
			deActivateSnakeBot();
		}
	}

	if (currentGM == PAUSE)
	{
		if (btnText == "Game")
		{
			currentGM = GAME;
		}
		else if (btnText == "EndGame")
		{
			GUIField->changeBtnLayout(1);
			currentGM = MAIN_MENU;
		}
		else if (btnText == "Exit")
		{
			currentGM = TO_CLOSE;
			toExit = true;
		}
	}

	if (currentGM == END_GAME)
	{
		if (btnText == "Restart")
		{
			snake->backToDefaultParams();
			logicField->defaultParams();
			backToDefaultParams();
		}
		else if (btnText == "MainMenu")
		{
			GUIField->changeBtnLayout(1);
			currentGM = MAIN_MENU;
		}
		else if (btnText == "Exit")
		{
			currentGM = TO_CLOSE;
			toExit = true;
		}
	}

	if (currentGM == CONSTRUCTOR)
	{
		if (btnText == "Back")
		{
			backFromConstruct();
			currentGM = MAIN_MENU;
		}
		else if (btnText == "Save")
		{
			GUIField->saveMap(DefaultLevelsTales::emptyTaleMap);
		}
		else if (btnText == "Clear")
		{
			GUIField->setLVLEmptyMap();
		}
	}
	
}

// Apple {

void GameMaster::setApple()
{
	if (!logicField->appleOnBoard())
	{
		destroyApple();
		if (snakeBot)
		{
			snakeBot->setAppleSpawn(false);
		}
	}

	if (!currentApple)
	{
		logicField->setCurrentPawnCoord();
		currentApple = new Apple();
		while (!logicField->appleOnBoard())
		{
			srand(time(0));
			int x = 1 + rand() % (DefaultLevelsTales::lvlH - 1);
			int y = 1 + rand() % (DefaultLevelsTales::lvlW - 1);
			currentApple->setPosition(x, y);
			logicField->setApple(currentApple);
		}

		currentApple->drawApple(GUIField->getMainWindow());
		GUIField->getMainWindow()->display();

		if (snakeBot && snakeBotOn)
		{
			snakeBot->setAppleSpawn(true);
			snakeBot->setPathFind(false);
			snake->stopMovement();
		}
	}

}

void GameMaster::destroyApple()
{
	if (currentApple)
	{
		currentApple->~Apple();
	}
	currentApple = nullptr;
}

// Apple }

//////////////////////////////////////////////////////////
//_______________________________________CONSTRUCTOR_START


void GameMaster::constructorMode()
{
	if (currentGM == CONSTRUCTOR)
	{
		if (GUIField->getMainWindow()->isOpen())
		{

			if (toExit)
			{
				return;
			}

			eventHandler();
			GUIField->getMainWindow()->clear();
			GUIField->drawConstructField();
			drawButtons();
			GUIField->constructorMode();

			GUIField->getMainWindow()->display();

		}
	}
}

void GameMaster::goToConstruct()
{
	if (evaMode)
	{
		switchTaleMap(1);
		GUIField->goToDefault();
		setOriginSprites();
		evaMode = false;
	}

	currentGM = CONSTRUCTOR;
	GUIField->setConstructorMode(true);
	GUIField->changeBtnLayout(5);
	GUIField->setSpriteWidth(30);
	GUIField->setMapW(40);

	GUIField->reScaleSprites(0.75, 1.0);
	GUIField->setLVLEmptyMap();

}

void GameMaster::backFromConstruct()
{
	currentGM = MAIN_MENU;
	GUIField->setConstructorMode(false);
	GUIField->changeBtnLayout(1);
	GUIField->setSpriteWidth(40);
	GUIField->reScaleSprites(1.0, 1.0);
	GUIField->setMapW(30);

}

//_______________________________________CONSTRUCTOR_END
////////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//______________________________________SNAKE_BOT_START

void GameMaster::activateSnakeBot()
{
	snakeBot = new SnakeBot();
	snakeBot->setCurrentPawn(snake);
	snakeBotOn = true;
}

void GameMaster::deActivateSnakeBot()
{
	snakeBotOn = false;
	delete snakeBot;
	snakeBot = nullptr;
}

void GameMaster::snakeBotWork()
{
	if (!snakeBotOn || !snakeBot)
	{
		CONSOLELOG("snakeModOff or snakeBot not found!");
		return;
	}

	snakeBot->setLogicField(logicField->getCurLogicField());
	if (currentApple)
	{
		snakeBot->setA_S_Points(snake->getCurrentHeadPosition(), currentApple->getCurPosition());
		
		if (!snakeBot->botWork())
		{
			CONSOLELOG("Cant find way!SnakeBot disabled.");
			deActivateSnakeBot();
			snakeBotFailedEvent = true;
			return;
		}
	}
}

//______________________________________SNAKE_BOT_END
/////////////////////////////////////////////////////

//Egs

void GameMaster::setNewSprites()
{
	for (int i = 0; i < snake->getSnakeSize(); ++i)
	{
		if (i == 0)
		{
			snake->setNewSprite(i, "resources\\evaHead.png");
			continue;
		}
		else
		{
			snake->setNewSprite(i, "resources\\evaTorso.png");
		}
	}

	if (currentApple)
	{
		currentApple->setNewSprite("resources\\prism.png");
	}
}

void GameMaster::setOriginSprites()
{
	snake->setOriginSprites();
	currentApple->setOriginSprite();
}