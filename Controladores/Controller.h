#pragma once

#include<vector>
#include "../Personajes/Hero1.h"
#include "../Personajes/Hero2.h"
#include "../Personajes/Enemy1.h"
#include "../Personajes/Enemy2.h"
#include "../Personajes/Enemy3.h"
#include "../Personajes/Portal.h"

using namespace std;
using namespace System::Drawing;

class Controller {
private:
	Hero1* hero1;
	Hero2* hero2;
	vector<Enemy1*> enemies1;
	vector<Enemy2*> enemies2;
	vector<Enemy3*> enemies3;
	Portal* portal;

	int selectedHero;
	bool portalSpawned;
	int invulnerabilityFrames;
	int levelId; // 0 = Tutorial, 1 = Ciudad

public:
	Controller(int sh, Bitmap^ bmpHero1, Bitmap^ bmpHero2) {
		hero1 = new Hero1(bmpHero1->Width / 4, bmpHero1->Height / 4);
		hero2 = new Hero2(bmpHero2->Width / 4, bmpHero2->Height / 4);
		portal = nullptr;
		selectedHero = sh;
		portalSpawned = false;
		invulnerabilityFrames = 0;
		levelId = 1;
	}

	~Controller() {
		delete hero1;
		delete hero2;
		for (int i = 0; i < enemies1.size(); i++) delete enemies1[i];
		for (int i = 0; i < enemies2.size(); i++) delete enemies2[i];
		for (int i = 0; i < enemies3.size(); i++) delete enemies3[i];
		if (portal != nullptr) delete portal;
	}

	void setLevel(int id) {
		levelId = id;
	}

	// --- LÓGICA DE SPAWN (COORDENADAS REALES) ---
	Point getValidSpawnPoint() {
		int x, y;

		if (levelId == 0) {
			// Nivel 0: Habitación
			x = rand() % 900 + 150;
			y = rand() % 400 + 150;
		}
		else {
			// Nivel 1: Ciudad
			int zona = rand() % 3;
			switch (zona) {
			case 0: // Parking
				x = rand() % 300 + 50;
				y = rand() % 250 + 150;
				break;
			case 1: // Avenida
				x = rand() % 140 + 480;
				y = rand() % 600 + 50;
				break;
			case 2: // Derecha
				x = rand() % 400 + 700;
				y = rand() % 150 + 450;
				break;
			default: x = 100; y = 100; break;
			}
		}
		return Point(x, y);
	}

	void createEnemies(Bitmap^ bmpEnemy1, Bitmap^ bmpEnemy2, Bitmap^ bmpEnemy3) {
		enemies1.clear(); enemies2.clear(); enemies3.clear();
		int count = rand() % 3 + 3;

		for (int i = 0; i < count; i++) {
			Enemy1* e1 = new Enemy1(bmpEnemy1->Width / 4, bmpEnemy1->Height / 4);
			Point p1 = getValidSpawnPoint();
			e1->setPosition(p1.X, p1.Y);
			enemies1.push_back(e1);

			Enemy2* e2 = new Enemy2(bmpEnemy2->Width / 4, bmpEnemy2->Height / 4);
			Point p2 = getValidSpawnPoint();
			e2->setPosition(p2.X, p2.Y);
			enemies2.push_back(e2);

			Enemy3* e3 = new Enemy3(bmpEnemy3->Width / 4, bmpEnemy3->Height / 4);
			Point p3 = getValidSpawnPoint();
			e3->setPosition(p3.X, p3.Y);
			enemies3.push_back(e3);
		}
	}

	void spawnPortal(int x, int y) {
		if (portal == nullptr) {
			portal = new Portal(x, y);
			portal->activate();
			portalSpawned = true;
		}
	}

	void spawnPortalCentro(int screenWidth, int screenHeight) {
		int portalX = screenWidth / 2 - 40;
		int portalY = screenHeight / 2 - 50;
		spawnPortal(portalX, portalY);
	}

	void setPortalVisible(bool v) {
		if (portal != nullptr) portal->setVisible(v);
	}

	bool isPortalSpawned() { return portalSpawned; }

	// --- NUEVO MÉTODO PARA DIBUJAR ZONAS (SOLICITADO) ---
	void drawSpawnZones(Graphics^ g) {
		// Pinceles temporales para debug
		SolidBrush^ debugBrush = gcnew SolidBrush(Color::FromArgb(60, 0, 255, 0)); // Verde translúcido
		Pen^ debugPen = gcnew Pen(Color::Lime, 2);

		if (levelId == 0) {
			// Nivel 0
			g->FillRectangle(debugBrush, 150, 150, 900, 400);
			g->DrawRectangle(debugPen, 150, 150, 900, 400);
			g->DrawString("ZONA SPAWN N0", gcnew System::Drawing::Font("Arial", 10), Brushes::Lime, 150, 130);
		}
		else {
			// Nivel 1 (Ciudad)
			// Zona A (Parking)
			g->FillRectangle(debugBrush, 50, 150, 300, 250);
			g->DrawRectangle(debugPen, 50, 150, 300, 250);
			g->DrawString("Parking", gcnew System::Drawing::Font("Arial", 10), Brushes::Lime, 50, 130);

			// Zona B (Avenida)
			g->FillRectangle(debugBrush, 480, 50, 140, 600);
			g->DrawRectangle(debugPen, 480, 50, 140, 600);
			g->DrawString("Calle", gcnew System::Drawing::Font("Arial", 10), Brushes::Lime, 480, 30);

			// Zona C (Derecha)
			g->FillRectangle(debugBrush, 700, 450, 400, 150);
			g->DrawRectangle(debugPen, 700, 450, 400, 150);
			g->DrawString("Vereda", gcnew System::Drawing::Font("Arial", 10), Brushes::Lime, 700, 430);
		}

		delete debugBrush;
		delete debugPen;
	}

	void drawEverything(Graphics^ g, Bitmap^ bmpHero1, Bitmap^ bmpHero2, Bitmap^ bmpEnemy1, Bitmap^ bmpEnemy2, Bitmap^ bmpEnemy3) {

		// LLAMADA AL MÉTODO DE DIBUJADO DE ZONAS
		drawSpawnZones(g);

		if (portal != nullptr) portal->draw(g);

		for (int i = 0; i < enemies1.size(); i++) enemies1[i]->draw(g, bmpEnemy1);
		for (int i = 0; i < enemies2.size(); i++) enemies2[i]->draw(g, bmpEnemy2);
		for (int i = 0; i < enemies3.size(); i++) enemies3[i]->draw(g, bmpEnemy3);

		if (selectedHero == 1) {
			hero1->draw(g, bmpHero1);
			if (invulnerabilityFrames > 0 && (invulnerabilityFrames / 5) % 2 == 0) {
				SolidBrush^ shieldBrush = gcnew SolidBrush(Color::FromArgb(100, 0, 255, 255));
				Rectangle h = hero1->getRectangle();
				g->FillEllipse(shieldBrush, h.X - 5, h.Y - 5, h.Width + 10, h.Height + 10);
				delete shieldBrush;
			}
		}
		else {
			hero2->draw(g, bmpHero2);
			if (invulnerabilityFrames > 0 && (invulnerabilityFrames / 5) % 2 == 0) {
				SolidBrush^ shieldBrush = gcnew SolidBrush(Color::FromArgb(100, 0, 255, 255));
				Rectangle h = hero2->getRectangle();
				g->FillEllipse(shieldBrush, h.X - 5, h.Y - 5, h.Width + 10, h.Height + 10);
				delete shieldBrush;
			}
		}
	}

	void moveEverything(Graphics^ g) {
		for (int i = 0; i < enemies1.size(); i++) enemies1[i]->move(g);
		for (int i = 0; i < enemies2.size(); i++) enemies2[i]->move(g);
		for (int i = 0; i < enemies3.size(); i++) enemies3[i]->move(g);
		if (invulnerabilityFrames > 0) invulnerabilityFrames--;
	}

	void moveHero(Graphics^ g, char c) {
		if (selectedHero == 1) hero1->move(g, c); else hero2->move(g, c);
	}

	int getVidasHero() {
		return (selectedHero == 1) ? hero1->getVidas() : hero2->getVidas();
	}

	void collision() {
		if (invulnerabilityFrames > 0) return;

		auto check = [&](Character* h) {
			bool hit = false;
			for (auto e : enemies1) if (h->getRectangle().IntersectsWith(e->getRectangle())) { hit = true; if (e->getType() == 0) e->changeDx(); else e->changeDy(); }
			for (auto e : enemies2) if (h->getRectangle().IntersectsWith(e->getRectangle())) { hit = true; if (e->getType() == 0) e->changeDx(); else e->changeDy(); }
			for (auto e : enemies3) if (h->getRectangle().IntersectsWith(e->getRectangle())) { hit = true; if (e->getType() == 0) e->changeDx(); else e->changeDy(); }

			if (hit) {
				if (selectedHero == 1) hero1->quitarVida(); else hero2->quitarVida();
				invulnerabilityFrames = 120;
			}
			};

		if (selectedHero == 1) check(hero1); else check(hero2);
	}

	bool checkPortalCollision() {
		if (portal == nullptr || !portal->getIsActive()) return false;
		return getHeroRectangle().IntersectsWith(portal->getRectangle());
	}

	Rectangle getHeroRectangle() {
		return (selectedHero == 1) ? hero1->getRectangle() : hero2->getRectangle();
	}

	void setHeroPosition(int x, int y) {
		if (selectedHero == 1) hero1->setPosition(x, y); else hero2->setPosition(x, y);
	}

	void setInitialSpawn(int x, int y) { setHeroPosition(x, y); }
};