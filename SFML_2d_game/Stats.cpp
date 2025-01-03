#include "Stats.h"


Stats::Stats() {
	font.loadFromFile("font/huston.otf");
	setFont(font);
	setPosition(10, 750);
	setCharacterSize(20);
}

void Stats::update(const Player& player) {
	int sec_pom = round(game_clock.getElapsedTime().asSeconds());
	string sec = to_string(sec_pom);
	if (sec == "60") {
		mins++;
		game_clock.restart();
	}
	if (sec_pom < 10) {
		sec = "0" + sec;
	}
	setString("healthpoints: " + to_string(player.hp) + "  " + 
			"bullets left: " + to_string(player.ammo) + "  " + 
			"time: " + to_string(mins)+":"+sec);
}



