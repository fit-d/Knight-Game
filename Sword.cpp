#include "Sword.h"

Sword::Sword() {
	projectile.setSize(sf::Vector2f(15.f, 5.f));
	projectile.setFillColor(sf::Color::Red);

	projectiles.push_back(sf::RectangleShape(projectile));
}

void Sword::update(sf::Vector2f playerCenter, float x_spd, float y_spd) {
	projectile.setPosition(playerCenter);
	projectiles.push_back(sf::RectangleShape(projectile));

	//for (size_t i = 0; i < projectiles.size(); i++) {
	//	projectiles[i].move(x_spd, y_spd);

		//if (projectiles[i].getPosition().x > 0) {
		//	projectiles.erase(projectiles.begin() + i);
		//}
	//}
}

void Sword::render(sf::RenderTarget& target) {
	for (size_t i = 0; i < projectiles.size(); i++)
		target.draw(this->projectiles[i]);
}