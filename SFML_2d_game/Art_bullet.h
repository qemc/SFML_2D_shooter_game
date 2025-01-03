#pragma once
#include "Soldiers.h"
#include "Player.h"

//CLASS RESPONSIBLE FOR ARTYLERTY BULLET

class Art_bullet:public CircleShape
{
private:
	Vector2f velocity;
	Vector2f pos;
	float scale = 1;
	float acc_scale;

public:
	Art_bullet(const Vector2f &position);
	void chasing(Player& player);
};

