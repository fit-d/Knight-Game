#pragma once

#ifndef TEXT_H
#define TEXT_H

#include "Includes.h"
#include <iostream>
#include <string>

class Text {
private:
	sf::RectangleShape textBox;
	sf::Text text;
	std::string baseText;
	std::string textString;

	float totalTime;
	int charactersPrinted;

	int lives = 3;

	sf::SoundBuffer textPlayBuffer;
	sf::Sound textPlay;

public:
	Text(std::string textString, sf::Font* font, int charSize, sf::Vector2f pos, std::string soundBufferName, sf::Color textColor, sf::Color boxColor);

	// Public Functions
	void render(sf::RenderWindow& window);
	void textUpd(float switchTime, float deltaTime);
	void setPosition(sf::Vector2f pos);
};

#endif