#pragma once
#include "Bonus.h"
#include "Player.h"


//SMMO BONUS CLASS
class Ammo:public Bonus
{
private:
	Clock ammo_c;
public:
	Ammo(const Texture &texture, const Vector2f &position);
	void add_ammo(Player& player);
	bool visited = false;
};

