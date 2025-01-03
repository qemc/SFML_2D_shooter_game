#pragma once
#include "Soldiers.h"
#include "Bullets.h"
#include "Player.h"
#include "Art_bullet.h"			

//CLASS RESPONSIBLE FOR ARTYLLERY GAME MODE
class Art:public Soldiers
{
private:
	bool shoot = false;
	Vector2f current_pos;
	Vector2f shootDir;
	void draw(RenderTarget& target, RenderStates state)const override;
	vector<Art_bullet> bullets;
public:
	Art();
	void get_dir_vec_art(const Vector2f& mousepos, Player& player);
	Clock s_clock;
	int hp = 10;
};

