#include "SnakeParticle.h"

SnakeParticle::SnakeParticle(const char* iPath)
{


	mainText = new sf::Texture();
	mainText->loadFromFile(iPath);



	body = new sf::CircleShape(20.0);
	body->setOrigin(body->getRadius(), body->getRadius());
	body->setRotation(0);
	body->setTexture(mainText);
	

}

SnakeParticle::~SnakeParticle()
{
	delete body;
}

void SnakeParticle::changeLocation(int locX, int locY)
{
	
	if (locY > currentLocation_Y)
	{
		body->setRotation(180);
	}
	else if (locY < currentLocation_Y)
	{
		body->setRotation(0);
	}

	if (locX > currentLocation_X)
	{
		body->setRotation(90);
	}
	else if (locX < currentLocation_X)
	{
		body->setRotation(270);
	}


	currentLocation_X = locX;
	currentLocation_Y = locY;
}

void SnakeParticle::drawSprite(sf::RenderWindow* mWindow)
{
	body->setPosition(currentLocation_X * 40 + 20, currentLocation_Y * 40 + 20);
	mWindow->draw(*body);


}

void SnakeParticle::setNewSprite(const char* path)
{
	swapText = new sf::Texture();
	swapText->loadFromFile(path);

	body->setTexture(swapText);

}

void SnakeParticle::setOriginSprite()
{
	body->setTexture(mainText);
	delete swapText;
}