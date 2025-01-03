#include "Game.h"
#include "Fireplace.h"

Game::Game(const Texture& texture) {
	setTexture(texture);
	setScale(0.5, 0.5);
}
void Game::shoot(Player& player, Enemy& enemy) {
	for (auto s = player.bullets_.begin(); s != player.bullets_.end();) {
		if(s->getGlobalBounds().intersects(enemy.main.getGlobalBounds())) {
			s = player.bullets_.erase(s);
			enemy.hp--;
		}
		else {
			++s;
		}
	}
	for (auto s = enemy.bullets.begin(); s != enemy.bullets.end();) {
		if (s->getGlobalBounds().intersects(player.main.getGlobalBounds())) {

			player.hp--;
			s = enemy.bullets.erase(s);
		}
		else {
			++s;
		}
	}
}

void Game:: win_game(Player& player, Start& start) {
	if (player.main.getGlobalBounds().intersects(this->getGlobalBounds())) {
		win = true;
	}
}

void Game::win_boss(Art& art) {
	if (art.hp == 0) {

		win = true;

	}
}
