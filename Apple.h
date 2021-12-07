#ifndef APPLE_H
#define APPLE_H

#include "SFML/Graphics.hpp"

class Apple

{
public:
	Apple();

	~Apple();

	void setPosition(int x, int y);

	sf::Vector2f getPosition() const;

	void drawApple(sf::RenderWindow* mainWindow);

	int getCurX() const { return currentX; }

	int getCurY() const { return currentY; }

	sf::Vector2i getCurPosition() const;

	void setNewSprite(const char* path);

	void setOriginSprite();

private:

	int currentX = 0;

	int currentY = 0;

	sf::Texture* appleText = nullptr;

	sf::Texture* swapTexture = nullptr;

	sf::Sprite* appleSprite = nullptr;



	/// <summary>
	/// 
	/// </summary>
	const char* pathToOriginTexture = "resources\\apple.png";
};






























#endif // !APPLE_H

