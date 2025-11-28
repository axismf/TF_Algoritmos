#pragma once

#include<vector>
#include "../Personajes/Hero1.h"
#include "../Personajes/Hero2.h"
#include "../Personajes/Enemy1.h"
#include "../Personajes/Enemy2.h"
#include "../Personajes/Enemy3.h"

using namespace std;

class Controller {
private:
	Hero1* hero1;
	Hero2* hero2;
	vector<Enemy1*> enemies1;
	vector<Enemy2*> enemies2;
	vector<Enemy3*> enemies3;
	// EXTRA 
	Character* heroSelected;

	int selectedHero;
public:
	Controller(int sh, Bitmap^ bmpHero1, Bitmap^ bmpHero2) {
		hero1 = new Hero1(bmpHero1->Width / 4, bmpHero1->Height / 4);
		hero2 = new Hero2(bmpHero2->Width / 4, bmpHero2->Height / 4);

		selectedHero = sh;
	}

	~Controller() {
	}

	void createEnemies(Bitmap^ bmpEnemy1, Bitmap^ bmpEnemy2, Bitmap^ bmpEnemy3) {
		int count = rand() % 3 + 2;
		for (int i = 0; i < count; i++) {
			enemies1.push_back(new Enemy1(bmpEnemy1->Width / 4, bmpEnemy1->Height / 4));
			enemies2.push_back(new Enemy2(bmpEnemy2->Width / 4, bmpEnemy2->Height / 4));
			enemies3.push_back(new Enemy3(bmpEnemy3->Width / 4, bmpEnemy3->Height / 4));
		}
	}

	void drawEverything(Graphics^ g, Bitmap^ bmpHero1, Bitmap^ bmpHero2, Bitmap^ bmpEnemy1, Bitmap^ bmpEnemy2, Bitmap^ bmpEnemy3) {
		if (selectedHero == 1) {
			hero1->draw(g, bmpHero1);
		}
		else {
			hero2->draw(g, bmpHero2);
		}


		for (int i = 0; i < enemies1.size(); i++) {
			enemies1[i]->draw(g, bmpEnemy1);
		}

		for (int i = 0; i < enemies2.size(); i++) {
			enemies2[i]->draw(g, bmpEnemy2);
		}

		for (int i = 0; i < enemies3.size(); i++) {
			enemies3[i]->draw(g, bmpEnemy3);
		}

	}

	void moveEverything(Graphics^ g) {
		for (int i = 0; i < enemies1.size(); i++) {
			enemies1[i]->move(g);
		}

		for (int i = 0; i < enemies2.size(); i++) {
			enemies2[i]->move(g);
		}

		for (int i = 0; i < enemies3.size(); i++) {
			enemies3[i]->move(g);
		}
	}

	void moveHero(Graphics^ g, char c) {
		if (selectedHero == 1) {
			hero1->move(g, c);
		}
		else {
			hero2->move(g, c);
		}
	}

	int getVidasHero() {
		if (selectedHero == 1) {
			return hero1->getVidas();
		}

		return hero2->getVidas();
	}

	void collision() {


		if (selectedHero == 1) {
			for (int i = 0; i < enemies1.size(); i++) {
				if (hero1->getRectangle().IntersectsWith(enemies1[i]->getRectangle())) {
					hero1->quitarVida();
					if (enemies1[i]->getType() == 0) {
						enemies1[i]->changeDx();
					}
					else {
						enemies1[i]->changeDy();
					}

				}
			}


			for (int i = 0; i < enemies2.size(); i++) {
				if (hero1->getRectangle().IntersectsWith(enemies2[i]->getRectangle())) {
					hero1->quitarVida();

					if (enemies2[i]->getType() == 0) {
						enemies2[i]->changeDx();
					}
					else {
						enemies2[i]->changeDy();
					}
				}
			}

			for (int i = 0; i < enemies3.size(); i++) {
				if (hero1->getRectangle().IntersectsWith(enemies3[i]->getRectangle())) {
					hero1->quitarVida();

					if (enemies3[i]->getType() == 0) {
						enemies3[i]->changeDx();
					}
					else {
						enemies3[i]->changeDy();
					}
				}
			}
		}

		else {
			for (int i = 0; i < enemies1.size(); i++) {
				if (hero2->getRectangle().IntersectsWith(enemies1[i]->getRectangle())) {
					hero2->quitarVida();
					if (enemies1[i]->getType() == 0) {
						enemies1[i]->changeDx();
					}
					else {
						enemies1[i]->changeDy();
					}

				}
			}

			for (int i = 0; i < enemies2.size(); i++) {
				if (hero2->getRectangle().IntersectsWith(enemies2[i]->getRectangle())) {
					hero2->quitarVida();

					if (enemies2[i]->getType() == 0) {
						enemies2[i]->changeDx();
					}
					else {
						enemies2[i]->changeDy();
					}
				}
			}

			for (int i = 0; i < enemies3.size(); i++) {
				if (hero2->getRectangle().IntersectsWith(enemies3[i]->getRectangle())) {
					hero2->quitarVida();

					if (enemies3[i]->getType() == 0) {
						enemies3[i]->changeDx();
					}
					else {
						enemies3[i]->changeDy();
					}
				}
			}
		}


	}
};