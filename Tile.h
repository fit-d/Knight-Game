#pragma once

#ifndef TILE_H
#define TILE_H

#include "Includes.h"

class Tile {
private:
	sf::RectangleShape tile;

public:
	Tile();
	Tile(float x, float y, float gridSizeF, const sf::Texture& tileTexture, const sf::IntRect& texture_rect);

	// functions
	void render(sf::RenderTarget& window);
};

#endif