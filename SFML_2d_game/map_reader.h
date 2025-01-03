#pragma once
#include "Soldiers.h"
#include "Walls.h"
#include "Enemy.h"
#include"Fireplace.h"
#include "Ammo.h"
#include "Game.h"

//MAP READING FUNCTIONS

vector<Walls>read_walls(const Image& image) {

	
	vector<Vector2f>cords_pos;
	vector<Walls>rectangles;

	for (uint16_t j = 1; j < 700; j++) {
		for (uint16_t i = 1; i < 700; i++) {

			if (image.getPixel(i, j) == Color::Black && (image.getPixel(i, j - 1) != Color::Black || j - 1 == 0) && (image.getPixel(i - 1, j) != Color::Black || i - 1 == 0)) {

				cords_pos.emplace_back(Vector2f(i, j));

			}
		}
	}
	for (uint16_t j = 0; j < 699; j++) {
		for (uint16_t i = 0; i < 699; i++) {

			if (image.getPixel(i, j) == Color::Black && (image.getPixel(i, j + 1) != Color::Black || j + 1 == 699) && (image.getPixel(i + 1, j) != Color::Black || i + 1 == 699)) {

				cords_pos.emplace_back(Vector2f(i, j));

			}
		}
	}
	for (uint16_t j = 1; j < 700; j++) {
		for (uint16_t i = 0; i < 699; i++) {

			if (image.getPixel(i, j) == Color::Black && (image.getPixel(i, j - 1) != Color::Black || j - 1 == 0) && (image.getPixel(i + 1, j) != Color::Black || i + 1 == 699)) {

				cords_pos.emplace_back(Vector2f(i, j));

			}
		}
	}
	for (uint16_t j = 0; j < 699; j++) {
		for (uint16_t i = 1; i < 700; i++) {

			if (image.getPixel(i, j) == Color::Black && (image.getPixel(i, j + 1) != Color::Black || j + 1 == 699) && (image.getPixel(i - 1, j) != Color::Black || i - 1 == 0)) {

				cords_pos.emplace_back(Vector2f(i, j));

			}
		}
	}
	for (uint16_t j = 1; j < 699; j++) {
		for (uint16_t i = 1; i < 699; i++) {

			if (image.getPixel(i, j) == Color::Black && image.getPixel(i + 1, j - 1) != Color::Black && image.getPixel(i, j - 1) == Color::Black && image.getPixel(i + 1, j) == Color::Black) {

				cords_pos.emplace_back(Vector2f(i, j));

			}
		}
	}
	for (uint16_t j = 1; j < 699; j++) {
		for (uint16_t i = 1; i < 699; i++) {

			if (image.getPixel(i, j) == Color::Black && image.getPixel(i - 1, j - 1) != Color::Black && image.getPixel(i, j - 1) == Color::Black && image.getPixel(i - 1, j) == Color::Black) {

				cords_pos.emplace_back(Vector2f(i, j));

			}
		}
	}
	for (uint16_t j = 1; j < 699; j++) {
		for (uint16_t i = 1; i < 699; i++) {

			if (image.getPixel(i, j) == Color::Black && image.getPixel(i + 1, j + 1) != Color::Black && image.getPixel(i, j + 1) == Color::Black && image.getPixel(i + 1, j) == Color::Black) {

				cords_pos.emplace_back(Vector2f(i, j));
			}
		}
	}
	for (uint16_t j = 1; j < 699; j++) {
		for (uint16_t i = 1; i < 699; i++) {

			if (image.getPixel(i, j) == Color::Black && image.getPixel(i - 1, j + 1) != Color::Black && image.getPixel(i, j + 1) == Color::Black && image.getPixel(i - 1, j) == Color::Black) {

				cords_pos.emplace_back(Vector2f(i, j));
			}
		}
	}
	for (int i = 0; i < cords_pos.size(); i++) {

		for (int j = 0; j < cords_pos.size(); j++) {

			if (cords_pos[i].y == cords_pos[j].y && i != j) {

				for (int x = 0; x < cords_pos.size(); x++) {

					if (cords_pos[j].x == cords_pos[x].x && j != x) {

						for (int o = 0; o < cords_pos.size(); o++) {

							if (cords_pos[x].y == cords_pos[o].y && cords_pos[i].x == cords_pos[o].x && o != x) {

								rectangles.emplace_back(Walls(Vector2f(cords_pos[i]), Vector2f(cords_pos[j].x - cords_pos[i].x, cords_pos[o].y - cords_pos[i].y)));
								break;

							}
						}
					}
				}
			}
		}
	}
	return rectangles;
}

vector<Enemy> read_enemies(const Image& image) {
	vector<Vector2f> ecord_pos;
	vector<Enemy> soldiers;
	Color red(255, 0, 0);
	for (uint16_t j = 1; j < 700; j++) {
		for (uint16_t i = 1; i < 700; i++) {
			if (image.getPixel(i, j) == red && (image.getPixel(i, j - 1) != red || j - 1 == 0) && (image.getPixel(i - 1, j) != red || i - 1 == 0)) {
				ecord_pos.emplace_back(Vector2f(i, j));
				int i_ = i;
				int j_ = j;
				while (image.getPixel(i_, j) == red && image.getPixel(i_, j - 1) != red) {
					i_++;
				}
				while (image.getPixel(i, j_) == red && image.getPixel(i - 1, j_) != red) {
					j_++;
				}
				if (i_ - i > j_ - j) {
					soldiers.emplace_back(Vector2f(i, i_), Vector2f(i_, j - (j - j_) / 2), false, Vector2f((i_ - i), (j_ - j)), Vector2f(i, j));
				}
				else {
					soldiers.emplace_back(Vector2f(j, j_), Vector2f(i - (i - i_) / 2, j), true, Vector2f((i_ - i), (j_ - j)), Vector2f(i, j));
				}
			}
		}
	}
	return soldiers;
}



vector<unique_ptr<Bonus>> read_bonus(const Image& image, const Texture& fire_texture, const Texture& ammo_texture) {

	vector<Vector2f> ecord_pos;
	vector<unique_ptr<Bonus>> bonus;
	Color yellow(255, 255, 0);
	Color green(0, 255, 0);
	IntRect sourceSprite(0, 0, 64, 128);
	for (uint16_t j = 1; j < 700; j++) {
		for (uint16_t i = 1; i < 700; i++) {
			if (image.getPixel(i, j) == yellow && (image.getPixel(i, j - 1) != yellow || j - 1 == 0) && (image.getPixel(i - 1, j) != yellow || i - 1 == 0)) {
				ecord_pos.emplace_back(Vector2f(i, j));
				int i_ = i;
				int j_ = j;
				while (image.getPixel(i_, j) == yellow && image.getPixel(i_, j - 1) != yellow) {
					i_++;
				}
				while (image.getPixel(i, j_) == yellow && image.getPixel(i - 1, j_) != yellow) {
					j_++;
				}
				bonus.emplace_back(make_unique<Fireplace>(Fireplace(fire_texture, Vector2f(i_ - 32, j_ - 50), sourceSprite)));
			}
		}
	}
	//bonus - ammo
	for (uint16_t j = 1; j < 700; j++) {
		for (uint16_t i = 1; i < 700; i++) {
			if (image.getPixel(i, j) == green && (image.getPixel(i, j - 1) != green || j - 1 == 0) && (image.getPixel(i - 1, j) != green || i - 1 == 0)) {
				ecord_pos.emplace_back(Vector2f(i, j));
				int i_ = i;
				int j_ = j;
				while (image.getPixel(i_, j) == green && image.getPixel(i_, j - 1) != green) {
					i_++;
				}
				while (image.getPixel(i, j_) == green && image.getPixel(i - 1, j_) != green) {
					j_++;
				}
				bonus.emplace_back(make_unique<Ammo>(Ammo(ammo_texture, Vector2f(i_ - 30, j_ - 32))));
			}
		}
	}

	return bonus;
}


Vector2f set_destination(const Image& image) {

	vector<Vector2f> ecord_pos;
	Vector2f position;
	Color blue(0, 0, 255);

	for (uint16_t j = 1; j < 700; j++) {

		for (uint16_t i = 1; i < 700; i++) {

			if (image.getPixel(i, j) == blue && (image.getPixel(i, j - 1) != blue || j - 1 == 0) && (image.getPixel(i - 1, j) != blue || i - 1 == 0)) {

				ecord_pos.emplace_back(Vector2f(i, j));
				int i_ = i;
				int j_ = j;
				while (image.getPixel(i_, j) == blue && image.getPixel(i_, j - 1) != blue) {
					i_++;
				}
				while (image.getPixel(i, j_) == blue && image.getPixel(i - 1, j_) != blue) {
					j_++;
				}
				position.x = i_ - 64;
				position.y = j_ - 64;
			}
		}
	}


	return position;
}