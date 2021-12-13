#include <SFML/Graphics.hpp>
using namespace sf;

class Checker {
public:
	CircleShape &get_checker() {
		return this->checker;
	}
	Vector2f check_position() { // передает позицию
		return this->checker.getPosition();
	}
	float get_x() {
		return (this->check_position().x - 87) / 80;
	}
	float get_y() {
		return (this->check_position().y - 87) / 80;
	}
	bool get_color() {
		return this->checker_color;
	}
	bool check_select() {
		return this->choice;
	}
	bool check_superior() {
		return this->superior;
	}
	
	void make_superior() {
		this->superior = 1;
	}
	void set_position(float x_position, float y_position) {
		this->checker.setPosition(x_position, y_position);
	}
	void set_color(Color color) {
		this->checker.setFillColor(color);
	}
	void select_checker() {//выбор фигуры
		this->choice= 1;
	}
	void unselect() {//отмена выбора фигуры
		this->choice = 0; 
	}

	Checker() { }

	Checker(float x_position, float y_position, bool color) {
		this->checker.setOutlineThickness(3);
		this->checker.setOutlineColor(Color(0, 0, 0));
		this->checker_color = color;
		if (color == 0) {
			this->set_color(Color(159, 133, 103));
		}
		else if (color == 1) {
			this->set_color(Color(37, 25, 13));
		}
		this->set_position(x_position, y_position);
		this->choice = 0;
	}

	void draw_checker(RenderWindow  &window) {
		window.draw(this->checker);
		if (superior == 1) {
			this->checker_texture.loadFromFile("Images//Queen.png");
			this->sprite.setTexture(checker_texture);
			this->sprite.setTextureRect(IntRect(0, 0, 25, 25));
			this->sprite.setPosition(this->check_position().x + 6, this->check_position().y + 6);
		}
		window.draw(this->sprite);
	}

	Checker operator = (Checker checker) {
		this->checker_texture = checker.checker_texture;
		this->sprite = checker.sprite;
		this->choice = checker.choice;
		this->superior = checker.superior;
		this->checker_color = checker.checker_color;
		if (checker.checker_color == 0) {
			this->set_color(Color(159, 133, 103));
		}
		else if (checker.checker_color == 1) {
			this->set_color(Color(37, 25, 13));
		}
		this->set_position(checker.check_position().x, checker.check_position().y);
		return (*this);
	}
private:
	CircleShape checker = CircleShape(35);
	bool checker_color;// 0 = белые, 1 = черные
	bool choice = 0;//1 если выбрана, 0 если нет
	bool superior = 0;//1 если шашка дамка, 0 если нет
	Texture checker_texture;//текстура значка дамки
	Sprite sprite;//спрайт значка дамки
};