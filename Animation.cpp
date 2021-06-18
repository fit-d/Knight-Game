#include "Animation.h"

// inits
Animation::Animation(sf::Texture* entityTexture, sf::Vector2u imageCount, float switchTime) {
	this->imageCount = imageCount;
	this->switchTime = switchTime;

	this->totalTime = 0.0f;
	this->currentImage.x = 0;

	uvRect.width = entityTexture->getSize().x / float(this->imageCount.x);
	uvRect.height = entityTexture->getSize().y / float(this->imageCount.y);
}

// loop
void Animation::update(float deltaTime, int row) {
	// loop through the animation based on the row you want,
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}

	// redefine the rect's
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}