#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "Includes.h"
#include "Animation.h"
#include "Hitbox.h"
#include <ctime>
#include <cstdlib>

class Enemy {
private:
	std::unique_ptr<Animation> enemyAnimation;

	bool walkingRight;
	bool walkingLeft;

	sf::Color* outlineColor;

	float movementSpeed;

public:
	std::unique_ptr<Hitbox> enemyHitbox;
	sf::Sprite enemySprite;

	Enemy(sf::Vector2f spriteScale, float movementSpeed, float x, float y, sf::Texture* enemyTexture, sf::Vector2u imageCount, float switchTime);
	~Enemy();

	// Functions
	void move(float dt, float dir_x, float dir_y);
	void setTextureRect();
	void setPosition(float x, float y);
	void update(float dt);
	void updCollision(float fX, float fY, float fWidth, float fHeight, float sX, float sY, float sWidth, float sHeight);
	void render(sf::RenderWindow& window);
};

#endif