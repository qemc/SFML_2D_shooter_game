#include "Soldiers.h"
#include "Bullets.h"


const float PI = 3.14159265359f;


Vector2f Soldiers::norm(const Vector2f& x, const Vector2f& y) {

	Vector2f all(abs(x.x - y.x), abs(x.y - y.y));
	float sqr = sqrt(((y.x - x.x) * (y.x - x.x)) + (y.y - x.y) * (y.y - x.y));
	return Vector2f(all.x / sqr, all.y / sqr);
}
float Soldiers::angle(Vector2f dirVec) {

	float magSquare = sqrt((dirVec.x * dirVec.x) + (dirVec.y * dirVec.y));
	dirVec.x = (dirVec.x) / magSquare;
	dirVec.y = (dirVec.y) / magSquare;
	return acos(dirVec.x) * (180 / PI);

}
void Soldiers::get_dir_vec(const Vector2f& mousepos) {

	 Vector2f dirVec_(mousepos.x - main.getPosition().x, mousepos.y - main.getPosition().y);
	 dirVec = dirVec_;
	 if (Mouse::isButtonPressed(Mouse::Left)) {
		 Vector2f mousepos_(mouse_pos);
		 mouse_pos = mousepos_;
	 }		
	 Vector2f currnentpos_ = main.getPosition();
	 current_pos = currnentpos_;
}

void Soldiers::set_circles() {
	main.setFillColor(Color::Transparent);
	main.setRadius(10);
	main.setOutlineThickness(2);
	main.setOutlineColor(Color::White);
	main.setOrigin(10, 10);
	aim.setFillColor(Color::Green);
	aim.setRadius(4);
	aim.setOrigin(2, 20);
}
void Soldiers::update() {
	set_circles();
	if (dirVec.y < 0) {
		aim.setRotation(90 - angle(dirVec));
	}
	else {
		aim.setRotation(90 + angle(dirVec));
	}
}
void Soldiers::draw(RenderTarget& target, RenderStates state) const {
	target.draw(main, state);
	target.draw(aim,state);
}

