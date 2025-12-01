#pragma once

using namespace System::Drawing;

class Character {
protected:
	int x, y;
	int dx, dy;
	int width, height;
	int idx, idy;
	double zoom = 1.0;

	
	int minX, maxX;
	int minY, maxY;

public:
	Character(int width, int height) : width(width), height(height) {
		idx = idy = 0;
		
		minX = 0; maxX = 5000;
		minY = 0; maxY = 5000;
	}
	~Character() {}

	void draw(Graphics^ g, Bitmap^ bmp) {
		Rectangle sectionShow = Rectangle(idx * width, idy * height, width, height);
		Rectangle zoomRect = Rectangle(x, y, (int)(width * 0.4), (int)(height * 0.4));
		g->DrawImage(bmp, zoomRect, sectionShow, GraphicsUnit::Pixel);
	}

	virtual void move(Graphics^ g) {} 

	
	void setBounds(int x1, int y1, int ancho, int alto) {
		minX = x1;
		minY = y1;
		maxX = x1 + ancho;
		maxY = y1 + alto;
	}

	void setPosition(int newX, int newY) {
		x = newX;
		y = newY;
	}

	int getX() { return x; }
	int getY() { return y; }

	Rectangle getRectangle() {
		return Rectangle(x, y, (int)(width * 0.4), (int)(height * 0.4));
	}

	void changeDx() { dx *= -1; }
	void changeDy() { dy *= -1; }

	
};