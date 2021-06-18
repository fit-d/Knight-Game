#pragma once

#ifndef GAME_H
#define GAME_H

#include "Button.h"
#include "Entity.h"
#include "Includes.h"
#include "Text.h"
#include "Enemy.h"
#include "TileMap.h"
#include <memory>
#include <fstream>
#include <iostream>
#include <string>

class Game {
private: 
	// Variables
	std::unique_ptr<sf::RenderWindow> window;
	sf::VideoMode videoMode;
	sf::Event gmEvent;

	std::unique_ptr<Button> mainMenuBtn;
	std::unique_ptr<Button> skipIntro;

	// BROKEN
	// std::unique_ptr<Text> textTest;

	std::unique_ptr<Entity> player;

	std::unique_ptr<Enemy> skeletonTestOne;
	std::unique_ptr<Enemy> skeletonTestTwo;
	std::unique_ptr<Enemy> skeletonTestThree;

	TileMap map;

	sf::View camera;
	
	sf::Font font;
	sf::Text title;

	std::string buildString;
	sf::Text buildVersion;

	sf::Texture playerTexture;
	sf::Texture skeletonTexture;
	
	std::string fpsString;
	sf::Text fpsText;

	float dt;

	bool reachedCloud;

	bool reachedDevMode; // check to see if i have pressed the H key which shows me a bunch of different statistics

	sf::Time gameTime;
	sf::Clock clock;

	sf::Music titleMusic;
	sf::Music gameMusic;
	
	sf::SoundBuffer buttonHoverBuffer;
	sf::Sound buttonHover;

	sf::Text introText;

	sf::RectangleShape fadeBlock;
	int fadeAmount;

	bool characterPlaying; // should the character be able to move?

	// scene and check to see if they already removed last scene
	int scene;
	int lastScene;

	sf::Vector2i mousePos;
	sf::Vector2f mousePosF;

	sf::Texture introBackgroundTexture;
	sf::Sprite introBackground;

	sf::Texture titleBackgroundTexture;
	sf::Sprite titleBackground;

	// Private Functions
	void initVariables();
	void initWindow();

	// Fade In Effect Variables
	float totalTime;
	float switchTime;

public:
	// constructor & destructor
	Game();
	virtual ~Game();

	// Accessors
	void run();

	// Functions
	void pollEvents();
	void update();
	void render();
	void UpdMousePos();
	void CheckGameState();
	void UpdateVisualEffects();
	void Fade();
};

#endif