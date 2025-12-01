#pragma once
#include "Character.h"

class Hero2 : public Character {
private:
	int vidas;

public:
	Hero2(int width, int height) : Character(width, height) {
		x = 100;
		y = 300;
		dx = dy = 10;
		vidas = 8;
	}

	~Hero2() {}

	void move(Graphics^ g, char c) {
		switch (c) {
		case 'A':
			if (x > 0) {
				x -= dx;
				idy = 1;
			}
			break;
		case 'D':
			if (x + width * 0.4 < g->VisibleClipBounds.Width) {
				x += dx;
				idy = 2;
			}
			break;
		case 'W':
			if (y > 0) {
				y -= dy;
				idy = 3;
			}
			break;
		case 'S':
			if (y + height * 0.4 < g->VisibleClipBounds.Height) {
				y += dy;
				idy = 0;
			}
			break;
		}
		idx++;
		if (idx > 3) idx = 0;
	}

	int getVidas() { return vidas; }

	void quitarVida() {
		vidas--;
	}

	void setPosition(int newX, int newY) {
		x = newX;
		y = newY;
	}
};