#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Art.h"
#include "Start.h"
#include "Walls.h"

//CLASS RESPONSIBLE FOR GAMEPLAY
class Game :public Sprite
{
public:
	Game(const Texture &testure);
	bool start = false;
	void shoot(Player &player, Enemy &enemy);
	bool win = false;
	bool lost = false;
	void win_game(Player& player, Start &start);
	void win_boss(Art& art);
};

