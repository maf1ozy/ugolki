#include <SFML/Graphics.hpp>
#include "Conditions.h"
#include "bot.h"
using namespace sf;
using namespace std;



int cell_width = 100;
int cell[8][8];
int cell_imaginary[8][8];
int counter = 0;
int movement = 1;
Conditions cond{};
Bot ai{};
int main()
{
	Texture t;
	t.loadFromFile("desk.png");
	Sprite s(t);
	Texture t1;
	t1.loadFromFile("white.png");
	Sprite s1(t1);
	Texture t2;
	t2.loadFromFile("black.png");
	Sprite s2(t2);
	Texture t3;
	t3.loadFromFile("possibleMove.png");
	Sprite s3(t3);
	Texture ww;
	ww.loadFromFile("ww.jpg");
	Sprite whitewin(ww);
	whitewin.setPosition(200, 200);
	Texture bw;
	bw.loadFromFile("bw.jpg");
	Sprite blackwin(bw);
	blackwin.setPosition(200, 200);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cell[i][j] = 2;
			if ((i == 0) && (j < 3)) cell[i][j] = 1;
			if ((i == 1) && (j < 3)) cell[i][j] = 1;
			if ((i == 2) && (j < 3)) cell[i][j] = 1;
			if ((i == 5) && (j > 4)) cell[i][j] = 0;
			if ((i == 6) && (j > 4)) cell[i][j] = 0;
			if ((i == 7) && (j > 4)) cell[i][j] = 0;
			cell_imaginary[i][j] = counter;
			counter++;
		}
	}
	RenderWindow window(VideoMode(875, 875), "Ugolki");
	while (window.isOpen())
	{
		if (movement == -1) {
			ai.move(cell);
			movement = -1 * movement;
		}
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x / cell_width;
		int y = pos.y / cell_width;
		if ((x > 7)||(y>7)) continue;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)
			if ((event.key.code == Mouse::Left) && (cell[x][y] < 2)) {
					cout << "cell_imaginary: " << cell_imaginary[x][y] << "|cell: " << cell[x][y] << "|x: " << x << "|y: " << y << endl;
					if ((cell[x][y] == 0) && (movement == 1)) cell[x][y] = cond.clickOnFigure(x, y, cell, cell_imaginary);
					//if ((cell[x][y] == 1) && (movement == -1))cell[x][y] = cond.clickOnFigure(x, y, cell, cell_imaginary);
			}
			if ((event.key.code == Mouse::Left) && (cell[x][y] == 3)) {
				cell[x][y] = cond.clickOnSpot(cell, x, y);
				movement = -1 * movement;
			}
			if ((event.key.code == Mouse::Left) && (cell[x][y] == 2)) {
				cell[x][y] = cond.cancelSpots(x, y, cell);
				cout << "cell_imaginary: " << cell_imaginary[x][y] << "|cell: " << cell[x][y] << "|x: " << x << "|y: " << y << endl;
			}
		}
		window.clear(Color(229, 189, 140));
		window.draw(s);

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (cell[i][j] == 0) {
					s1.setPosition(i * cell_width, j * cell_width);
					window.draw(s1);
				}
				if (cell[i][j] == 1) {
					s2.setPosition(i * cell_width, j * cell_width);
					window.draw(s2);
				}
				if (cell[i][j] == 3) {
					s3.setPosition(i * cell_width, j * cell_width);
					window.draw(s3);
				}
			}
		}
		if (cond.whitesWin(cell) == true) window.draw(whitewin);
		if (cond.blacksWin(cell) == true) window.draw(blackwin);

		window.display();
	}

	return 0;
}