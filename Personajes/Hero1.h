#pragma once
#include "Character.h"

class Hero1 : public Character {
private:
	int vidas;

public:
	Hero1(int width, int height) : Character(width, height) {
		x = 460;
		y = 320;
		dx = dy = 10;
		vidas = 5;
	}

	~Hero1() {}

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