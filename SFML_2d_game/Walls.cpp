#include "Walls.h"
Walls::Walls(const Vector2f& position, const Vector2f& size) {


	setSize(size);
	setPosition(position);
	Color color(255, 0, 0);
	setFillColor(Color::Green);
	
}
void Walls::collision(Player &player) {
	
	//player collsion with walls

	this->playerBounds = player.main.getGlobalBounds();
	this->playerBounds.left = playerBounds.left + playerBounds.width / 2;
	this->playerBounds.top = playerBounds.top + playerBounds.height / 2;
	this->rectangleBounds = this->getGlobalBounds();

				
	if (playerBounds.top  < rectangleBounds.top 
		&& playerBounds.top + playerBounds.height < rectangleBounds.top + rectangleBounds.height
		&& playerBounds.left< rectangleBounds.left + rectangleBounds.width
		&& playerBounds.left + playerBounds.width>rectangleBounds.left) {

		player.velocity.y = 0.f;
		player.velocity.x = 0.f;
		player.main.setPosition(playerBounds.left, rectangleBounds.top - playerBounds.height/2);
	}
	//top
	if (playerBounds.top > rectangleBounds.top
		&& playerBounds.top + playerBounds.height > rectangleBounds.top + rectangleBounds.height
		&& playerBounds.left<rectangleBounds.left + rectangleBounds.width
		&& playerBounds.left + playerBounds.width>rectangleBounds.left) {

		player.velocity.y = 0.f;
		player.velocity.x = 0.f;
		player.main.setPosition(playerBounds.left, rectangleBounds.top + rectangleBounds.height + playerBounds.height / 2);
	}
	//right
	if (playerBounds.left < rectangleBounds.left
		&& playerBounds.left + playerBounds.width < rectangleBounds.left + rectangleBounds.width
		&& playerBounds.top<rectangleBounds.top + rectangleBounds.height
		&& playerBounds.top + playerBounds.height>rectangleBounds.top) {

		player.velocity.x = 0.f;
		player.velocity.y = 0.f;
		player.main.setPosition(rectangleBounds.left - playerBounds.width/2, playerBounds.top);
	}
	//left
	if (playerBounds.left > rectangleBounds.left
		&& playerBounds.left + playerBounds.width > rectangleBounds.left + rectangleBounds.width
		&& playerBounds.top<rectangleBounds.top + rectangleBounds.height
		&& playerBounds.top + playerBounds.height>rectangleBounds.top) {
		player.velocity.y = 0.f;
		player.velocity.x = 0.f;
		player.main.setPosition(rectangleBounds.left + rectangleBounds.width + playerBounds.height / 2, playerBounds.top);
	}
}


void Walls::bullet_collision(Player& player , Enemy &enemy) {

	for (int i = 0; i < player.bullets_.size(); i++) {
		if (player.bullets_[i].getGlobalBounds().intersects(this->getGlobalBounds())) {
			player.bullets_.erase(player.bullets_.begin() + i); 
		}
	}
	for (int i = 0; i < enemy.bullets.size(); i++) {
		if (enemy.bullets[i].getGlobalBounds().intersects(this->getGlobalBounds())) {
			enemy.bullets.erase(enemy.bullets.begin() + i);
		}
	}
	for (int i = 0; i < enemy.ch_bullets.size(); i++) {
		if (enemy.ch_bullets[i].getGlobalBounds().intersects(this->getGlobalBounds())) {
			enemy.ch_bullets.erase(enemy.ch_bullets.begin() + i);
		}
	}
}

void Walls::player_col(Player& player) {
	if (player.main.getPosition().x - player.main.getGlobalBounds().width / 2 < 0) {
		player.main.setPosition(2 + player.main.getGlobalBounds().width / 2, player.main.getPosition().y);
	}
	if (player.main.getPosition().x + player.main.getGlobalBounds().width / 2 > 700) {
		player.main.setPosition(698 - player.main.getGlobalBounds().width / 2, player.main.getPosition().y);
	}
	if (player.main.getPosition().y - player.main.getGlobalBounds().width / 2 < 0) {
		player.main.setPosition(player.main.getPosition().x, 2 + player.main.getGlobalBounds().width / 2);
	}
	if (player.main.getPosition().y + player.main.getGlobalBounds().width / 2 > 700) {
		player.main.setPosition(player.main.getPosition().x, 698 - player.main.getGlobalBounds().width / 2);
	}
}



