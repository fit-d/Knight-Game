#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Sword.h"
#include "Includes.h"
#include "Animation.h"
#include "Hitbox.h"
#include <memory>

class Entity {
private:
	Animation* entityAnimation;

	sf::Color* outlineColor;

	std::unique_ptr<Sword> sword;

	sf::Vector2f playerCenter;

	bool walkingLeft, walkingRight;

	float movementSpeed;

public:
	std::unique_ptr<Hitbox> playerHitbox;
	sf::Sprite entitySprite;
	int speed;
	int lives;

	Entity(sf::Vector2f spriteScale, float movementSpeed, float x, float y, sf::Texture* entityTexture, sf::Vector2u imageCount, float switchTime);
	~Entity();

	// func
	void move(float dt, float dir_x, float dir_y);
	void update(float dt);
	void setPosition(float x, float y);
	void setTextureRect();
	void characterHit();
	bool updCollision(float fX, float fY, float fWidth, float fHeight);
	void render(sf::RenderWindow& window);
};

#endif