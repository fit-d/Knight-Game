#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Includes.h"
#include <iostream>

class Animation
{
private:
	sf::Vector2u entityTextureSize;

	// self explanatory
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;  // how much time has passed
	float switchTime; // how fast the animation plays

public:
	sf::IntRect uvRect;

	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	
	void update(float deltaTime, int row);
};

#endif