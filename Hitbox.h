#pragma once

#ifndef HITBOX_H
#define HITBOX_H

#include "Includes.h"
#include <iostream>

class Hitbox {
public:

public:
	sf::RectangleShape hitBox;

	Hitbox(sf::Color* outlineColor, float width, float height, float x, float y);

	// Functions
	void render(sf::RenderWindow& window);
	bool checkCollision(float fX, float fY, float fWidth, float fHeight, float sX, float sY, float sWidth, float sHeight);
	void update(float x, float y);
};

#endif