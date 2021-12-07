#include "Field.h"



//#include "DefaultLevels.h"



#include <iostream>

Field::Field()
{
	mainWindow = new sf::RenderWindow(sf::VideoMode(1200, 1200), "Snake", sf::Style::Titlebar | sf::Style::Close);
	
////////////////////////////////////////////////
//_____________________________LOAD_SPRITE_START

//WallSprite_______________________________
	sf::Texture* text = new sf::Texture();
	text->loadFromFile("resources\\wall.png");
	sf::Sprite* wallSprite = new sf::Sprite(*text);
	//wallSprite->setOrigin(20, 20);
//GroundSprite
	sf::Texture* text2 = new sf::Texture();
	text2->loadFromFile("resources\\ground2.png");
	sf::Sprite* groundSprite = new sf::Sprite(*text2);
	//groundSprite->setOrigin(20, 20);
//RockSprite
	sf::Texture* text3 = new sf::Texture();
	text3->loadFromFile("resources\\rock.png");
	sf::Sprite* rockSprite = new sf::Sprite(*text3);
	//rockSprite->setOrigin(20, 20);

	sf::Texture* text4 = new sf::Texture();
	text4->loadFromFile("resources\\tree.png");
	sf::Sprite* sp = new sf::Sprite(*text4);
	//sp->setOrigin(20, 20);

	sf::Texture* text5 = new sf::Texture();
	text5->loadFromFile("resources\\water.png");
	sf::Sprite* sp2 = new sf::Sprite(*text5);
	//sp2->setOrigin(20, 20);

	sf::Texture* text6 = new sf::Texture();
	text6->loadFromFile("resources\\LCLsea.png");
	sf::Sprite* sp3 = new sf::Sprite(*text6);
	//sp3->setOrigin(20, 20);

	sf::Texture* text7 = new sf::Texture();
	text7->loadFromFile("resources\\metalicFlor.png");
	sf::Sprite* sp4 = new sf::Sprite(*text7);
	//sp4->setOrigin(20, 20);

	sf::Texture* text8 = new sf::Texture();
	text8->loadFromFile("resources\\start.png");
	sf::Sprite* sp5 = new sf::Sprite(*text8);


	spriteBox.push_back(wallSprite);
	spriteBox.push_back(groundSprite);
	spriteBox.push_back(rockSprite);
	spriteBox.push_back(sp);
	spriteBox.push_back(sp2);
	spriteBox.push_back(sp3);
	spriteBox.push_back(sp4);
	spriteBox.push_back(sp5);

//______________________________LOAD_SPRITE_END
///////////////////////////////////////////////




	
	textFont.loadFromFile("resources\\Maler.ttf");

	pointsText = new sf::Text();
	pointsText->setFont(textFont);
	pointsText->setCharacterSize(40);
	pointsText->setFillColor(sf::Color::White);
	pointsText->setStyle(sf::Text::Italic);


	debugText = new sf::Text();
	debugText->setFont(textFont);
	debugText->setCharacterSize(40);
	debugText->setFillColor(sf::Color::Red);
	debugText->setStyle(sf::Text::Italic);
}

Field::~Field()
{
	mainWindow->close();
}

void Field::setLevelTales(std::string *LTL)
{
	levelTaleMap = LTL;
}


void Field::changeBtnLayout(int layout)
{
	if (layout > 5 || layout < 1)
	{
		return;
	}

	buttonsLayout.clear();
	switch (layout)
	{
	case 1:
	{//Main menu buttons
		Button* btnGame = new Button();
		btnGame->setText("Start");
		buttonsLayout.push_back(btnGame);

		Button* btnSettings = new Button();
		btnSettings->setText("Params");
		buttonsLayout.push_back(btnSettings);

		Button* constBtn = new Button();
		constBtn->setText("Constructor");
		buttonsLayout.push_back(constBtn);

		Button* btnExit = new Button();
		btnExit->setText("Exit");
		buttonsLayout.push_back(btnExit);
	}
		break;

	case 2:
	{//Params buttons
		Button* btnLvl1 = new Button();
		btnLvl1->setText("LVL#1");
		buttonsLayout.push_back(btnLvl1);

		Button* btnLvl2 = new Button();
		btnLvl2->setText("LVL#2");
		buttonsLayout.push_back(btnLvl2);

		Button* btnLvl3 = new Button();
		btnLvl3->setText("LVL#3");
		buttonsLayout.push_back(btnLvl3);

		if(customLVL)
		{			
			Button* customBtn = new Button();
			customBtn->setText("CustomLVL");
			buttonsLayout.push_back(customBtn);
		}

		Button* snakeModeBtn = new Button();
		if (!snakeModeOn)
		{
			snakeModeBtn->setText("SnakeBotOFF");
			snakeModeBtn->setSwitchedText("SnakeBotON");
		}
		else
		{
			snakeModeBtn->setText("SnakeBotON");
			snakeModeBtn->setSwitchedText("SnakeBotOFF");

		}
		snakeModeBtn->setNeedToSwitchText(true);
		buttonsLayout.push_back(snakeModeBtn);

		Button* btnBack = new Button();
		btnBack->setText("Back");
		buttonsLayout.push_back(btnBack);
	}
		break;

	case 3:
	{ //Pause buttons
		Button* btnCont = new Button();
		btnCont->setText("Game");
		buttonsLayout.push_back(btnCont);

		Button* btnMM = new Button();
		btnMM->setText("EndGame");
		buttonsLayout.push_back(btnMM);

		Button* btnEx = new Button();
		btnEx->setText("Exit");
		buttonsLayout.push_back(btnEx);
	}
		break;

	case 4:
	{ //Restart buttons
		Button* btnRestart = new Button();
		btnRestart->setText("Restart");
		buttonsLayout.push_back(btnRestart);

		Button* btnMM = new Button();
		btnMM->setText("MainMenu");
		buttonsLayout.push_back(btnMM);

		Button* btnExit = new Button();
		btnExit->setText("Exit");
		buttonsLayout.push_back(btnExit);
	}
		break;
	
	case 5:
	{ //ConstructBtns
		Button* btnSave = new Button();
		btnSave->setText("Save");
		buttonsLayout.push_back(btnSave);

		Button* btnClear = new Button();
		btnClear->setText("Clear");
		buttonsLayout.push_back(btnClear);

		Button* btnBack = new Button();
		btnBack->setText("Back");
		buttonsLayout.push_back(btnBack);
	}
		break;


	}
}

std::string Field::buttonsHandler(int mode)
{
	if (mode != 1)
	{
		//In constr mode
		if (constrMode)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*getMainWindow());
			int x = mousePos.x / spriteWidth;
			int y = mousePos.y / spriteHeight;

			std::cout << "Mouse pos(x/y):\t" << x << "/" << y << '\n';

			if (takeTitle)
			{
				if (x >= 30)
				{
					curSprite = nullptr;
					takeTitle = false;
				}
				else
				{
					alreadyHaveStartPoint();
					emptyTaleMap[y][x] = curSpriteName;
					correctPositionStartPoint();
				}
			}

			if (constEmptyTaleMap[y][x] == 'G')
			{
				curSpriteName = 'G';
				takeTitle = true;
				curSprite = spriteBox[1];
				std::cout << "TakeSprite\n";
			}
			else if (constEmptyTaleMap[y][x] == 'W')
			{
				curSpriteName = 'W';
				takeTitle = true;
				curSprite = spriteBox[0];
				std::cout << "TakeSprite\n";
			}
			else if (constEmptyTaleMap[y][x] == 'R')
			{
				curSpriteName = 'R';
				takeTitle = true;
				curSprite = spriteBox[2];
				std::cout << "TakeSprite\n";
			}
			else if (constEmptyTaleMap[y][x] == 'D')
			{
				curSpriteName = 'D';
				takeTitle = true;
				curSprite = spriteBox[4];
				std::cout << "TakeSprite\n";
			}
			else if (constEmptyTaleMap[y][x] == 'S')
			{
				curSpriteName = 'S';
				takeTitle = true;
				curSprite = spriteBox[7];
				std::cout << "TakeSprite\n";
			}

		}

		//Default handler
		for (Button* btn : buttonsLayout)
		{
			if (btn->getPressedStatus())
			{
				btn->setPressedStatus(false);
				return btn->getText();
			}
		}
		
	}

	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*getMainWindow());
		for (Button* btn : buttonsLayout)
		{
			sf::Vector2f btnPos = btn->getButtonPosition();
			sf::Vector2f btnSize = btn->getBtnSize();

			//Check mousePos in btn rectangle borders
			if (mousePos.x >= btnPos.x && mousePos.x <= (btnPos.x + btnSize.x) &&
				mousePos.y >= btnPos.y && mousePos.y <= (btnPos.y + btnSize.y))
			{
				btn->setPressedStatus(true);
			}
		}
	}
	

	return std::string();
}


///////////////////////////////////////////////////////////////
//_________________________________________DRAW_PROCESSES_START


void Field::drawWalls()
{
	if (!mainWindow)
	{
		return;
	}
	if (!levelTaleMap)
	{
		return;
	}

	for (int i = 0; i < MapH; ++i)
	{
		for (int j = 0; j < MapW; ++j)
		{
			if (levelTaleMap[i][j] == 'B')
			{
				spriteBox[currentWallSprite]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[currentWallSprite]);
			}
			else if (levelTaleMap[i][j] == 'W')
			{
				spriteBox[0]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[0]);
			}
			else if (levelTaleMap[i][j] == 'G')
			{
				spriteBox[1]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[1]);
			}
			else if (levelTaleMap[i][j] == 'R')
			{
				spriteBox[2]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[2]);
			}
			else if (levelTaleMap[i][j] == 'D')
			{
				spriteBox[currentWaterSprite]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[currentWaterSprite]);
			}
			else
			{
				spriteBox[currentGroundSprite]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[currentGroundSprite]);
			}
	
		}
	}
}


void Field::drawButtons()
{
	if (!mainWindow)
	{
		return;
	}

	if (!constrMode)
	{
		sf::Vector2u wRes = mainWindow->getSize();

		int btnCount = 1;
		for (Button* btn : buttonsLayout)
		{
			sf::Vector2f rectSize = btn->getSize();
			sf::Vector2f btnPos;
			btnPos.x = wRes.x / 2 - (rectSize.x / 2);
			btnPos.y = (((wRes.y / buttonsLayout.size() / 2)) * (btnCount)-rectSize.y / 2);

			btn->setPosition(btnPos);

			btn->drawButtons(mainWindow);

			++btnCount;
		}
	}
	// Constructor mode ON (side btn's)
	else if (constrMode)
	{
		sf::Vector2u wRes = mainWindow->getSize();
		int btnCount = 1;
		for (Button* btn : buttonsLayout)
		{
				
			sf::Vector2f rectSize = btn->getSize();
			sf::Vector2f btnPos;
			btnPos.x = wRes.x * 0.88 - (rectSize.x / 2);
			btnPos.y = ((((wRes.y * 0.5) / buttonsLayout.size() / 2)) * (btnCount)-rectSize.y / 2);

			btn->setPosition(btnPos);

			btn->drawButtons(mainWindow);

			++btnCount;
		}
	}

}

void Field::drawPoints(const int points, const int mode)
{
	if (mode == 0)
	{
		pointsText->setString("Your points: ##" + std::to_string(points) + "##");
	}
	if (mode == 1)
	{
		pointsText->setString("      GameOver!\nTotal points is : #" + std::to_string(points) + "#");
	}
	pointsText->setPosition(mainWindow->getSize().x / 2 - (pointsText->getGlobalBounds().width / 2), mainWindow->getSize().y / 10 - pointsText->getGlobalBounds().height);
	pointsText->setFillColor(sf::Color::White);
	mainWindow->draw(*pointsText);

}


void Field::drawDebugMessage(std::string text)
{
	debugText->setString(text);
	debugText->setPosition(mainWindow->getSize().x / 2 - (pointsText->getGlobalBounds().width / 2), mainWindow->getSize().y / 4 - pointsText->getGlobalBounds().height);
	mainWindow->draw(*debugText);
}


//////////////////////////////////////////////////
///_______________________________CONSRUCTOR_START


void Field::drawConstructField()
{
	for (int i = 0; i < MapH; ++i)
	{
		for (int j = 0; j < MapW; ++j)
		{
			if (constEmptyTaleMap[i][j] == '/')
			{
				spriteBox[3]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[3]);
			}
			else if (constEmptyTaleMap[i][j] == 'W')
			{
				spriteBox[0]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[0]);
			}
			else if (constEmptyTaleMap[i][j] == 'G')
			{
				spriteBox[1]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[1]);
			}
			else if (constEmptyTaleMap[i][j] == 'R')
			{
				spriteBox[2]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[2]);
			}
			else if (constEmptyTaleMap[i][j] == 'D')
			{
				spriteBox[4]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[4]);
			}
			else if (constEmptyTaleMap[i][j] == 'S')
			{
				spriteBox[7]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[7]);
			}
		}
	}
	for (int i = 0; i < startMapH; ++i)
	{
		for (int j = 0; j < startMapW; ++j)
		{
			if (emptyTaleMap[i][j] == 'W')
			{
			spriteBox[0]->setPosition(j * spriteWidth, i * spriteHeight);
			mainWindow->draw(*spriteBox[0]);
			}
			else if (emptyTaleMap[i][j] == 'G')
			{
			spriteBox[1]->setPosition(j * spriteWidth, i * spriteHeight);
			mainWindow->draw(*spriteBox[1]);
			}
			else if (emptyTaleMap[i][j] == 'R')
			{
			spriteBox[2]->setPosition(j * spriteWidth, i * spriteHeight);
			mainWindow->draw(*spriteBox[2]);
			}
			else if (emptyTaleMap[i][j] == 'D')
			{
			spriteBox[4]->setPosition(j * spriteWidth, i * spriteHeight);
			mainWindow->draw(*spriteBox[4]);
			}
			else if (emptyTaleMap[i][j] == 'S')
			{
				spriteBox[7]->setPosition(j * spriteWidth, i * spriteHeight);
				mainWindow->draw(*spriteBox[7]);
			}
			else
			{
			spriteBox[currentGroundSprite]->setPosition(j * spriteWidth, i * spriteHeight);
			mainWindow->draw(*spriteBox[currentGroundSprite]);
			}
		}
	}
}

void Field::constructorMode()
{
	if (takeTitle)
	{
		if (curSprite)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*getMainWindow());
			sf::Vector2f mp(mousePos.x, mousePos.y);
			curSprite->setPosition(mp);
			mainWindow->draw(*curSprite);
		}
	}
}

void Field::setLVLEmptyMap()
{
	for (int i = 0; i < 30; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			emptyTaleMap[i][j] = constEmptyTaleMap[i][j];
		}
	}
}

void Field::saveMap(std::string* map)
{
	for (int i = 0; i < startMapH; ++i)
	{
		for (int j = 0; j < startMapW; ++j)
		{
			map[i][j] = emptyTaleMap[i][j];
		}
	}

	customLVL = true;

}

void Field::reScaleSprites(const float Y, const float X)
{
	for (auto el : spriteBox)
	{
		el->setScale(Y, X);
	}
}

void Field::alreadyHaveStartPoint()
{
	if (curSpriteName == 'S')
	{
		for (int i = 0; i < startMapH; ++i)
		{
			for (int j = 0; j < startMapW; ++j)
			{
				if (emptyTaleMap[i][j] == 'S')
				{
					emptyTaleMap[i][j] = ' ';
				}
			}
		}
	}
}

void Field::correctPositionStartPoint()
{
	for (int i = 0; i < startMapH; ++i)
	{
		for (int j = 0; j < startMapW; ++j)
		{
			if (emptyTaleMap[i][j] == 'S')
			{
				if (i + 3 >= startMapH)
				{
					emptyTaleMap[i][j] = ' ';
					return;
				}
				
				if ((emptyTaleMap[i + 1][j] != ' ' && emptyTaleMap[i + 1][j] != 'G') ||
					(emptyTaleMap[i + 2][j] != ' ' && emptyTaleMap[i + 2][j] != 'G'))
				{
					emptyTaleMap[i][j] = ' ';
					return;
				}
			}
		}
	}
	
}

//Eggs

void Field::goToDefault()
{
	currentGroundSprite = startGroundSprite;
	currentWaterSprite = startWaterSprite;
}

void Field::goToEva()
{
	currentGroundSprite = 6;
	currentWaterSprite = 5;

}