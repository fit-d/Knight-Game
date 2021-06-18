#include "Entity.h"

Entity::Entity(sf::Vector2f spriteScale, float movementSpeed, float x, float y, sf::Texture *entityTexture, sf::Vector2u imageCount, float switchTime) {
	this->entitySprite.setTexture(*entityTexture);
	this->entitySprite.setScale(spriteScale);

	speed = 5;
	
	this->entityAnimation = new Animation(entityTexture, imageCount, switchTime);
	
	this->entitySprite.setPosition(x, y);
	this->movementSpeed = movementSpeed;

	this->entitySprite.setOrigin(entitySprite.getScale() / 2.0f);
	this->entitySprite.setScale(3.f, 3.f);

	outlineColor = new sf::Color(sf::Color::Green);

	this->playerHitbox.reset(new Hitbox(outlineColor, 50.f, 75.f, entitySprite.getPosition().x, entitySprite.getPosition().y));

	walkingLeft = false;
	walkingRight = false;

	lives = 3;

	sword.reset(new Sword());
}

Entity::~Entity() {
	delete this->outlineColor;
}

void Entity::move(float dt, float dir_x, float dir_y) {
	this->entitySprite.move(dir_x * this->movementSpeed * dt, dir_y * movementSpeed * dt);
}

// character hit
void Entity::characterHit() {
	this->lives--;
	std::cout << lives << std::endl;
}

// TODO: fix up projectiles.
void Entity::update(float dt) {
	playerCenter = sf::Vector2f(this->playerHitbox->hitBox.getPosition().x, this->playerHitbox->hitBox.getPosition().y + 20);

	this->playerHitbox->update(entitySprite.getPosition().x - 2.5, entitySprite.getPosition().y + 15); // get hit box

	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		if (walkingLeft == true) {
			this->sword->update(playerCenter, -1.0f, 0.f);
		}
		else if (walkingRight == true) {
			this->sword->update(playerCenter, 1.0f, 0.f);
		}
	}

	// left and right idle animations
	if (walkingLeft == true) {
		entityAnimation->update(dt, 3);
	} else if (walkingRight == true) {
		entityAnimation->update(dt, 0);
	}

	// move the sprite + play the animation according to that
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->move(dt, 0, -speed);
		if (walkingLeft == true) {
			entityAnimation->update(dt, 2);
		} else if (walkingRight == true) {
			entityAnimation->update(dt, 1);
		} else {
			entityAnimation->update(dt, 1);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->move(dt, -speed, 0);
		entityAnimation->update(dt, 2);
		walkingLeft = true;
		walkingRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->move(dt, 0, speed);
		if (walkingLeft == true) {
			entityAnimation->update(dt, 2);
		} else if (walkingRight == true) {
			entityAnimation->update(dt, 1);
		} else {
			entityAnimation->update(dt, 1);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->move(dt, speed, 0);
		entityAnimation->update(dt, 1);
		walkingRight = true;
		walkingLeft = false;
	}
}

bool Entity::updCollision(float fX, float fY, float fWidth, float fHeight) {
	if (this->playerHitbox->checkCollision(fX, fY, fWidth, fHeight, this->playerHitbox->hitBox.getPosition().x, this->playerHitbox->hitBox.getPosition().y, this->playerHitbox->hitBox.getSize().x, this->playerHitbox->hitBox.getSize().y) == true) {
		return true;
	}
	else {
		return false;
	}
}

void Entity::setPosition(float x, float y) {
	this->entitySprite.setPosition(x, y);
}

// set the texture rect
void Entity::setTextureRect() {
	this->entitySprite.setTextureRect(entityAnimation->uvRect);
}

void Entity::render(sf::RenderWindow& window) {
	this->playerHitbox->render(window);
	this->sword->render(window);
	window.draw(this->entitySprite);
}