#include "Start.h"


Start::Start(const vector<Texture>& textures,const Texture& texture) {

	for (int i = 0; i < 7; i++) {
		Vector2f vector;
		image_pos.emplace_back(vector);
	}
	tick.setTexture(texture);
	tick2.setTexture(texture);
	image_pos[0].x = 10;
	image_pos[0].y = 10;
	image_pos[1].x = 250;
	image_pos[1].y = 10;
	image_pos[2].x = 490;
	image_pos[2].y = 10;
	image_pos[3].x = 10;
	image_pos[3].y = 290;
	image_pos[4].x = 10;
	image_pos[4].y = 580;
	image_pos[5].x = 250;
	image_pos[5].y = 580;
	image_pos[6].x = 490;
	image_pos[6].y = 580;

	for (int i = 0; i < textures.size(); i++) {
		Sprite sprite;
		sprite.setTexture(textures[i]);
		sprite.setScale(0.3, 0.3);
		sprite.setPosition(image_pos[i]);
		maps.emplace_back(sprite);
	}
	size = textures.size();
	font.loadFromFile("font/huston.otf");
	title.setFont(font);
	title.setPosition(300, 300);
	title.setCharacterSize(40);
	title.setString("steal the tank!");
	inst.setFont(font);
	inst.setPosition(300, 350);
	inst.setCharacterSize(20);
	inst.setString("choose map");
	result.setFont(font);
	result.setPosition(300, 380);
	result.setCharacterSize(20);
	enable_boss.setFont(font);
	enable_boss.setPosition(300, 410);
	enable_boss.setCharacterSize(20);
	enable_boss.setString("destroy the artylery");
	enable_tank.setFont(font);
	enable_tank.setPosition(300, 460);
	enable_tank.setCharacterSize(20);
	enable_tank.setString("steal the tank");
	enable.setSize(Vector2f(30, 30));
	enable.setPosition(600, 408);
	enable.setFillColor(Color::Transparent);
	enable.setOutlineColor(Color::White);
	enable.setOutlineThickness(3);
	enable_.setSize(Vector2f(30, 30));
	enable_.setPosition(600, 458);
	enable_.setFillColor(Color::Transparent);
	enable_.setOutlineColor(Color::White);
	enable_.setOutlineThickness(3);
	tick.setPosition(600, 408);
	tick.setScale(0, 0);
	tick2.setPosition(600, 458);
	tick2.setScale(0, 0);
	tick.setColor(Color::Green);
	tick2.setColor(Color::Green);
}
int Start::update(const Vector2f& m_pos) {
	Color c(160, 160, 160);
	for (int i = 0; i < size; i++) {
		if (maps[i].getGlobalBounds().contains(m_pos)) {
			maps[i].setColor(c);
		}
		else {
			maps[i].setColor(Color::White);
		}
		if (maps[i].getGlobalBounds().contains(m_pos) && Mouse::isButtonPressed(Mouse::Left)) {
			start = true;
			return i+1;
			break;
		}
		else {
			start = false;
		}
	}
	if (enable.getGlobalBounds().contains(m_pos) && Mouse::isButtonPressed(Mouse::Left) && boss==false && tick_c.getElapsedTime().asSeconds()>0.25) {
		tick.setScale(1, 1);
		boss = true;
		mode_art = true;
		mode_tank = false;
		tick_c.restart();
	}
	else if(enable.getGlobalBounds().contains(m_pos) && Mouse::isButtonPressed(Mouse::Left) && boss == true && tick_c.getElapsedTime().asSeconds() > 0.25) {
		tick.setScale(0, 0);
		boss = false;
		tick_c.restart();
		tank = true;
		mode_art = false;
		mode_tank = true;
	}
	if (enable_.getGlobalBounds().contains(m_pos) && Mouse::isButtonPressed(Mouse::Left) && tank == false && tick_c.getElapsedTime().asSeconds() > 0.25) {
		tick2.setScale(1, 1);
		tank = true;
		tick_c.restart();
		mode_art = false;
		mode_tank = true;
	}
	else if (enable_.getGlobalBounds().contains(m_pos) && Mouse::isButtonPressed(Mouse::Left) && tank == true && tick_c.getElapsedTime().asSeconds() > 0.25) {
		tank = false;
		tick2.setScale(0, 0);
		tick_c.restart();
		mode_art = true;
		mode_tank = false;
	}
	if (mode_tank == true) {
		tick2.setScale(1, 1);
		tick.setScale(0, 0);
	}
	if (mode_art == true) {
		tick.setScale(1, 1);
		tick2.setScale(0, 0);
	}
}

void Start::draw(RenderTarget& target, RenderStates state)const {
	for (int i = 0; i < size; i++) {
		target.draw(maps[i]);
	}
	target.draw(enable_boss);
	target.draw(this->title);
	target.draw(this->inst);
	target.draw(this->result);
	target.draw(this->enable);
	target.draw(this->tick);
	target.draw(this->enable_);
	target.draw(this->enable_tank);
	target.draw(tick2);
}