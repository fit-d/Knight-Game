#pragma once

#ifndef SWORD_H
#define SWORD_H

#include "Includes.h"
#include <iostream>
#include <vector>

class Sword {
private:
	std::vector<sf::RectangleShape> projectiles;
	sf::RectangleShape projectile;

public:
	Sword();

	// Functions
	void update(sf::Vector2f playerCenter, float x_spd, float y_spd);
	void render(sf::RenderTarget& target);
};

#endif