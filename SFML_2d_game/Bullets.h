#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

//CLASS RESPONSIBLE FOR PLAYER AND ENEMY BULLETS

class Bullets:public CircleShape
{
private:
	Vector2f player_shoot_pos;
public:
	Vector2f velocity;
	Bullets(const Vector2f &position, const Vector2f& velocity_,const Vector2f& m_pos);	
};

