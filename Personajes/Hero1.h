#pragma once
#include "Character.h"

class Hero1 : public Character {
private:

	int vidas;
public:
	Hero1(int width, int height) : Character(width, height) {
		x = 0;
		y = 50;
		dx = dy = 15;  // ⬅️ MÁS RÁPIDO (era 10)
		vidas = 5;     // ⬅️ FIJO, 5 vidas (era random)
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

			if (x + width * 1.0 < g->VisibleClipBounds.Width) {
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

			if (y + height * 1.0 < g->VisibleClipBounds.Height) {
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
};