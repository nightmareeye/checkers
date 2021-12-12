#include <SFML/Graphics.hpp>
#include "Checkers_on_board.h"
using namespace sf;

class Game {
private:
	int how_many = 0;
	bool who_can_move = 0;//���� ����, 0 ���� ��� �����, 1 ���� ��� ������
	bool select_is_made = 0;//0 ���� ������ �� �������, 1 ���� �������
	int choise_chacker;//����� ��������� ��� ���� �����
	float x;//����� ������ � ������� ����� �� ��� �
	float y;//����� ������ � ������� ����� �� ��� �
	Vector2i mouse_position;//������� ����
	Checkers_on_board checkers_on_board;
	vector <int> who_must_eat;//����� �����, ������� ����� ������
public:
	Checkers_on_board & get_checkers_on_board() {
		return this->checkers_on_board;
	}
	void mouse_pos(RenderWindow &window) { // Smenil nazvanie funcii
		this->mouse_position = Mouse::getPosition(window);
	}
	Vector2i centre_on_square() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (mouse_position.x < i * 80 + 160 && mouse_position.x < (i + 1) * 80 + 160 &&
					mouse_position.y < j * 80 + 160 && mouse_position.y < (j + 1) * 80 + 160) {
					return Vector2i(i * 80 + 87, j * 80 + 87);
				}
			}
		}
	}

	void choise_of_checker(RenderWindow &window, Event event) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.key.code == Mouse::Left) {
				mouse_pos(window);
				if (event.type == sf::Event::MouseButtonPressed) {//��� ������ ������ ������
					if (event.key.code == Mouse::Left) {
						if (checkers_on_board.get_checker(choise_chacker).check_select() == 1 && select_is_made == 1) { // =get_select
							checkers_on_board.get_checker(choise_chacker).unselect(); // Smenil unselect
							select_is_made = 0;
							std::cout << "Drop" << endl;
							checkers_on_board.delete_backlight();
							return;
						}
					}
				}
				cout << mouse_position.x << endl;
				cout << mouse_position.y << endl;
				for (int i = 0; i < checkers_on_board.get_size(); i++) {
					if (this->mouse_position.x >= checkers_on_board.get_checker(i).check_position().x - 7 && // =get_position
						this->mouse_position.x <= checkers_on_board.get_checker(i).check_position().x + 73 && // =get_position 
						this->mouse_position.y >= checkers_on_board.get_checker(i).check_position().y - 7 && // =get_position
						this->mouse_position.y <= checkers_on_board.get_checker(i).check_position().y + 73) { // =get_position
						if (checkers_on_board.get_checker(i).check_select() == 0 && select_is_made == 0) { // =get_select
							if (checkers_on_board.get_checker(i).get_color() == who_can_move) {
								if (if_you_can_eat_you_must_eat(checkers_on_board.get_checker(i).get_color())) {
									int s = 0;
									for (int f : who_must_eat) {
										if (f == i) {
											s++;
										}
									}
									if (s == 0) {
										error_choise_checker(window, event);
										checkers_on_board.delete_backlight();
										return;
									}
								}
								choise_chacker = i;
								select_is_made = 1;
								checkers_on_board.get_checker(choise_chacker).select_checker();
								std::cout << "Take" << endl;
								x = checkers_on_board.get_checker(choise_chacker).get_x();
								y = checkers_on_board.get_checker(choise_chacker).get_y();
								if (checkers_on_board.get_checker(choise_chacker).check_superior()) { // =get_queen
									queen_square_for_move(checkers_on_board.get_checker(choise_chacker).get_color(), 1, 1, 1, 1);
								}
								else {
									square_for_move();
								}
								return;
							}
						}
					}
				}
			}
		}
	}
	void hod(RenderWindow &window, Event event) {//��� ����� // Smenil nazvanie funciiget_fon_active
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.key.code == Mouse::Right) {
				if (checkers_on_board.get_checker(choise_chacker).check_select() == 1 && select_is_made == 1) { // =get_select
					mouse_pos(window);
					if (checkers_on_board.get_board().get_all_squares((centre_on_square().x - 87) / 80, (centre_on_square().y - 87) / 80).get_fon_active()) {
						checkers_on_board.get_board().get_all_squares(x, y).cell_free_0();
						if (checkers_on_board.get_checker(choise_chacker).check_superior() == 1) { // =get_queen
							checkers_on_board.get_checker(choise_chacker).set_position(centre_on_square().x, centre_on_square().y);
							if (queen_eat_checker()) {
								x = (centre_on_square().x - 87) / 80;
								y = (centre_on_square().y - 87) / 80;
								checkers_on_board.delete_backlight();
								if (queen_square_for_move(checkers_on_board.get_checker(choise_chacker).get_color(), 1, 1, 1, 1)) {
									cout << "loop" << endl;
									return;
								}
							}
						}
						else {
							checkers_on_board.get_checker(choise_chacker).set_position(centre_on_square().x, centre_on_square().y);
							make_queen();
							if (eat_checker()) {
								checkers_on_board.delete_backlight();
								x = (centre_on_square().x - 87) / 80;
								y = (centre_on_square().y - 87) / 80;
								if (!chance_eat_checker(checkers_on_board.get_checker(choise_chacker).get_color())) {
									cout << "loop" << endl;
									return;
								}
							}
						}
						checkers_on_board.get_board().get_all_squares((centre_on_square().x - 87) / 80, (centre_on_square().y - 87) / 80).cell_free_1(checkers_on_board.get_checker(choise_chacker).get_color());
						who_can_move = !who_can_move;
						checkers_on_board.get_checker(choise_chacker).unselect();
						select_is_made = 0;
						std::cout << "Drop" << endl;
						for (int i = 0; i < 8; i++) {
							for (int j = 0; j < 8; j++) {
								cout << checkers_on_board.get_board().get_all_squares(j, i).get_free();
							}
							cout << endl;
						}
						checkers_on_board.delete_backlight();
						return;
					}
				}
			}
		}
	}
	void make_move(RenderWindow &window, Event event) {
		choise_of_checker(window, event);
		hod(window, event);
	}

	void square_for_move() {//�������� ����
		if (checkers_on_board.get_checker(choise_chacker).get_color()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_free() == 0) {
				if (end_board(x + 1, y + 1)) {
					checkers_on_board.get_board().get_all_squares(x + 1, y + 1).on_fon_active();
				}
			}
			if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_free() == 0) {
				if (end_board(x - 1, y + 1)) {
					checkers_on_board.get_board().get_all_squares(x - 1, y + 1).on_fon_active();
				}
			}
		}
		else {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_free() == 0) {
				if (end_board(x + 1, y - 1)) {
					checkers_on_board.get_board().get_all_squares(x + 1, y - 1).on_fon_active();
				}
			}
			if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_free() == 0) {
				if (end_board(x - 1, y - 1)) {
					checkers_on_board.get_board().get_all_squares(x - 1, y - 1).on_fon_active();
				}
			}
		}
		if (!chance_eat_checker(checkers_on_board.get_checker(choise_chacker).get_color())) {//�������� ������ �����
			checkers_on_board.delete_backlight();
			chance_eat_checker(checkers_on_board.get_checker(choise_chacker).get_color());
		}
	}
	bool chance_eat_checker(bool color) {//�������� ������ �����
		bool more = 1;
		if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_free()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y + 1).get_checker_color() != color) {
				if (checkers_on_board.get_board().get_all_squares(x + 2, y + 2).get_free() == 0) {
					if (end_board(x + 2, y + 2)) {
						checkers_on_board.get_board().get_all_squares(x + 2, y + 2).on_fon_active();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_free()) {
			if (checkers_on_board.get_board().get_all_squares(x - 1, y + 1).get_checker_color() != color) {
				if (checkers_on_board.get_board().get_all_squares(x - 2, y + 2).get_free() == 0) {
					if (end_board(x - 2, y + 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y + 2).on_fon_active();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_free()) {
			if (checkers_on_board.get_board().get_all_squares(x + 1, y - 1).get_checker_color() != color) {
				if (checkers_on_board.get_board().get_all_squares(x + 2, y - 2).get_free() == 0) {
					if (end_board(x + 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x + 2, y - 2).on_fon_active();
						more = 0;
					}
				}
			}
		}
		if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_free()) {
			if (checkers_on_board.get_board().get_all_squares(x - 1, y - 1).get_checker_color() != color) {
				if (checkers_on_board.get_board().get_all_squares(x - 2, y - 2).get_free() == 0) {
					if (end_board(x - 2, y - 2)) {
						checkers_on_board.get_board().get_all_squares(x - 2, y - 2).on_fon_active();
						more = 0;
					}
				}
			}
		}
		return more;
	}
	bool eat_checker() {//�� �����
		if ((centre_on_square().x - 87) / 80 - x == 2 || (centre_on_square().x - 87) / 80 - x == -2 &&
			(centre_on_square().y - 87) / 80 - y == 2 || (centre_on_square().y - 87) / 80 - y == -2) {
			for (int i = 0; i < checkers_on_board.get_size(); i++) {
				if (checkers_on_board.get_checker(i).get_x() == x + (checkers_on_board.get_checker(choise_chacker).get_x() - x) / 2 &&
					checkers_on_board.get_checker(i).get_y() == y + (checkers_on_board.get_checker(choise_chacker).get_y() - y) / 2) {
					checkers_on_board.get_board().get_all_squares(checkers_on_board.get_checker(i).get_x(), checkers_on_board.get_checker(i).get_y()).cell_free_0();
					for (int j = i; j < checkers_on_board.get_size() - 1; j++) {
						checkers_on_board.get_checker(j) = checkers_on_board.get_checker(j + 1);
					}
					checkers_on_board.delete_checker();
					if (i < choise_chacker) {
						choise_chacker = choise_chacker - 1;
					}
					return 1;
				}
			}
		}
		return 0;
	}

	void make_queen() {
		if (checkers_on_board.get_checker(choise_chacker).get_color() == 0) {
			if (checkers_on_board.get_checker(choise_chacker).get_y() == 0) {
				checkers_on_board.get_checker(choise_chacker).make_superior();
			}
		}
		if (checkers_on_board.get_checker(choise_chacker).get_color() == 1) {
			if (checkers_on_board.get_checker(choise_chacker).get_y() == 7) {
				checkers_on_board.get_checker(choise_chacker).make_superior();
			}
		}
	}
	bool queen_square_for_move(bool color, int i1, int i2, int i3, int i4) {//�������� ���� �����
		int must_eat = 0;
		bool can_eat[4] = { i1, i2, i3, i4 };
		checkers_on_board.delete_backlight();
		int x_queen = x;
		int y_queen = y;
		if (can_eat[0]) {
			can_eat[0] = 0;
			while (1) {
				if (end_board(x_queen + 1, y_queen + 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_free() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() == color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).get_checker_color() != color) {
							if (end_board(x_queen + 2, y_queen + 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen + 2).get_free() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen + 2).on_fon_active();
									x_queen = x_queen + 2;
									y_queen = y_queen + 2;
									must_eat++;
									can_eat[0] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen + 1).on_fon_active();
						x_queen = x_queen + 1;
						y_queen = y_queen + 1;
					}
				}
				else break;
			}
		}
		if (can_eat[1]) {
			can_eat[1] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen - 1, y_queen + 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_free() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() == color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).get_checker_color() != color) {
							if (end_board(x_queen - 2, y_queen + 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen + 2).get_free() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen + 2).on_fon_active();
									x_queen = x_queen - 2;
									y_queen = y_queen + 2;
									must_eat++;
									can_eat[1] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen + 1).on_fon_active();
						x_queen = x_queen - 1;
						y_queen = y_queen + 1;
					}
				}
				else break;
			}
		}
		if (can_eat[2]) {
			can_eat[2] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen + 1, y_queen - 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_free() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() == color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).get_checker_color() != color) {
							if (end_board(x_queen + 2, y_queen - 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen - 2).get_free() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen + 2, y_queen - 2).on_fon_active();
									x_queen = x_queen + 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[2] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen + 1, y_queen - 1).on_fon_active();
						x_queen = x_queen + 1;
						y_queen = y_queen - 1;
					}
				}
				else break;
			}
		}
		if (can_eat[3]) {
			can_eat[3] = 0;
			x_queen = x;
			y_queen = y;
			while (1) {
				if (end_board(x_queen - 1, y_queen - 1)) {
					if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_free() == 1) {
						if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() == color) {
							break;
						}
						else if (checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).get_checker_color() != color) {
							if (end_board(x_queen - 2, y_queen - 2)) {
								if (checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen - 2).get_free() == 0) {
									checkers_on_board.get_board().get_all_squares(x_queen - 2, y_queen - 2).on_fon_active();
									x_queen = x_queen - 2;
									y_queen = y_queen - 2;
									must_eat++;
									can_eat[3] = 1;
								}
								else break;
							}
							else break;
						}
					}
					else {
						checkers_on_board.get_board().get_all_squares(x_queen - 1, y_queen - 1).on_fon_active();
						x_queen = x_queen - 1;
						y_queen = y_queen - 1;
					}
				}
				else break;
			}
		}
		if (must_eat == 0) {
			return 0;
		}
		else {
			if (i1 == 1 && i2 == 1 && i3 == 1 && i4 == 1) {
				queen_square_for_move(color, can_eat[0], can_eat[1], can_eat[2], can_eat[3]);
			}
			else return 1;
		}
	}
	bool queen_eat_checker() {//�� �����
		int x_eat = 0;
		int y_eat = 0;
		if ((centre_on_square().x - 87) / 80 - x >= 2 && (centre_on_square().y - 87) / 80 - y >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 87) / 80 - 1 && j < (centre_on_square().y - 87) / 80 - 1) {
					if (checkers_on_board.get_board().get_all_squares(i + 1, j + 1).get_free() == 1) {
						x_eat = i + 1;
						y_eat = j + 1;
						break;
					}
					else {
						i++;
						j++;
					}
				}
				else break;
			}
		}
		if ((centre_on_square().x - 87) / 80 - x >= 2 && y - (centre_on_square().y - 87) / 80 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i < (centre_on_square().x - 87) / 80 - 1 && j >(centre_on_square().y - 87) / 80 + 1) {
					if (checkers_on_board.get_board().get_all_squares(i + 1, j - 1).get_free() == 1) {
						x_eat = i + 1;
						y_eat = j - 1;
						break;
					}
					else {
						i++;
						j--;
					}
				}
				else break;
			}
		}
		if (x - (centre_on_square().x - 87) / 80 >= 2 && (centre_on_square().y - 87) - y / 80 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 87) / 80 + 1 && j < (centre_on_square().y - 87) / 80 - 1) {
					if (checkers_on_board.get_board().get_all_squares(i - 1, j + 1).get_free() == 1) {
						x_eat = i - 1;
						y_eat = j + 1;
						break;
					}
					else {
						i--;
						j++;
					}
				}
				else break;
			}
		}
		if (x - (centre_on_square().x - 87) / 80 >= 2 && y - (centre_on_square().y - 87) / 80 >= 2) {
			int i = x;
			int j = y;
			while (1) {
				if (i > (centre_on_square().x - 87) / 80 + 1 && j > (centre_on_square().y - 87) / 80 + 1) {
					if (checkers_on_board.get_board().get_all_squares(i - 1, j - 1).get_free() == 1) {
						x_eat = i - 1;
						y_eat = j - 1;
						break;
					}
					else {
						i--;
						j--;
					}
				}
				else break;
			}
		}

		for (int f = 0; f < checkers_on_board.get_size(); f++) {
			if (checkers_on_board.get_checker(f).get_x() == x_eat && checkers_on_board.get_checker(f).get_y() == y_eat) {
				checkers_on_board.get_board().get_all_squares(checkers_on_board.get_checker(f).get_x(), checkers_on_board.get_checker(f).get_y()).cell_free_0();

				for (int c = f; c < checkers_on_board.get_size() - 1; c++) {
					checkers_on_board.get_checker(c) = checkers_on_board.get_checker(c + 1);
				}
				checkers_on_board.delete_checker();
				if (f < choise_chacker) {
					choise_chacker = choise_chacker - 1;
				}
				return 1;
			}
		}
		return 0;
	}

	bool end_board(float x, float y) {//�������� ������ �� ������� ����
		if (x >= 0 && x < 8 && y >= 0 && y < 8) {
			return 1;
		}
		return 0;
	}

	bool if_you_can_eat_you_must_eat(bool color) {
		while (who_must_eat.size() != 0) {
			who_must_eat.pop_back();
		}
		for (int i = 0; i < checkers_on_board.get_size(); i++) {
			if (checkers_on_board.get_checker(i).get_color() == color) {
				if (checkers_on_board.get_checker(i).check_superior() == 0) {  // =get_queen
					x = checkers_on_board.get_checker(i).get_x();
					y = checkers_on_board.get_checker(i).get_y();
					if (!chance_eat_checker(color)) {
						who_must_eat.push_back(i);
					}
				}
				if (checkers_on_board.get_checker(i).check_superior() == 1) { // =get_queen
					x = checkers_on_board.get_checker(i).get_x();
					y = checkers_on_board.get_checker(i).get_y();
					if (queen_square_for_move(color, 1, 1, 1, 1)) {
						who_must_eat.push_back(i);
					}
				}
			}
		}
		checkers_on_board.delete_backlight();
		if (who_must_eat.size() != 0) return 1;
		else return 0;
	}
	void error_choise_checker(RenderWindow &window, Event event) {
		while (1) {
			RectangleShape back = RectangleShape(Vector2f(170, 110));
			back.setFillColor(Color(245, 210, 175));
			back.setPosition(165, 225);
			Font font;
			font.loadFromFile("Font//bahnschrift.ttf");
			Text t = Text("", font, 25);
			t.setString(L"Eat necessary");
			t.setFillColor(Color::Black);
			t.setPosition(172, 235);
			Text out = Text("", font, 11);
			out.setString(L"press any key to continue");
			out.setFillColor(Color::Black);
			out.setPosition(173, 260);
			window.draw(back);
			window.draw(t);
			window.draw(out);
			window.display();
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
					return;
				}
			}
		}
	}

	void start_game(RenderWindow &window, Event event, bool &start) {
		Font font;
		font.loadFromFile("Font//bahnschrift.ttf");
		Text t[5];
		t[0] = Text("", font, 100);
		t[0].setPosition(82, 150);
		t[0].setStyle(Text::Bold);
		t[0].setString(L"�����");
		t[1] = Text("", font, 25);
		t[1].setPosition(82,  260);
		t[1].setString(L"����� ������ - ����� �����");
		t[2] = Text("", font, 25);
		t[2].setPosition(82, 260 + 25);
		t[2].setString(L"������ ������ - ������� ���");
		t[3] = Text("", font, 14);
		t[3].setFillColor(Color::Black);
		t[3].setPosition(225, 484);
		t[3].setString(L"������� ����� ������� ����� ����������");
		for (int i = 0; i < 5; i++) {
			t[i].setFillColor(Color::Black);
		}
		while (1) {	
			window.clear(Color(245, 210, 175));
			for (int i = 0; i < 5; i++) {
				window.draw(t[i]);
			}
			window.display();
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
					start = 0;
					return;
				}
			}
		}
	}

	bool end_game(RenderWindow &window, Event event) {
		int black = 0;
		int white = 0;
		for (int i = 0; i < checkers_on_board.get_size(); i++) {
			if (checkers_on_board.get_checker(i).get_color() == 0) {
				white++;
			}
			if (checkers_on_board.get_checker(i).get_color() == 1) {
				black++;
			}
		}
		if (white == 0) {
				RectangleShape back = RectangleShape(Vector2f(350, 150));
				back.setFillColor(Color(245, 210, 175));
				back.setPosition(75, 175);
				Font font;
				font.loadFromFile("Font//bahnschrift.ttf");
				Text t = Text("", font, 81);
				t.setString(L"Black win");
				t.setFillColor(Color::Black);
				t.setPosition(78, 190);
				window.draw(back);
				window.draw(t);
				if (event.type == Event::Closed)
					window.close();
				return 0;		
		}
		if (black == 0) {
			RectangleShape back = RectangleShape(Vector2f(350, 150));
			back.setFillColor(Color(245, 210, 175));
			back.setPosition(75, 175);
			Font font;
			font.loadFromFile("Font//bahnschrift.ttf");
			Text t = Text("", font, 81);
			t.setString(L"White win");
			t.setFillColor(Color::Black);
			t.setPosition(75, 190);
			window.draw(back);
			window.draw(t);
			if (event.type == Event::Closed)
				window.close();
			return 0;			
		}
		return 1;
	}
}; 