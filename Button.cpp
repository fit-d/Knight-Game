#include "Button.h"
#include "Game.h"

Button::Button(float x, float y, float width, float height, int fontSize, sf::Color color, sf::Font font, std::string text, sf::Color idleColor, sf::Color activeColor, sf::Color hoverColor) {
	this->buttonState = BTN_IDLE; // start off idle
	
	// button stuffs
	this->button.setPosition(sf::Vector2f(x, y));
	this->button.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(this->font);
	this->text.setString(text);
	this->text.setFillColor(color);
	this->text.setCharacterSize(fontSize);
	this->text.setPosition(
		this->button.getPosition().x + (this->button.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		(this->button.getPosition().y + (this->button.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f) - 5
	); // get the text to the middle of the button

	this->idleColor = idleColor;
	this->activeColor = activeColor;
	this->hoverColor = hoverColor;

	this->button.setFillColor(sf::Color(0, 0, 0, 0));

	//this->button.setFillColor(this->idleColor);
}

// Accessors
const bool Button::isPressed() const {
	// if button is pressed return true to notify that... the button is pressed
	if (this->buttonState == BTN_PRESSED)
		return true;

	return false;
}

// Functions
void Button::update(const sf::Vector2f mousePos) {
	// set it to idle, hover, or pressed depending on the state
	this->buttonState = BTN_IDLE;
	
	if (this->button.getGlobalBounds().contains(mousePos)) {
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = BTN_PRESSED;
		}
	}
	
	switch (this->buttonState) {
		case BTN_IDLE:
			this->text.setFillColor(this->idleColor);
			break;
		case BTN_HOVER:
			this->text.setFillColor(this->hoverColor);
			break;
		case BTN_PRESSED:
			this->text.setFillColor(this->activeColor);
			break;

		default:
			this->button.setFillColor(sf::Color::Red);
			break;
	}
}

// set the position
void Button::setPosition(int x, int y) {
	this->button.setPosition(x, y);
	this->text.setPosition(
		this->button.getPosition().x + (this->button.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		(this->button.getPosition().y + (this->button.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f) - 5
	);
}

// get the button state so in the Game.cpp file I can check if it's pressed or not
short unsigned Button::checkButtonState() {
	return buttonState;
}

// target is a pointer because we don't wanna draw a copy of something onto the window, we wanna draw the actual thing
void Button::render(sf::RenderWindow& window) {
	window.draw(this->button);
	window.draw(this->text);
}