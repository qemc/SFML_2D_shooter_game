#pragma once

//CPP
#include <iostream>
#include "Bullets.h"
#include <vector>
#include <memory>
#include <math.h>
//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// MOTHER CLASS OF ENEMIES AND PLAYER, RESPONSIBLE FOR THEIR ANIMATION
class Soldiers:public CircleShape
{
private:
	Vector2f base_position;
	Vector2f shootDir;
	Vector2f mouse_pos;
	Vector2f current_pos;
protected:
	Vector2f dirVec;
public:
	static Clock movement;
	int hp = 5;
	Soldiers() = default;
	virtual ~Soldiers() = default;
	CircleShape aim;
	CircleShape main;
	void get_dir_vec(const Vector2f& mouse_pos);
	void set_circles();
	void update();
	void draw(RenderTarget& target, RenderStates state) const override;
	float angle(Vector2f dirVec);
	Vector2f norm(const Vector2f& x, const Vector2f& y);
};

