#include <SFML/Graphics.hpp>
#include "Square.h"
#include <iostream>
using namespace sf; // класс
using namespace std; //библиотека

class Board {
private:
	Square all_squares[8][8];
public:
	Board(){}
	Square &get_all_squares(int i, int j) {
		return this->all_squares[i][j];
	}

	void draw_board(RenderWindow &window) {
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				all_squares[i - 1][j - 1].set_position(i * 80.0, j * 80);
				if ((i + j) % 2 == 1) all_squares[i - 1][j - 1].set_color(Color(115, 95, 74));
				else all_squares[i - 1][j - 1].set_color(Color(51, 37, 22));
				window.draw(all_squares[i - 1][j - 1].get_fon_active());
			}

		}
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (all_squares[i - 1][j - 1].get_fon_active() == 1) {
					RectangleShape square_light(Vector2f(50, 50));
					square_light.setPosition(i * 50, j * 50);
					all_squares[i - 1][j - 1].set_color(Color(150, 120, 90));
				}
				window.draw(all_squares[i - 1][j - 1].get_cell());
			}
		}
		/*Font font;
		font.loadFromFile("Font//bahnschrift.ttf");
		Text *t[16];
		for (int i = 0; i < 16; i++) {
			t[i] = new Text("", font, 35);

		}
		t[0]->setString(L"1");
		t[1]->setString(L"2");
		t[2]->setString(L"3");
		t[3]->setString(L"4");
		t[4]->setString(L"5");
		t[5]->setString(L"6");
		t[6]->setString(L"7");
		t[7]->setString(L"8");
		t[8]->setString(L"А");
		t[9]->setString(L"B");
		t[10]->setString(L"C");
		t[11]->setString(L"D");
		t[12]->setString(L"E");
		t[13]->setString(L"F");
		t[14]->setString(L"G");
		t[15]->setString(L"H");
		for (int i = 0; i < 8; i++) {
			t[i]->setFillColor(Color::Black);
			t[i]->setPosition(15, i * 50 + 55);
			window.draw(*t[i]);
			t[i]->setPosition(465, i * 50 + 55);
			window.draw(*t[i]);
		}
		for (int i = 8; i < 16; i++) {
			t[i]->setFillColor(Color::Black);
			t[i]->setPosition((i - 8) * 50 + 60, 5);
			window.draw(*t[i]);
			t[i]->setPosition((i - 8) * 50 + 60, 455);
			window.draw(*t[i]);
		}*/
	}
};