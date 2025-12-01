#pragma once
#include <iostream>
#include "Character.h"

class Enemy1 : public Character {
private:
	int type;

public:
	Enemy1(int width, int h) : Character(width, h) {
		x = 0; y = 0; // Se sobrescribirá desde el Controller
		dx = dy = rand() % 4 + 3;
		type = rand() % 2;
	}

	~Enemy1() {}

	void move(Graphics^ g) override { // 'override' es buena práctica
		int objWidth = (int)(width * 0.4);
		int objHeight = (int)(height * 0.4);

		switch (type) {
		case 0: // Movimiento Horizontal
			// Rebote usando los límites de la ZONA
			if (x + objWidth > maxX || x < minX) dx *= -1;

			if (dx > 0) idy = 1; else idy = 3;
			x += dx;
			break;

		case 1: // Movimiento Vertical
			if (y + objHeight > maxY || y < minY) dy *= -1;

			if (dy > 0) idy = 0; else idy = 2;
			y += dy;
			break;
		}

		idx++;
		if (idx > 3) idx = 0;
	}

	int getType() { return type; }
};