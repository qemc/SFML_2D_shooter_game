#include "Art.h"


Art::Art() {

	main.setFillColor(Color::Transparent);
	main.setRadius(15);
	main.setOutlineThickness(2);
	main.setOutlineColor(Color::White);
	main.setOrigin(15, 15);
	aim.setFillColor(Color::Red);
	aim.setRadius(6);
	aim.setOrigin(2, 20);
}
void Art::get_dir_vec_art(const Vector2f& mouse_pos,Player &player) {
	update();
	get_dir_vec(mouse_pos);
	main.setRadius(15);
	main.setOrigin(15, 15);
	aim.setFillColor(Color::Red);
	aim.setRadius(6);
	this->aim.setPosition(this->main.getPosition());
	if (s_clock.getElapsedTime().asSeconds() > 4) {
		bullets.emplace_back(Art_bullet(this->aim.getPosition()));
		s_clock.restart();
	}
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].chasing(player);
	}


	for (auto itr = bullets.begin(); itr != bullets.end();) {
		if (itr->getGlobalBounds().intersects(player.main.getGlobalBounds())) {
			itr = bullets.erase(itr);
		}
		else {
			++itr;
		}
	}


	for (auto itr = player.bullets_.begin(); itr != player.bullets_.end();) {
		if (itr -> getGlobalBounds().intersects(this->main.getGlobalBounds())) {
			itr = player.bullets_.erase(itr);
			hp--;
		}
		else {
			++itr;
		}
	}
}

void Art::draw(RenderTarget& target, RenderStates state) const {
	target.draw(main, state);
	target.draw(aim, state);
	for (int i = 0; i < this->bullets.size(); i++)
	{
		target.draw(bullets[i]);
	}
}