#include "Buttons.h"



Button::Button()
{
	//BtnStay__________________________________
	sf::Texture* text2 = new sf::Texture();
	text2->loadFromFile("resources\\buttonStay.png");

	btnStay = new sf::RectangleShape(sf::Vector2f(btnStartSizeX, btnStartSizeY));
	btnStay->setTexture(text2);


	//BtnPressed_______________________________
	sf::Texture* text3 = new sf::Texture();
	text3->loadFromFile("resources\\buttonPressed.png");

	btnPressed = new sf::RectangleShape(sf::Vector2f(btnStartSizeX, btnStartSizeY));
	btnPressed->setTexture(text3);

	textFont.loadFromFile("resources\\Maler.ttf");

	buttonText = new sf::Text();
	buttonText->setFont(textFont);
	buttonText->setCharacterSize(30);
	buttonText->setFillColor(sf::Color::Black);
	buttonText->setStyle(sf::Text::Italic);


}

Button::~Button()
{
	delete btnStay;
	delete btnPressed;
	delete buttonText;
}

void Button::drawButtons(sf::RenderWindow* mainWindow)
{
	if (btnPressed && btnStay)
	{
		buttonText->setString(text);

		if (isPressed)
		{
			mainWindow->draw(*btnPressed);
			mainWindow->draw(*buttonText);
			
		}
		else
		{
			mainWindow->draw(*btnStay);	
			mainWindow->draw(*buttonText);
		}
	}
}

void Button::setPosition(const sf::Vector2f position)
{
	if (btnPressed && btnStay)
	{
		btnPressed->setPosition(position);
		btnStay->setPosition(position);


		//Text offset after click/realease mouseBtn
		if (!isPressed)
		{
			buttonText->setPosition(position.x + ((btnStay->getSize().x / 2) - (buttonText->getGlobalBounds().width / 2)),
				position.y + ((btnStay->getSize().y / 2) - (buttonText->getGlobalBounds().height)));
		}
		else 
		{
			buttonText->setPosition(position.x + ((btnStay->getSize().x / 2) - (buttonText->getGlobalBounds().width / 2)),
				position.y + ((btnStay->getSize().y / 2) - (buttonText->getGlobalBounds().height)) + 14.0);
		}
	}
}

void Button::setSize(const sf::Vector2f size)
{
	if (btnPressed && btnStay)
	{
		btnPressed->setSize(size);
		btnStay->setSize(size);
	}
}

void Button::setPressedStatus(const bool& value)
{
	isPressed = value;
	
	if (!isPressed)
	{
		textToSwitch = !textToSwitch;
		if (needToSwitch)
		{
			std::string temp = text;
			text = switchedText;
			switchedText = temp;
		}
	}
}