#include <SFML/Graphics.hpp>
using namespace sf;

class Checker {
private:
	CircleShape checker = CircleShape(20);
	bool checker_color;// 0 для белых, 1 для черных
	bool choice = 0;//1 если выбрана, 0 если нет =select
	bool superior = 0;//1 если шашка дамка, 0 если нет =queen
	Texture texture;//текстура значка дамки
	Sprite sprite;//спрайт значка дамки
public:
	CircleShape &get_checker() {
		return this->checker;
	}
	Vector2f get_position() {
		return this->checker.getPosition();
	}
	float get_x() {
		return (this->get_position().x - 57) / 50;
	}
	float get_y() {
		return (this->get_position().y - 57) / 50;
	}
	bool get_color() {
		return this->checker_color;
	}
	bool get_select() {
		return this->choice; // =select
	}
	bool get_queen() {
		return this->superior; // =queen
	}
	//fedf
	void make_superior() { // =make_queen
		this->superior = 1; // = queen
	}
	void set_position(float x_position, float y_position) {
		this->checker.setPosition(x_position, y_position);
	}
	void set_color(Color color) {
		this->checker.setFillColor(color);
	}
	void select_checker() {//выбор фигуры
		this->choice= 1; // =select
	}
	void unselect() {//отмена выбора фигуры
		this->choice = 0; //=select
	}

	Checker() { }

	Checker(float x_position, float y_position, bool color) {
		this->checker.setOutlineThickness(3);
		this->checker.setOutlineColor(sf::Color(0, 0, 0));
		this->checker_color = color;
		if (color == 0) {
			this->set_color(Color(180, 120, 55));
		}
		else if (color == 1) {
			this->set_color(Color(61, 25, 7));
		}
		this->set_position(x_position, y_position);
		this->choice = 0; // =select
	}

	void draw_checker(RenderWindow  &window) {
		window.draw(this->checker);
		if (superior == 1) { // =queen
			this->texture.loadFromFile("Images//Queen.png");
			this->sprite.setTexture(texture);
			this->sprite.setTextureRect(IntRect(0, 0, 25, 25));
			this->sprite.setPosition(this->get_position().x + 6, this->get_position().y + 6);
		}
		window.draw(this->sprite);
	}

	Checker operator = (Checker checker) {
		this->texture = checker.texture;
		this->sprite = checker.sprite;
		this->choice = checker.choice; // =select
		this->superior = checker.superior; //=queen
		this->checker_color = checker.checker_color;
		if (checker.checker_color == 0) {
			this->set_color(Color(180, 120, 55));
		}
		else if (checker.checker_color == 1) {
			this->set_color(Color(61, 25, 7));
		}
		this->set_position(checker.get_position().x, checker.get_position().y);
		return (*this);
	}
};