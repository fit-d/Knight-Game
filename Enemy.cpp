#include "Enemy.h"

Enemy::Enemy(sf::Vector2f spriteScale, float movementSpeed, float x, float y, sf::Texture* enemyTexture, sf::Vector2u imageCount, float switchTime) {
	this->movementSpeed = movementSpeed;

	this->enemySprite.setTexture(*enemyTexture);
	this->enemySprite.setScale(spriteScale);

	this->enemyAnimation.reset(new Animation(enemyTexture, imageCount, switchTime));

	this->enemySprite.setPosition(x, y);
	this->movementSpeed = movementSpeed;

	outlineColor = new sf::Color(sf::Color::Red);

	this->enemyHitbox.reset(new Hitbox(outlineColor, 50.f, 50.f, enemySprite.getPosition().x, enemySprite.getPosition().y));

	this->walkingLeft = false;
	this->walkingRight = true;
}

Enemy::~Enemy() {
	delete this->outlineColor;
}

void Enemy::move(float dt, float dir_x, float dir_y) {
	this->enemySprite.move(dir_x * this->movementSpeed * dt, dir_y * movementSpeed * dt);
}

void Enemy::update(float dt) {
	this->enemyHitbox->update(enemySprite.getPosition().x, enemySprite.getPosition().y);

	/*
		* TODO: add AI
		the commented code below is just a basic script that makes the enemy walk left and right
	*/ 

	if (walkingRight == true) {
		enemyAnimation->update(dt, 2);
		this->move(dt, 2.f, 0.f);
		if (enemySprite.getPosition().x > 750) {
			walkingRight = false;
			walkingLeft = true;
		}
	}
	else if (walkingLeft == true) {
		enemyAnimation->update(dt, 3);
		this->move(dt, -2.f, 0.f);
		if (enemySprite.getPosition().x < 0) {
			walkingRight = true;
			walkingLeft = false;
		}
	}

	// updates the animation
	this->enemyAnimation->update(dt, 0);
}

void Enemy::setTextureRect() {
	this->enemySprite.setTextureRect(enemyAnimation->uvRect);
}

void Enemy::updCollision(float fX, float fY, float fWidth, float fHeight, float sX, float sY, float sWidth, float sHeight) {
	this->enemyHitbox->checkCollision(fX, fY, fWidth, fHeight, sX, sY, sWidth, sHeight);
}

void Enemy::setPosition(float x, float y) {
	this->enemySprite.setPosition(x, y);
}

void Enemy::render(sf::RenderWindow& window) {
	this->enemyHitbox->render(window);
	window.draw(this->enemySprite);
}
