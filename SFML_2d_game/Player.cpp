#include "Player.h"

Player::Player(const Texture &texture) {
	main.setPosition(50, 650);
	umbrella.setTexture(texture);
	umbrella.setScale(0, 0);
}

void Player::control() {

	aim.setPosition(main.getPosition());
	umbrella.setPosition(main.getPosition().x - 20, main.getPosition().y - 20);
	if (Keyboard::isKeyPressed(Keyboard::Key::W)) {
		velocity.x = 0;
		velocity.y = -5;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S)) {
		velocity.x = 0;
		velocity.y = 5;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
		velocity.x = -5;
		velocity.y = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D)) {
		velocity.x = 5;
		velocity.y = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
		velocity.x = 0;
		velocity.y = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::W) && Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
		velocity.x = 0;
		velocity.y = -10;

	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S) && Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
		velocity.x = 0;
		velocity.y = 10;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A) && Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
		velocity.x = -10;
		velocity.y = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D) && Keyboard::isKeyPressed(Keyboard::Key::LShift)) {
		velocity.x = 10;
		velocity.y = 0;
	}
	main.move(velocity.x, velocity.y );
}

void Player::get_dir_vec_player(const Vector2f& mousepos) {

	Vector2f dirVec_(mousepos.x - main.getPosition().x, mousepos.y - main.getPosition().y);
	dirVec = dirVec_;
	if (Mouse::isButtonPressed(Mouse::Left)) {
		Vector2f mousepos_(mouse_pos);
		mouse_pos = m_pos;
	}
	Vector2f currnentpos_ = main.getPosition();
	current_pos = currnentpos_;
		if (Mouse::isButtonPressed(Mouse::Left)&&p_clock_s.getElapsedTime().asSeconds() > 0.25 && ammo > 0) {
			mouse_pos = m_pos;
			m_pos2 = main.getPosition();
			if (mouse_pos.x < current_pos.x && mouse_pos.y < current_pos.y) {
				shootDir.x = -8  * norm(mouse_pos, current_pos).x;
				shootDir.y = -8  * norm(mouse_pos, current_pos).y;
			}
			else
			if (mouse_pos.x > current_pos.x && mouse_pos.y < current_pos.y) {
				shootDir.x = 8  * norm(mouse_pos, current_pos).x;
				shootDir.y = -8 * norm(mouse_pos, current_pos).y;
			}
			else
			if (mouse_pos.x < current_pos.x && mouse_pos.y > current_pos.y) {
				shootDir.x = -8  * norm(mouse_pos, current_pos).x;
				shootDir.y = 8  * norm(mouse_pos, current_pos).y;
			}
			else
			if (mouse_pos.x > current_pos.x && mouse_pos.y > current_pos.y) {
				shootDir.x = 8  * norm(mouse_pos, current_pos).x;
				shootDir.y = 8  * norm(mouse_pos, current_pos).y;
			}
			bullets_.emplace_back(Bullets(aim.getPosition(), shootDir, m_pos2));
			p_clock_s.restart();
			ammo--;
		}

	for (int i = 0; i < bullets_.size(); i++) {
		bullets_[i].move(bullets_[i].velocity.x, bullets_[i].velocity.y );
	}

	//deleting bullets our of window
	for (int i = 0; i < bullets_.size(); i++) {
		if (bullets_[i].getPosition().x > 700 || bullets_[i].getPosition().x < 0|| bullets_[i].getPosition().y > 700 || bullets_[i].getPosition().y < 0) {
			bullets_.erase(bullets_.begin()+i);
		}
	}
}


void Player::def() {
	if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
		velocity.x = 0;
		velocity.y = 0;
		umbrella.setScale(1, 1);
		if_umbrella = true;
	}
	else {
		if_umbrella = false;
		umbrella.setScale(0, 0);
	}
}


void Player::draw(RenderTarget& target, RenderStates state) const {
	for (int i = 0; i < bullets_.size(); i++) {
		target.draw(bullets_[i]);
	}
	target.draw(main, state);
	target.draw(aim, state);
	if (if_umbrella == true) {
		target.draw(umbrella);
	}
}
