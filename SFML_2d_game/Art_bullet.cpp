#include "Art_bullet.h"


Vector2f norm(const Vector2f& x, const Vector2f& y) {

	Vector2f all(abs(x.x - y.x), abs(x.y - y.y));
	float sqr = sqrt(((y.x - x.x) * (y.x - x.x)) + (y.y - x.y) * (y.y - x.y));
	return Vector2f(all.x / sqr, all.y / sqr);
}
float ve_vec(const Vector2f& x, const Vector2f& y) {
	
	Vector2f all(abs(x.x - y.x), abs(x.y - y.y));
	return sqrt(((y.x - x.x) * (y.x - x.x)) + (y.y - x.y) * (y.y - x.y));
}

Art_bullet::Art_bullet( const Vector2f& position) {
	setPosition(position);
	setRadius(10);
	setFillColor(Color::Red);
	setOrigin(2, 20);
	pos = position;
}


//CHASING BULLET FUNCTION
void Art_bullet::chasing(Player& player) {

	//CALCULATIN VELOCITY OF THE BULLET
	if (player.main.getPosition().x < this->getPosition().x && player.main.getPosition().y < this->getPosition().y) {
		velocity.x = -8 * norm(player.main.getPosition(), this->getPosition()).x;
		velocity.y = -8 * norm(player.main.getPosition(), this->getPosition()).y;
	}
	if (player.main.getPosition().x > this->getPosition().x && player.main.getPosition().y < this->getPosition().y) {
		velocity.x = 8* norm(player.main.getPosition(), this->getPosition()).x;
		velocity.y = -8 * norm(player.main.getPosition(), this->getPosition()).y;
	}
	if (player.main.getPosition().x < this->getPosition().x && player.main.getPosition().y > this->getPosition().y) {
		velocity.x = -8 * norm(player.main.getPosition(), this->getPosition()).x;
		velocity.y = 8* norm(player.main.getPosition(), this->getPosition()).y;
	}
	if (player.main.getPosition().x > this->getPosition().x && player.main.getPosition().y > this->getPosition().y) {
		velocity.x = 8 * norm(player.main.getPosition(), this->getPosition()).x;
		velocity.y = 8 * norm(player.main.getPosition(), this->getPosition()).y;
	}
	move(velocity.x, velocity.y);
	//ANIMATION OF THE BULLET
	if (ve_vec(pos, this->getPosition()) < ve_vec(pos, player.main.getPosition()) / 2) {
		acc_scale = 1 + (scale / 30);
		setScale(acc_scale, acc_scale);
		scale++;
	}else{
		acc_scale = 1 + (scale / 30);
		setScale(acc_scale, acc_scale);
		scale--;
	}
	if (player.main.getGlobalBounds().intersects(this->getGlobalBounds())) {
		if (player.if_umbrella == true) {
		}
		else {
			player.hp -= 3;
		}
	}
}