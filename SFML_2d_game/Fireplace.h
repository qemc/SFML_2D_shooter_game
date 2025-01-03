#pragma once
#include "Bonus.h"
#include "Player.h"

// CLASS RESPONSIBLE FOR FIREPLACE, CHILD CLASS OF BONUS
class Fireplace:public Bonus
{
private:
	Clock hp_clock;
public:
	Fireplace(const Texture &texture, const Vector2f& position, const IntRect& choose_sprite);
	void add_hp(Player &player);
	RectangleShape range;
};

