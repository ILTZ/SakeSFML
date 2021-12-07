#ifndef BUTTINS_H
#define BUTTONS_H

#include "SFML/Graphics.hpp"

#include <string>

class Button
{
private:

	const int btnStartSizeX = 280;

	const int btnStartSizeY = 80;

	bool isPressed = false;

	bool textToSwitch = false;

	bool needToSwitch = false;

	sf::RectangleShape* btnStay = nullptr;

	sf::RectangleShape* btnPressed = nullptr;

	std::string text;

	std::string switchedText;

	sf::Text* buttonText = nullptr;

	sf::Font textFont;

public:

	Button();

	~Button();

	void drawButtons(sf::RenderWindow* mainWindow);

////////////////////////////////////////////////////////////
//_____________________________________________GET/SET_START

	sf::Vector2f getBtnSize() const { if (btnStay) return btnStay->getSize(); }

	void setPosition(const sf::Vector2f position);

	sf::Vector2f getButtonPosition() const { if (btnStay) return btnStay->getPosition(); }

	void setText(const char* iText) { text = iText; }

	std::string getText() const { return text; }

	sf::Vector2f getSize() const { return btnStay->getSize(); }

	void setSize(const sf::Vector2f size);

	void setPressedStatus(const bool& value);

	bool getPressedStatus() const { return isPressed; }


	void setFont(sf::Font iF) { textFont = iF; }

	sf::Font getFont() const { return textFont; }

	//Text on button will change after click
	void setSwitchedText(const std::string& newText) { switchedText = newText; }

	//If u need to switch text after click
	void setNeedToSwitchText(const bool value) { needToSwitch = value; }

//_____________________________________________GET/SET_END
//////////////////////////////////////////////////////////
};





#endif // !BUTTINS_H

