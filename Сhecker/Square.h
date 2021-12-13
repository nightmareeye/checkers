#include <SFML/Graphics.hpp>
using namespace sf; 

class Square {
public:
	Square() { ; }

	RectangleShape &get_cell() { 
		return this->cell;
	}
	bool get_fon_active() { 
		return this->fon_active; 
	}
	bool get_free() { 
		return this->free;
	}
	bool get_checker_color() {
		return this->checker_color;
	}
	void off_fon_active() {
		this->fon_active = 0;
	}
	void on_fon_active() { 
		this->fon_active = 1; 
	}
	void cell_free_0() {
		this->free = 0;
	}
		void cell_free_1(bool color) {
		this->free = 1;
		this->checker_color = color;
	}
	void set_color(Color color) {
		this->cell.setFillColor(color); 
	}
	void set_position(float x, float y) {
		this->cell.setPosition(x, y);
	}
private:
	bool fon_active = 0;// 1 подцветки есть, 0 = нет подцветки  
	bool free = 0;// 1 = заняте клетки, 0 = свободные клетки
	bool checker_color;// 1 = черные шашки, 0 = белые шашки
	RectangleShape cell = RectangleShape(Vector2f(80, 80));
};