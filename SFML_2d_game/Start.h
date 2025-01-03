#pragma once
#include "Menu.h"
//CLASS RESPONSIBLE FOR STARTING MENU 
class Start:public Menu
{
private:
	Font font;
	Text title;
	Text inst;
	vector<Vector2f> image_pos;
	int size;
	void draw(RenderTarget& target, RenderStates state)const override;
	bool boss = false;
	bool tank = true;
	RectangleShape enable;
	RectangleShape enable_;
	Text enable_tank;
	Sprite tick;
	Sprite tick2;

public:
	Start(const vector<Texture> &textures,const Texture &texture);
	bool mode_tank = true;
	bool mode_art = false;
	bool start = false;
	int update(const Vector2f &m_pos);	
	Text result;
	Text enable_boss;
	Vector2f m_pos_;
	vector<Sprite> maps;
	Clock tick_c;
};

