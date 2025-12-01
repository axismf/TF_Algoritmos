#pragma once

using namespace System::Drawing;

class Character {
protected:
	int x, y;
	int dx, dy;
	int width, height;
	int idx, idy;
	double zoom = 1.0;


public:
	Character(int width, int height) :width(width), height(height) {
		idx = idy = 0;
	}
	~Character() {}

	void draw(Graphics^ g, Bitmap^ bmp) {
		Rectangle sectionShow = Rectangle(idx * width, idy * height, width, height);
		Rectangle zoom = Rectangle(x, y, width * 0.4, height * 0.4);
		g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
	}

	virtual void move() {}

	int getX() { return x; }
	int getY() { return y; }

	// --- NUEVO MÉTODO AGREGADO ---
	void setPosition(int newX, int newY) {
		x = newX;
		y = newY;
	}
	// -----------------------------

	Rectangle getRectangle() {
		return Rectangle(x, y, width * 0.4, height * 0.4);
	}

	void changeDx() {
		dx *= -1;
	}

	void changeDy() {
		dy *= -1;
	}

};