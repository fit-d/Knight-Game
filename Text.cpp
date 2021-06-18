#include "Text.h"

Text::Text(std::string textString, sf::Font* font, int charSize, sf::Vector2f pos, std::string soundBufferName, sf::Color textColor, sf::Color boxColor) {
	// this is just setting up all the text
	this->textBox.setSize(sf::Vector2f(800.f, 200.f));
	this->textBox.setFillColor(boxColor);
	this->textBox.setPosition(pos);

	this->textString = textString;
	this->baseText = "";
	this->totalTime = 0.f;

	this->charactersPrinted = 0;

	this->text.setFont(*font);
	this->text.setCharacterSize(charSize);
	this->text.setFillColor(textColor);
	this->text.setPosition(textBox.getPosition().x + 10, textBox.getPosition().y + 10);

	if (!textPlayBuffer.loadFromFile(soundBufferName))
		std::cout << "Button Hover ogg file could not be retrieved." << std::endl;

	textPlay.setBuffer(textPlayBuffer);
}

void Text::textUpd(float switchTime, float deltaTime) {
	// typewriter effect, everyframe it checks to see if the total time has passed the switch line 
	// and also checks if the string is done

	totalTime += deltaTime;

	if (totalTime >= switchTime && textString.length() > charactersPrinted) {
		totalTime -= switchTime;
		baseText += textString[charactersPrinted];
		charactersPrinted++;
		textPlay.play();
		text.setString(baseText);
	}
}

// pretty self-explanatory but sets the position and renders
void Text::setPosition(sf::Vector2f pos) {
	this->textBox.setPosition(pos);
	this->text.setPosition(textBox.getPosition().x + 10, textBox.getPosition().y + 10);
}

void Text::render(sf::RenderWindow& window) {
	window.draw(this->textBox);
	window.draw(this->text);
}