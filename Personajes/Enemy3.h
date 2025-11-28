#pragma once
#include<iostream>
#include "Character.h"
class Enemy3 : public Character {
private:
	int type;

public:
	Enemy3(int width, int h) : Character(width, h) {
		x = rand() % 60 * 10;
		y = rand() % 30 * 10;

		dx = dy = rand() % 4 + 3;

		type = rand() % 2;

	}

	~Enemy3() {}

	void move(Graphics^ g) {

		switch (type) {
		case 0:
			if (x + width * 1.0 > g->VisibleClipBounds.Width || x < 0) dx *= -1;
			if (dx > 0) {
				idy = 1;
			}
			else {
				idy = 3;
			}
			x += dx;
			break;

		case 1:
			if (y + height * 1.0 > g->VisibleClipBounds.Height || y < 0) dy *= -1;
			if (dy > 0) {
				idy = 0;
			}
			else {
				idy = 2;
			}
			y += dy;
			break;
		}

		idx++;
		if (idx > 3) idx = 0;

	}


	int getType() {
		return type;
	}
};