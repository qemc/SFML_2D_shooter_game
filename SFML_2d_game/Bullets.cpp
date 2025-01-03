#include "Bullets.h"


Bullets::Bullets(const Vector2f& position, const Vector2f& velocity_, const Vector2f &m_pos) {
	setPosition(position);
	setRadius(4);
	velocity = velocity_;
	setOrigin(4, 4);
	player_shoot_pos = m_pos;

}












