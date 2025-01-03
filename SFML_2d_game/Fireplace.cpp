#include "Fireplace.h"


Fireplace::Fireplace(const Texture& texture, const Vector2f& position, const IntRect& choose_sprite) {
	setTexture(texture);
	setPosition(position);
	setTextureRect(choose_sprite);
	setScale(0.5, 0.5);
	range.setSize(Vector2f(64, 64));
	range.setFillColor(Color::Red);
	range.setPosition(position);
}

void Fireplace::add_hp(Player& player) {

	if (player.main.getGlobalBounds().intersects(this->range.getGlobalBounds()) && hp_clock.getElapsedTime().asSeconds() > 5) {
		player.hp++;
		cout << player.hp << endl;
		hp_clock.restart();
	}
}