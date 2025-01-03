#pragma once


#include "Bullets.h"
#include "Player.h"
#include "Enemy.h"

class Walls : public RectangleShape
{
private:
	FloatRect playerBounds;
	FloatRect rectangleBounds;
public:
	Walls(const Vector2f& position, const Vector2f& size);
	void collision(Player &player);
	void bullet_collision(Player &player, Enemy& enemy);
	RectangleShape boss;
	Vector2f boss_velocity;
	void player_col(Player &player);
};

