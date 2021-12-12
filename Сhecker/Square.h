#include <SFML/Graphics.hpp>
using namespace sf; 

class Square {
private:
	bool fon_active = 0;// подцветка 0 если нет, 1 если есть = backlight
	bool free = 0;// 0 для свободных, 1 для занятых = employment
	bool checker_color;// 0 для белых, 1 для черных 
	RectangleShape cell = RectangleShape(Vector2f(80, 80));//=square
public:
	Square() { ; }

	RectangleShape &get_square() {
		return this->cell;//=square
	}
	bool get_backlight() {
		return this->fon_active; //=backlight
	}
	bool get_employment() {
		return this->free;//=employment
	}
	bool get_checker_color() {
		return this->checker_color;
	}

	void on_backlight() {
		this->fon_active = 1; //=backlight
	}
	void off_backlight() {
		this->fon_active = 0;//=backlight
	}
	void square_employment(bool color) {
		this->free = 1;//=employment
		this->checker_color = color;
	}
	void square_free() {
		this->free = 0;//=employment
	}
	void set_color(Color color) {
		this->cell.setFillColor(color); //=square
	}
	void set_position(float x, float y) {
		this->cell.setPosition(x, y);//=square
	}
};