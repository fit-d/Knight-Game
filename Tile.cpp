#include "Tile.h"

Tile::Tile() {

}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture& tileTexture, const sf::IntRect& texture_rect) {
	this->tile.setTexture(&tileTexture);
	this->tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->tile.setPosition(x, y);
	this->tile.setTextureRect(texture_rect);
}

void Tile::render(sf::RenderTarget& window) {
	window.draw(this->tile);
}
