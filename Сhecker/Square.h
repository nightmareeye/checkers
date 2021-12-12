#include <SFML/Graphics.hpp>
using namespace sf; 

class Square {
private:
	bool fon_active = 0;// ��������� 0 ���� ���, 1 ���� ���� = backlight
	bool free = 0;// 0 ��� ���������, 1 ��� ������� = employment
	bool checker_color;// 0 ��� �����, 1 ��� ������ 
	RectangleShape cell = RectangleShape(Vector2f(80, 80));//=square
public:
	Square() { ; }

	RectangleShape &get_cell() { //=get_square
		return this->cell;//=square
	}
	bool get_fon_active() { //=get_backlight
		return this->fon_active; //=backlight
	}
	bool get_free() { //=get_employment
		return this->free;//=employment
	}
	bool get_checker_color() {
		return this->checker_color;
	}
	void off_fon_active() {//=off_backlight
		this->fon_active = 0;//=backlight
	}
	void on_fon_active() { //=on_backlight
		this->fon_active = 1; //=backlight
	}
	void cell_free_0() {//=square_free
		this->free = 0;//=employment
	}
		void cell_free_1(bool color) {//=square_employment
		this->free = 1;//=employment
		this->checker_color = color;
	}
	void set_color(Color color) {
		this->cell.setFillColor(color); //=square
	}
	void set_position(float x, float y) {
		this->cell.setPosition(x, y);//=square
	}
};