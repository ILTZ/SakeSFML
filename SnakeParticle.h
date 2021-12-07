#ifndef SNAKE_PARTICLE_H
#define SNAKE_PARTICLE_H

#include <SFML/Graphics.hpp>


class SnakeParticle
{
private:

	int currentLocation_X = 0;

	int currentLocation_Y = 0;

	sf::CircleShape *body = nullptr;

	sf::Texture* mainText = nullptr;

	sf::Texture* swapText = nullptr;

	bool evaModeON = false;


public:

	SnakeParticle(const char* iPath);

	~SnakeParticle();


	int getCurX() const { return currentLocation_X; }

	int getCurY() const { return currentLocation_Y; }

	void changeLocation(int locX, int locY);

	void setNewSprite(const char* path);

	void setOriginSprite();

	void drawSprite(sf::RenderWindow* mWindow);

private:








};















#endif
