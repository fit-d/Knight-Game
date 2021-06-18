#include "Hitbox.h"

Hitbox::Hitbox(sf::Color* outlineColor, float width, float height, float x, float y) {
	this->hitBox.setFillColor(sf::Color::Transparent);
	this->hitBox.setOutlineThickness(-1.f);
	this->hitBox.setOutlineColor(*outlineColor);
	this->hitBox.setSize(sf::Vector2f(width, height));
	this->hitBox.setPosition(x, y);
}

void Hitbox::update(float x, float y) {
	this->hitBox.setPosition(x, y);
}

bool Hitbox::checkCollision(float fX, float fY, float fWidth, float fHeight, float sX, float sY, float sWidth, float sHeight) {
	return fX < sX + sWidth && fX + fWidth > sX && fY < sY + sHeight && fY + fHeight > sY;
}

void Hitbox::render(sf::RenderWindow& window) {
	window.draw(this->hitBox);
}