#include "Player.h"
#include "Enemy.h"
#include "Soldiers.h"
#include "Game.h"
#include "Bullets.h"
#include "Walls.h"
#include "Bonus.h"
#include "Fireplace.h"
#include "Ammo.h"
#include "Stats.h"
#include "Start.h"
#include "map_reader.h"
#include "Art.h"
#include <string>
#include <map>
#include <fstream>
#include <iostream>


using namespace std;
using namespace sf;
Vector2f Player::m_pos;
Clock Soldiers::movement;


int main() {

	//WINDOW ELEMENTS
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(700, 800), "Steal the tank!", Style::Default, settings);
	window.setFramerateLimit(60);
	//TEXTURES
	Texture umbrella;
	umbrella.loadFromFile("images/umbrella.png");
	Texture background_t;
	background_t.loadFromFile("images/background.png");
	Texture tick_texture;
	tick_texture.loadFromFile("images/tick.png");
	Texture tank_texture;
	tank_texture.loadFromFile("images/tank.png");
	Texture ammo_texture;
	ammo_texture.loadFromFile("images/ammo.png");
	Texture fire_texture;
	fire_texture.loadFromFile("images/fireplace.png");

	//OBJECTS
	Event event;
	Stats stats;
	Player player(umbrella);
	Image image;
	//COLORS
	Color red(237, 28, 36);
	Color yellow(255, 242, 0);
	Color grey(112, 146, 190);
	Color blue(0, 162, 232);
	//CLOCKS
	Clock fireplace_clock;
	Clock shoot_clock;
	//MAP ELEMENTS
	vector<Vector2f>cords_pos;
	vector<CircleShape> corners;
	vector<Walls>rectangles;
	vector<Vector2f> ecord_pos;
	vector<Enemy> soldiers;
	vector<unique_ptr<Bonus>> bonus;
	vector<Fireplace>fire;
	//MAP STATS & TEXTURES
	vector<int> maps_num;
	vector<Texture>textures;
	vector<pair<int, int>>all_data;
	int ile_map = 0;
	//BACKGROUND
	Sprite background;
	background.setTexture(background_t);
	//BOOL VARIABLES
	bool start = false;
	bool menu = true;
	for (int i = 0; i < 7; i++) {
		Texture texture;
		Image image;
		pair<int, int>data;
		if (!image.loadFromFile("images/maps/map" + to_string(i+1) + ".png")) {

		}
		else {
			maps_num.emplace_back(i);
			ile_map++;
		}
		if (!texture.loadFromFile("images/png" + to_string(i+1) + ".png") && image.loadFromFile("images/maps/map" + to_string(i+1) + ".png") == true) {
			texture.loadFromFile("images/default.png");
		}
		textures.emplace_back(texture);
		fstream plik;
		plik.open("game_config/con" + to_string(i+1) + ".txt");
		string dane;
		int akt = 1;
		while (getline(plik, dane)) {

			if (akt == 1) {
				data.first = stoi(dane);
			}
			else if (akt == 2) {
				data.second = stoi(dane);
				break;
			}
			akt++;	
		}
		plik.close();
		all_data.emplace_back(data);
	}
	Start start_m(textures,tick_texture);
	Vector2f cords_set_pos;
	Vector2f current_pos;
	Game game(tank_texture);
	//fireplace animation variables
	IntRect sourceSprite(0, 0, 64, 128);
	int choose_sprite_x = 64;
	int choose_sprite_y = 128;
	//reading map variables
	Art art;
	player.set_circles();
	//main loop
	while (window.isOpen()) {
		//sound.play();
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				break;
			}
		}
		//starting loop
		while (menu == true) {
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
					break;
				}
			}
			start_m.update(window.mapPixelToCoords(Mouse::getPosition(window)));
			for (int i = 0; i < ile_map; i++) {
				if (Mouse::isButtonPressed(Mouse::Left)&&start_m.maps[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
					image.loadFromFile("images/maps/map" + to_string(start_m.update(window.mapPixelToCoords(Mouse::getPosition(window)))) + ".png");
					rectangles = read_walls(image);
					soldiers = read_enemies(image);
					bonus = read_bonus(image, fire_texture, ammo_texture);
					game.setPosition(set_destination(image));
					start = true;
					menu = false;
					stats.game_clock.restart();
					game.win = false;
					player.hp = all_data[i].second;
					player.ammo = all_data[i].first;
					game.lost = false;
					stats.mins = 0;
					art.main.setPosition(set_destination(image).x+43, set_destination(image).y+43);
					art.s_clock.restart();
					player.if_umbrella = false;
					art.hp = 10;
				}
			}
			window.clear();
			window.draw(background);
			window.draw(start_m);
			window.display();
		}
		// game loop
		while (start == true) {
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
					break;
				}
			}
			window.clear();
			window.draw(background);
			//enemy
			for (auto& s : soldiers) {
				s.get_dir_vec(player.main.getPosition());
				s.update();
				s.control(player);
				s.move_();
				window.draw(s);
				game.shoot(player, s);
			}
			//deleting deal enemy
			for (auto s = soldiers.begin(); s != soldiers.end();) {
				if (s->hp <= 0) {
					s = soldiers.erase(s);
				}
				else {
					++s;
				}
			}
			//player functions
			player.update();
			player.get_dir_vec_player(window.mapPixelToCoords(Mouse::getPosition(window)));
			player.m_pos = window.mapPixelToCoords(Mouse::getPosition(window));
			player.control();
			window.draw(player);

			//walls functions
			for (auto& s : rectangles) {
				if (player.main.getGlobalBounds().intersects(s.getGlobalBounds())) {
					s.collision(player);
				}
				s.player_col(player);
				window.draw(s);		
			}
			for (auto& e : soldiers) {
				for (auto& s : rectangles) {
					s.bullet_collision(player, e);
				}
			}
			//bonus funcitons and drawing
			for (auto& s : bonus) {
				if (s->is_ammo == false) {
					if (fireplace_clock.getElapsedTime().asSeconds() > 0.10) {
						Fireplace& some_fireplace = dynamic_cast<Fireplace&>(*s.get());
						sourceSprite.left = choose_sprite_x;
						choose_sprite_x += 64;
						choose_sprite_y += 64;
						for (const auto& g : bonus) {
							if (g->is_ammo == false) {
								g->setTextureRect(sourceSprite);
							}
						}
						if (choose_sprite_x == 512) {
							choose_sprite_y += 64;
							choose_sprite_x = 64;
						}
						if (choose_sprite_y == 512) {
							choose_sprite_y = 64;
							choose_sprite_x = 64;
						}
						some_fireplace.add_hp(player);
						fireplace_clock.restart();
					}
				}

				if (s->is_ammo == false) {
					Fireplace& some_fireplace = dynamic_cast<Fireplace&>(*s.get());
					some_fireplace.add_hp(player);
				}
				else {
					Ammo& some_ammo = dynamic_cast<Ammo&>(*s.get());
					some_ammo.add_ammo(player);
				}
				window.draw(*s);
			}
			//deleting 
			for (auto itr = bonus.begin(); itr != bonus.end();) {
				Bonus& some_bonus = dynamic_cast<Bonus&>(*itr->get());
				if (some_bonus.is_ammo == true && some_bonus.getGlobalBounds().intersects(player.main.getGlobalBounds())) {

					itr = bonus.erase(itr);
				}
				else {
					++itr;
				}
			}
			stats.update(player);
			window.draw(stats);
			if (start_m.mode_art == true) {
				art.get_dir_vec_art(player.main.getPosition(), player);
				window.draw(art);
				game.win_boss(art);
				player.def();
			}
			else {
				window.draw(game);
				game.win_game(player,start_m);
			}
			window.display();
			if (game.win == true) {

				start = false;
				soldiers.clear();
				player.ammo = 50;
				player.hp = 5;
				menu = true;
				rectangles.clear();
				bonus.clear();
				player.velocity.x = 0;
				player.velocity.x = 0;
				player.main.setPosition(50, 650);
				start_m.result.setString("you won");

			}
			if (player.hp <= 0) {

				game.lost = true;
				start = false;
				soldiers.clear();
				player.ammo = 50;
				player.hp = 5;
				menu = true;
				rectangles.clear();
				bonus.clear();
				player.velocity.x = 0;
				player.velocity.x = 0;
				player.main.setPosition(50, 650);
				start_m.result.setString("you lost");
			}
		}
	}
	return 0;
}
