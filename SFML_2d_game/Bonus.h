#pragma once
#include "Soldiers.h"

//MOTHER CLASS OF AMMO AND FIREPLACE

class Bonus:public Sprite
{
public:
	bool is_ammo = false;
	Bonus() = default;
	virtual ~Bonus() = default;
};

