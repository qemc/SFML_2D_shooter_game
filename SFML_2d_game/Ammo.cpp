#include "Ammo.h"
Ammo::Ammo(const Texture& texture, const Vector2f& position) {
	setTexture(texture);
	setPosition(position);
	setScale(0.5, 0.5);
	is_ammo = true;
}
void Ammo::add_ammo(Player& player) {
	if (player.main.getGlobalBounds().intersects(this->getGlobalBounds())&& ammo_c.getElapsedTime().asSeconds()>0.5) {
		player.ammo += 20;
		cout << "20 ammo added" << endl;
		ammo_c.restart();
		this->visited = true;
	}
}

