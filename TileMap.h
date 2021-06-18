#pragma once

#ifndef TILEMAP_H
#define TILEMAP_H

#include "Includes.h"
#include "Tile.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <vector>

class TileMap {
private:
	// map details
	// TODO: save these to a file later
	float    gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	sf::Vector2u mapSize;
	std::vector<std::vector<std::vector<Tile>>> map; // x, y, layer

	// change the tiles but it don't work soooo
	// TODO:  make tiles random + fix the black fade effect when it first loads the tiles
	std::string randNumber;
	int randNumb;

	sf::Texture tileTexture;
	sf::IntRect textureRect;

public:
	TileMap();

	// Functions
	void update();
	void render(sf::RenderTarget& window);
};

#endif