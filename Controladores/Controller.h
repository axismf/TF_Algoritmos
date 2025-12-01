#pragma once

#include <vector>
#include "../Personajes/Hero1.h"
#include "../Personajes/Hero2.h"
#include "../Personajes/Enemy1.h"
#include "../Personajes/Enemy2.h"
#include "../Personajes/Enemy3.h"
#include "../Personajes/Portal.h"
#include "GameConfig.h" 

using namespace std;
using namespace System::Drawing;
using namespace JuegoFinal;

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

    // AQUI ES DONDE EDITAS LA LOGICA DE APARICIÓN
    void setupEnemyInZone(Character* enemy) {
        int zX, zY, zW, zH;

        if (levelId == 0) {
            // Tutorial
            zX = 150; zY = 150; zW = 900; zH = 400;
        }
        else if (levelId == 1) {
            // Nivel 1: Ciudad (Zonas separadas)
            int zona = rand() % 3;
            switch (zona) {
            case 0: // Parking (Izquierda)
                zX = 50; zY = 150; zW = 300; zH = 250;
                break;
            case 1: // Avenida (Centro)
                zX = 480; zY = 50; zW = 140; zH = 600;
                break;
            case 2: // Vereda (Derecha Abajo)
                zX = 700; zY = 450; zW = 400; zH = 150;
                break;
            }
        }
        else {
            // Nivel 2 y 3 (Pantalla completa por defecto)
            zX = 50; zY = 50; zW = GameConfig::WINDOW_WIDTH - 100; zH = GameConfig::WINDOW_HEIGHT - 150;
        }

        // LÍMITES
        enemy->setBounds(zX, zY, zW, zH);

        // POSICIÓN ALEATORIA SEGURA (Corregido para que no se salgan)
        int safeW = zW - 60; // Restamos tamaño del enemigo
        int safeH = zH - 60;

        if (safeW <= 0) safeW = 10;
        if (safeH <= 0) safeH = 10;

        int randomX = zX + (rand() % safeW);
        int randomY = zY + (rand() % safeH);

        enemy->setPosition(randomX, randomY);
    }

    void createEnemies(Bitmap^ bmpEnemy1, Bitmap^ bmpEnemy2, Bitmap^ bmpEnemy3) {
        enemies1.clear(); enemies2.clear(); enemies3.clear();
        int count = rand() % 3 + 3;

        for (int i = 0; i < count; i++) {
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

        // AQUI DIBUJAS LAS ZONAS VISUALMENTE (COPIA LOS MISMOS NUMEROS QUE EN setupEnemyInZone)
        SolidBrush^ spawnBrush = gcnew SolidBrush(Color::FromArgb(40, 0, 255, 0));
        Pen^ spawnPen = gcnew Pen(Color::Lime, 2);

        if (levelId == 0) {
            g->FillRectangle(spawnBrush, 150, 150, 900, 400);
            g->DrawRectangle(spawnPen, 150, 150, 900, 400);
        }
        else if (levelId == 1) {
            // Parking
            g->FillRectangle(spawnBrush, 50, 150, 300, 250);
            g->DrawRectangle(spawnPen, 50, 150, 300, 250);

            // Avenida
            g->FillRectangle(spawnBrush, 480, 50, 140, 600);
            g->DrawRectangle(spawnPen, 480, 50, 140, 600);

            // Vereda
            g->FillRectangle(spawnBrush, 700, 450, 400, 150);
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