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
	int levelId;

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

	// Helper para obtener una zona aleatoria válida y configurarla en el enemigo
	void setupEnemyInZone(Character* enemy) {
		int zX, zY, zW, zH; // Variables para la zona (X, Y, Ancho, Alto)

		if (levelId == 0) {
			// Nivel 0: Habitación
			zX = 150; zY = 150; zW = 900; zH = 400;
		}
		else {
			// Nivel 1: Ciudad
			int zona = rand() % 3;
			switch (zona) {
			case 0: // Parking
				zX = 50; zY = 150; zW = 300; zH = 250;
				break;
			case 1: // Avenida
				zX = 480; zY = 50; zW = 140; zH = 600;
				break;
			case 2: // Vereda Derecha
				zX = 700; zY = 450; zW = 400; zH = 150;
				break;
			default: zX = 0; zY = 0; zW = 100; zH = 100; break;
			}
		}

		// 1. Configurar los límites para que no salga
		enemy->setBounds(zX, zY, zW, zH);

		// 2. Calcular posición inicial aleatoria DENTRO de esos límites
		int randomX = zX + rand() % zW;
		int randomY = zY + rand() % zH;

		// Ajuste fino para asegurar que el sprite no nazca pegado al borde derecho/inferior
		if (randomX + 30 > zX + zW) randomX = zX + zW - 30;
		if (randomY + 40 > zY + zH) randomY = zY + zH - 40;

		enemy->setPosition(randomX, randomY);
	}

	void createEnemies(Bitmap^ bmpEnemy1, Bitmap^ bmpEnemy2, Bitmap^ bmpEnemy3) {
		enemies1.clear(); enemies2.clear(); enemies3.clear();
		int count = rand() % 3 + 3;

		for (int i = 0; i < count; i++) {
			// Creamos el enemigo y llamamos al helper para configurarlo
			Enemy1* e1 = new Enemy1(bmpEnemy1->Width / 4, bmpEnemy1->Height / 4);
			setupEnemyInZone(e1);
			enemies1.push_back(e1);

			Enemy2* e2 = new Enemy2(bmpEnemy2->Width / 4, bmpEnemy2->Height / 4);
			setupEnemyInZone(e2);
			enemies2.push_back(e2);

			Enemy3* e3 = new Enemy3(bmpEnemy3->Width / 4, bmpEnemy3->Height / 4);
			setupEnemyInZone(e3);
			enemies3.push_back(e3);
		}
	}

	// ... Resto de métodos iguales ...
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

	void drawEverything(Graphics^ g, Bitmap^ bmpHero1, Bitmap^ bmpHero2, Bitmap^ bmpEnemy1, Bitmap^ bmpEnemy2, Bitmap^ bmpEnemy3) {

		// DIBUJO DE ZONAS (VERDE)
		SolidBrush^ spawnBrush = gcnew SolidBrush(Color::FromArgb(60, 0, 255, 0));
		Pen^ spawnPen = gcnew Pen(Color::Lime, 2);

		if (levelId == 0) {
			g->FillRectangle(spawnBrush, 150, 150, 900, 400);
			g->DrawRectangle(spawnPen, 150, 150, 900, 400);
		}
		else {
			g->FillRectangle(spawnBrush, 50, 150, 300, 250); // A
			g->DrawRectangle(spawnPen, 50, 150, 300, 250);
			g->FillRectangle(spawnBrush, 480, 50, 140, 600); // B
			g->DrawRectangle(spawnPen, 480, 50, 140, 600);
			g->FillRectangle(spawnBrush, 700, 450, 400, 150); // C
			g->DrawRectangle(spawnPen, 700, 450, 400, 150);
		}
		delete spawnBrush; delete spawnPen;

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
		Character* hero = (selectedHero == 1) ? (Character*)hero1 : (Character*)hero2;

		bool hit = false;
		for (auto e : enemies1) if (hero->getRectangle().IntersectsWith(e->getRectangle())) { hit = true; if (e->getType() == 0) e->changeDx(); else e->changeDy(); }
		for (auto e : enemies2) if (hero->getRectangle().IntersectsWith(e->getRectangle())) { hit = true; if (e->getType() == 0) e->changeDx(); else e->changeDy(); }
		for (auto e : enemies3) if (hero->getRectangle().IntersectsWith(e->getRectangle())) { hit = true; if (e->getType() == 0) e->changeDx(); else e->changeDy(); }

		if (hit) {
			if (selectedHero == 1) hero1->quitarVida(); else hero2->quitarVida();
			invulnerabilityFrames = 120;
		}
	}

	bool checkPortalCollision() {
		if (portal == nullptr || !portal->getIsActive()) return false;
		Character* hero = (selectedHero == 1) ? (Character*)hero1 : (Character*)hero2;
		return hero->getRectangle().IntersectsWith(portal->getRectangle());
	}

	Rectangle getHeroRectangle() {
		return (selectedHero == 1) ? hero1->getRectangle() : hero2->getRectangle();
	}

	void setHeroPosition(int x, int y) {
		if (selectedHero == 1) hero1->setPosition(x, y); else hero2->setPosition(x, y);
	}

	void setInitialSpawn(int x, int y) { setHeroPosition(x, y); }
};