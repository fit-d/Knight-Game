#include "TileMap.h"

// TODO: make the floor tiles randomized
TileMap::TileMap() {
	srand(time(NULL));

	this->gridSizeF = 40.f;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->mapSize.x = 10;
	this->mapSize.y = 10;
	this->layers    = 1;

	tileTexture.loadFromFile("Sprites/Tile/floor_1.png");

	// tileTexture.loadFromFile("Sprites/Tile/floor_1.png");
	this->textureRect = sf::IntRect(0, 0, 16, 16);

	// makes the tiles which will be all rendered in one frame later on
	this->map.resize(this->mapSize.x);
	for (size_t x = 0; x < this->mapSize.x; x++) {
		this->map.push_back(std::vector<std::vector<Tile>>());

		for (size_t y = 0; y < this->mapSize.y; y++) {
			this->map[x].resize(this->mapSize.y);
			this->map[x].push_back(std::vector<Tile>());

			this->map[x][y].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, tileTexture, textureRect));

			//for (size_t z = 0; z < this->layers; z++) {
			//	this->map[x][y].resize(this->layers);
			//	this->map[x][y].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, tileTexture, textureRect));
			//}
		}
	} 
}

// get a random tile
void TileMap::update() {
	randNumb = rand() % 8 + 1;
	//std::cout << randNumb << std::endl;
	randNumber = "Sprites/Tile/floor_" + std::to_string(randNumb) + ".png";
	tileTexture.loadFromFile(randNumber);
	//std::cout << randNumber << std::endl;
}

// render the tiles
void TileMap::render(sf::RenderTarget& window) {
	for (auto& x : this->map) {
		for (auto& y : x) {
			for (auto& z : y) {
				z.render(window);
			}
		}
	}
}