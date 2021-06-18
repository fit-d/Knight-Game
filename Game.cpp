#include "Game.h"

// Constructors and Destructors
Game::Game() {
	// calls these functions
	this->initVariables();
	this->initWindow();

	// create buttons, x, y, width, height, textSize, font, string, idleColor, activeColor, hoverColor
	this->mainMenuBtn.reset(new Button(325.f, 235.f, 150.f, 50.f, 24, sf::Color::Black, this->font, "Play",
		sf::Color(255, 255, 255, 255), sf::Color(245, 245, 245, 255), sf::Color(240, 240, 240, 255)
		));

	this->skipIntro.reset(new Button(3000.f, 3000.f, 100.f, 25.f, 20, sf::Color::Black, this->font, ">>>",
		sf::Color(0, 0, 0, 255), sf::Color(35, 35, 35, 255),  sf::Color(60, 60, 60, 255)
		));

	this->player.reset(new Entity(sf::Vector2f(3.f, 3.f), 50.f, 100000.f, 100000.f, &playerTexture, sf::Vector2u(4,4), 0.20f));
	
	// textTest is just for a test text where it manually types out each letter
	// BROKEN
	//this->textTest.reset(new Text("you got hit!", &font, 20, sf::Vector2f(4000.f, 4000.f), "Sounds/textPlay.wav", sf::Color::White, sf::Color::Black));

	// get skele and camera
	this->skeletonTestOne.reset(new Enemy(sf::Vector2f(3.f, 3.f), 50.f, 100000.f, 100000.f, &skeletonTexture, sf::Vector2u(4, 4), 0.155f));
	this->skeletonTestTwo.reset(new Enemy(sf::Vector2f(3.f, 3.f), 50.f, 100000.f, 100000.f, &skeletonTexture, sf::Vector2u(4, 4), 0.155f));
	this->skeletonTestThree.reset(new Enemy(sf::Vector2f(3.f, 3.f), 50.f, 100000.f, 100000.f, &skeletonTexture, sf::Vector2u(4, 4), 0.155f));

	this->camera = sf::View(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
}

// manually delete the things we manually allocated
// ^ not needed anymore because of smart pointers
Game::~Game() {
	//delete this->window; // closes the window when we want it to
	//delete this->mainMenuBtn;
	//delete this->skipIntro;
	//delete this->player;
	//delete this->textTest;
	//delete this->skeleton;
}

// basic key input event's that i don't even use
void Game::pollEvents()
{
	while (this->window->pollEvent(this->gmEvent)) {
		switch (this->gmEvent.type) {
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					this->window->close();
				break;
		}
	}
}

// Functions
void Game::update() {
	// call other functions
	this->pollEvents();
	this->UpdMousePos();
	this->UpdateVisualEffects();
	this->CheckGameState();

	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	// std::cout << this->skeleton->enemyHitbox->hitBox.getSize().x << ":" << this->skeleton->enemyHitbox->hitBox.getPosition().y << std::endl;

	//std::cout << titleBackground.getPosition().x << " " << titleBackground.getPosition().y << std::endl;
	//std::cout << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << std::endl;
	//std::cout << scene << " " << lastScene << " " << fadeAmount << " " << fadeBlock.getPosition().x << " " << fadeBlock.getPosition().y << std::endl;

	// loop the music
	if (titleMusic.getStatus() != sf::Music::Status::Playing && scene < 1) {
		titleMusic.play();
	}

	if (gameMusic.getStatus() != sf::Music::Status::Playing && scene > 1) {
		gameMusic.play();
		titleMusic.stop();
	}

	dt = this->clock.getElapsedTime().asSeconds(); // get the delta time

	// these comments below were for the text testin
	// if (scene == 2 && fadeAmount == 0) {
		// this->textTest->textUpd(.085f, dt);
	// }

	// only let the character be controlable if he is on the playable screen.
	if (characterPlaying == true) {
		// update the character
		this->player->update(dt);
		this->player->setTextureRect();
	
		// update the enemy (skeleton for now)
		this->skeletonTestOne->update(dt);
		this->skeletonTestOne->setTextureRect();

		this->skeletonTestTwo->update(dt);
		this->skeletonTestTwo->setTextureRect();

		this->skeletonTestThree->update(dt);
		this->skeletonTestThree->setTextureRect();

		// gives the game a more lively feel
		this->camera.setCenter(
			std::floor(this->player->entitySprite.getPosition().x + (static_cast<float>(mousePos.x) - static_cast<float>(videoMode.width / 2)) / 5.5f), // used to be 5.5f
			std::floor(this->player->entitySprite.getPosition().y + (static_cast<float>(mousePos.y) - static_cast<float>(videoMode.height / 2)) / 5.5f)
		);
		
		// yes it's a pain but if the player collides with whatever that disgusting if statement is then do whatever is in the if statement
		if (this->player->updCollision(this->skeletonTestOne->enemyHitbox->hitBox.getPosition().x, this->skeletonTestOne->enemyHitbox->hitBox.getPosition().y, this->skeletonTestOne->enemyHitbox->hitBox.getSize().x, this->skeletonTestOne->enemyHitbox->hitBox.getSize().y) == true) {
			this->player->characterHit();
			this->skeletonTestOne->setPosition(3000, 3000);
		}

		if (this->player->updCollision(this->skeletonTestTwo->enemyHitbox->hitBox.getPosition().x, this->skeletonTestTwo->enemyHitbox->hitBox.getPosition().y, this->skeletonTestTwo->enemyHitbox->hitBox.getSize().x, this->skeletonTestTwo->enemyHitbox->hitBox.getSize().y) == true) {
			this->player->characterHit();
			this->skeletonTestTwo->setPosition(3000, 3000);
		}

		if (this->player->updCollision(this->skeletonTestThree->enemyHitbox->hitBox.getPosition().x, this->skeletonTestThree->enemyHitbox->hitBox.getPosition().y, this->skeletonTestThree->enemyHitbox->hitBox.getSize().x, this->skeletonTestThree->enemyHitbox->hitBox.getSize().y) == true) {
			this->player->characterHit();
			this->skeletonTestThree->setPosition(3000, 3000);
		}

		//switch (player->lives) {
		//case 0:
		//	exit(0);
		//	break;
		//default:
		//	break;
		//}

		//std::cout << this->player->entitySprite.getPosition().x << ":" << this->player->entitySprite.getPosition().x << std::endl;
	}

	// get the framerate
	this->window->setFramerateLimit(60);
	this->gameTime = this->clock.getElapsedTime();
	//std::cout << 1.0f / this->gameTime.asSeconds() << std::endl;
	fpsString = std::to_string(static_cast<int>(1.0f / gameTime.asSeconds()));
	fpsText.setString(fpsString);
	//fpsText.setPosition(this->player->playerHitbox->hitBox.getPosition().x + 17, this->player->playerHitbox->hitBox.getPosition().y - 17);
	fpsText.setPosition(camera.getCenter().x - 400, camera.getCenter().y - 305);
	this->clock.restart().asSeconds();
}

// updates the game state and scenes
/*
	{explanation}
	* you can see that some of the positions get sent to a random xy coordinate,
	* this is because even when you don't display it or draw it, it is still there
	* this is just so that some buttons don't get mixed etc

	cancerous code u gotta fix later
*/
void Game::CheckGameState() {
	if (scene == 1 && fadeAmount == 255) {
		this->mainMenuBtn->setPosition(3000001, 30000009);
		buildVersion.setString("");
		fadeBlock.setFillColor(sf::Color(0, 0, 0, fadeAmount));
		lastScene++;
		title.setString("");
		titleMusic.stop();
		introBackground.setPosition(-110,-80);
		gameMusic.play();
		titleBackground.setPosition(20000000, 20000000);
		introText.setPosition(100, 120);
		this->skipIntro->setPosition(325, 275);
	} else if (scene == 2 && fadeAmount == 255) {
		characterPlaying = true;
		introBackground.setPosition(3000000, 3000000);
		introText.setString("");
		this->skipIntro->setPosition(3000000, 3000000);
		this->player->setPosition(100.f, 100.f);
		lastScene = 2;
		// textTest->setPosition(sf::Vector2f(0.f, 400.f));
		skeletonTestOne->setPosition(200.f, 200.f);
		skeletonTestTwo->setPosition(100.f, 400.f);
		skeletonTestThree->setPosition(150.f, 300.f);
	}
}

// visual effects such as clouds moving, fade in fade out
void Game::UpdateVisualEffects() {
	// fade out, don't know my own code even works LMAO
	if (scene == 1 && fadeAmount != 255 && lastScene == 0) {
		fadeAmount += 3;
		fadeBlock.setFillColor(sf::Color(0, 0, 0, fadeAmount));
	} else if (lastScene == 1 && fadeAmount != 0 && scene == 1) {
		fadeAmount -= 3;
		fadeBlock.setFillColor(sf::Color(0, 0, 0, fadeAmount));
	} else if (scene == 2 && lastScene == 1 && fadeAmount != 255) {
		fadeAmount += 3;
		fadeBlock.setFillColor(sf::Color(0, 0, 0, fadeAmount));
	} else if (lastScene == 2 && fadeAmount != 0) {
		fadeAmount -= 3;
		fadeBlock.setFillColor(sf::Color(0, 0, 0, fadeAmount));
	}

	// move the clouds
	if (scene == 0 && titleBackground.getPosition().x < -80 && reachedCloud == false) {
		titleBackground.move(0.3f, 0.f);
		if (reachedCloud == false && titleBackground.getPosition().x >= -80)
			reachedCloud = true;
	}
	else if (scene == 0 && titleBackground.getPosition().x > -400 && reachedCloud == true) {
		titleBackground.move(-0.3f, 0.f);
		if (reachedCloud == true && titleBackground.getPosition().x <= -400)
			reachedCloud = false;
	}
}

void Game::render() {
	// render
	this->window->clear(sf::Color(255, 219, 219, 255)); // clears the frame before it

	//this->map.render(*window);

	if (characterPlaying == true) {
		window->setView(camera);
		this->map.render(*window);
	}
	
	window->draw(titleBackground);
	window->draw(introBackground);
	
	this->mainMenuBtn->render(*window);
	this->skipIntro->render(*window);

	window->draw(title);
	window->draw(introText);

	this->player->render(*window);

	window->draw(buildVersion);
	window->draw(fadeBlock);
	
	this->skeletonTestOne->render(*window);
	this->skeletonTestTwo->render(*window);
	this->skeletonTestThree->render(*window);

	window->draw(fpsText);

	window->display(); // display it
}


void Game::UpdMousePos() {
	// mouse positions
	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

	// Button class has a update function that needs the mouse pos
	this->mainMenuBtn->update(mousePosF);
	this->skipIntro->update(mousePosF);

	// is the button pressed?
	if (this->mainMenuBtn->checkButtonState() == BTN_PRESSED) {
		scene = 1;
		buttonHover.play(); // sound effect gets repeated f
	}
	if (this->skipIntro->checkButtonState() == BTN_PRESSED) {
		scene = 2;
		buttonHover.play();
	}
}

// Private Functions
void Game::initVariables() {
	// nullptr so it doesn't gain a random memory address
	this->window = nullptr;

	// Fade In Variables
	totalTime = 0.f;
	switchTime = 0.5f;

	scene = 0;
	lastScene = 0;

	fpsText.setFont(font);
	fpsText.setFillColor(sf::Color::White);
	fpsText.setPosition(0, 20);
	fpsText.setCharacterSize(22);

	fadeAmount = 0;

	characterPlaying = false;

	buildString = "v0.0.1";

	playerTexture.loadFromFile("Sprites/Player/characterSpritesheet.png");
	skeletonTexture.loadFromFile("Sprites/Enemies/skeletonSpritesheet.png");

	dt = 0.f;

	if (!font.loadFromFile("perfectdos.ttf"))
		std::cout << "Font could not load" << std::endl;

	fadeBlock.setSize(sf::Vector2f(800, 600));
	fadeBlock.setPosition(0, 0);
	fadeBlock.setFillColor(sf::Color(0, 0, 0, fadeAmount));

	introText.setFont(font);
	introText.setString("This is just a test. This is just a test. This is just a test. This is just a test.\nThis is just a test. This is just a test. This is just a test. This is just a test.\nThis is just a test.");
	introText.setPosition(1000, 1060);
	introText.setCharacterSize(20);
	introText.setFillColor(sf::Color::Black);

	buildVersion.setFont(font);
	buildVersion.setString(buildString);
	buildVersion.setPosition(static_cast<float>(videoMode.width) / 2.f, 580.f);
	buildVersion.setCharacterSize(20);
	buildVersion.setFillColor(sf::Color::White);

	title.setFont(font);
	title.setString(/*"Knight of Conflict"*/"Test Title");
	title.setPosition(215, 175);
	title.setCharacterSize(38);
	title.setFillColor(sf::Color::White);

	if (!titleMusic.openFromFile("Sounds/title.ogg"))
		std::cout << "Music could not be loaded" << std::endl;

	if (!gameMusic.openFromFile("Sounds/gamePlay.ogg"))
		std::cout << "Music could not be loaded" << std::endl;

	if (!titleBackgroundTexture.loadFromFile("Sprites/Background/background.png"))
		std::cout << "Background could not be loaded" << std::endl;

	if (!buttonHoverBuffer.loadFromFile("Sounds/buttonHover.wav"))
		std::cout << "Button Hover ogg file could not be retrieved." << std::endl;

	if (!introBackgroundTexture.loadFromFile("Sprites/Background/introBackground.png"))
		std::cout << "Background could not be loaded" << std::endl;

	buttonHover.setBuffer(buttonHoverBuffer);

	//introBackground.setTexture(introBackgroundTexture);
	//introBackground.setPosition(2000, 2000);
	//introBackground.setScale(sf::Vector2f(0.75, 0.75));

	titleBackground.setTexture(titleBackgroundTexture);
	titleBackground.setPosition(-250, -200);
}
 
void Game::initWindow() {
	// setting up the height and width of the screen
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	// redefining it to make it into a window
	this->window.reset(new sf::RenderWindow(this->videoMode, /*"Knight of Conflict"*/"Test Title", sf::Style::Titlebar | sf::Style::Close)); 
}

//TODO: actually finish this fade in and out function
void Game::Fade() {
	totalTime += dt;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		fadeAmount++;
	}
}

// Accessors
void Game::run() {
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}