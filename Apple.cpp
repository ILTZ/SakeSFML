#include "Apple.h"


Apple::Apple()
{
	appleText = new sf::Texture();
	appleText->loadFromFile(pathToOriginTexture);
	appleSprite = new sf::Sprite(*appleText);


}

void Apple::setPosition(int x, int y)
{
	currentX = x;
	currentY = y;
}

sf::Vector2f Apple::getPosition() const 
{
	return appleSprite->getPosition();
}

void Apple::drawApple(sf::RenderWindow* mainWindow)
{
	appleSprite->setPosition(currentX * 40.0, currentY * 40.0);
	if (appleSprite)
	{
		mainWindow->draw(*appleSprite);
	}
}

Apple::~Apple()
{

}

sf::Vector2i Apple::getCurPosition() const
{
	sf::Vector2i curPos;
	curPos.x = currentX;
	curPos.y = currentY;

	return curPos;
}

void Apple::setNewSprite(const char* path)
{
	swapTexture = new sf::Texture();
	swapTexture->loadFromFile(path);
	appleSprite->setTexture(*swapTexture);

}

void Apple::setOriginSprite()
{
	appleSprite->setTexture(*appleText);

	delete swapTexture;
}