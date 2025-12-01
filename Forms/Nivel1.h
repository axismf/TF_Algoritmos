#pragma once
#include "../Controladores/Controller.h"
#include "../Controladores/GameStateManager.h"
#include "Nivel2.h"

namespace JuegoFinal {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class Nivel1 : public Form
    {
    private:
        Graphics^ g;
        BufferedGraphicsContext^ space;
        BufferedGraphics^ buffer;
        Bitmap^ bmpHero1; Bitmap^ bmpHero2;
        Bitmap^ bmpEnemy1; Bitmap^ bmpEnemy2; Bitmap^ bmpEnemy3;
        Bitmap^ bmpFondo;
        Controller* controller;
        Label^ lbVidas; Label^ lbTiempo; Label^ lbPuntos; Label^ lbObjetivo; Label^ lbNivel;
        Panel^ panelJuego; Panel^ panelHUD;
        Timer^ timer;
        int timeRemaining; int frameCount; int requiredTime;
        bool portalSpawned; bool storyShown;
        GameStateManager^ gameState;

    public:
        Nivel1(void) { InitializeComponent(); InitializeGame(); }
        ~Nivel1() {
            if (controller != nullptr) delete controller;
            if (components != nullptr) delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void) {
            this->components = gcnew System::ComponentModel::Container();
            this->SuspendLayout();
            this->Text = L"Nivel 1 - Dimensión del Caos";
            this->ClientSize = System::Drawing::Size(1200, 700);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->BackColor = Color::Black;
            this->KeyDown += gcnew KeyEventHandler(this, &Nivel1::Nivel1_KeyDown);

            panelHUD = gcnew Panel();
            panelHUD->Location = Point(0, 0);
            panelHUD->Size = Drawing::Size(1200, 80);
            panelHUD->BackColor = Color::FromArgb(30, 30, 40);
            this->Controls->Add(panelHUD);

            lbNivel = gcnew Label(); lbNivel->Text = L"NIVEL 1"; lbNivel->Font = gcnew Drawing::Font("Arial", 18); lbNivel->ForeColor = Color::Cyan; lbNivel->Location = Point(20, 25); lbNivel->AutoSize = true; panelHUD->Controls->Add(lbNivel);
            lbVidas = gcnew Label(); lbVidas->Text = L"❤️ Vidas: 5"; lbVidas->Font = gcnew Drawing::Font("Arial", 14); lbVidas->ForeColor = Color::Red; lbVidas->Location = Point(250, 28); lbVidas->AutoSize = true; panelHUD->Controls->Add(lbVidas);
            lbTiempo = gcnew Label(); lbTiempo->Text = L"⏱️ Tiempo: 60s"; lbTiempo->Font = gcnew Drawing::Font("Arial", 14); lbTiempo->ForeColor = Color::Yellow; lbTiempo->Location = Point(480, 28); lbTiempo->AutoSize = true; panelHUD->Controls->Add(lbTiempo);
            lbPuntos = gcnew Label(); lbPuntos->Text = L"⭐ Puntos: 0"; lbPuntos->Font = gcnew Drawing::Font("Arial", 14); lbPuntos->ForeColor = Color::Gold; lbPuntos->Location = Point(750, 28); lbPuntos->AutoSize = true; panelHUD->Controls->Add(lbPuntos);
            lbObjetivo = gcnew Label(); lbObjetivo->Text = L"🎯 Sobrevive 30 segundos"; lbObjetivo->Font = gcnew Drawing::Font("Arial", 12); lbObjetivo->ForeColor = Color::LightGreen; lbObjetivo->Location = Point(950, 30); lbObjetivo->AutoSize = true; panelHUD->Controls->Add(lbObjetivo);

            panelJuego = gcnew Panel();
            panelJuego->Location = Point(0, 80);
            panelJuego->Size = Drawing::Size(1200, 620);
            panelJuego->BackColor = Color::Black;
            this->Controls->Add(panelJuego);

            timer = gcnew Timer(this->components);
            timer->Interval = 16; // 60 FPS
            timer->Tick += gcnew EventHandler(this, &Nivel1::timer_Tick);
            this->ResumeLayout(false);
        }

        void InitializeGame() {
            gameState = GameStateManager::getInstance();
            timeRemaining = 60; requiredTime = 30; frameCount = 0;
            portalSpawned = false; storyShown = false;

            g = panelJuego->CreateGraphics();
            space = BufferedGraphicsManager::Current;
            buffer = space->Allocate(g, panelJuego->ClientRectangle);

            bmpHero1 = gcnew Bitmap("Assets/Sprites/prota.png"); bmpHero1->MakeTransparent(bmpHero1->GetPixel(0, 0));
            bmpHero2 = gcnew Bitmap("Assets/Sprites/IA.png"); bmpHero2->MakeTransparent(bmpHero2->GetPixel(0, 0));
            bmpEnemy1 = gcnew Bitmap("Assets/Sprites/roboto.png"); bmpEnemy1->MakeTransparent(bmpEnemy1->GetPixel(0, 0));
            bmpEnemy2 = gcnew Bitmap("Assets/Sprites/roboto.png"); bmpEnemy2->MakeTransparent(bmpEnemy2->GetPixel(0, 0));
            bmpEnemy3 = gcnew Bitmap("Assets/Sprites/roboto.png"); bmpEnemy3->MakeTransparent(bmpEnemy3->GetPixel(0, 0));
            bmpFondo = gcnew Bitmap("Assets/Background/fondo1.png");

            controller = new Controller(gameState->selectedHero, bmpHero1, bmpHero2);
            controller->setLevel(1); // Nivel 1 Ciudad
            controller->setInitialSpawn(100, 300);
            controller->createEnemies(bmpEnemy1, bmpEnemy2, bmpEnemy3);

            timer->Enabled = true;
        }

        void timer_Tick(Object^ sender, EventArgs^ e) {
            if (!storyShown) {
                buffer->Graphics->Clear(Color::Black);
                buffer->Graphics->DrawImage(bmpFondo, 0, 0, panelJuego->Width, panelJuego->Height);
                controller->drawEverything(buffer->Graphics, bmpHero1, bmpHero2, bmpEnemy1, bmpEnemy2, bmpEnemy3);
                buffer->Render(g);
                timer->Enabled = false;
                MessageBox::Show("¡No puede ser!, No fue un sueño, ¡Estoy en otra dimensión!", "Nivel 1 - El Caos", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
                storyShown = true; timer->Enabled = true;
                return;
            }

            frameCount++;
            if (frameCount % 60 == 0 && timeRemaining > 0) {
                timeRemaining--;
                lbTiempo->Text = "⏱️ Tiempo: " + timeRemaining.ToString() + "s";
                gameState->addScore(10);
                lbPuntos->Text = "⭐ Puntos: " + gameState->score.ToString();

                if (timeRemaining <= requiredTime && !portalSpawned) {
                    controller->spawnPortalCentro(panelJuego->Width, panelJuego->Height);
                    portalSpawned = true;
                    lbObjetivo->Text = "🌀 ¡PORTAL ABIERTO! Entra para avanzar";
                    lbObjetivo->ForeColor = Color::Magenta;
                }
            }

            controller->moveEverything(buffer->Graphics);
            controller->collision();

            int vidas = controller->getVidasHero();
            lbVidas->Text = "❤️ Vidas: " + vidas.ToString();
            if (vidas <= 2) lbVidas->ForeColor = Color::Red; else if (vidas <= 4) lbVidas->ForeColor = Color::Orange; else lbVidas->ForeColor = Color::LimeGreen;

            buffer->Graphics->Clear(Color::Black);
            buffer->Graphics->DrawImage(bmpFondo, 0, 0, panelJuego->Width, panelJuego->Height);
            controller->drawEverything(buffer->Graphics, bmpHero1, bmpHero2, bmpEnemy1, bmpEnemy2, bmpEnemy3);
            buffer->Render(g);

            if (portalSpawned && controller->checkPortalCollision()) {
                timer->Enabled = false;
                MostrarPantallaTransicion();
                return;
            }

            if (timeRemaining <= 0 && controller->getVidasHero() > 0 && !portalSpawned) {
                controller->spawnPortalCentro(panelJuego->Width, panelJuego->Height);
                portalSpawned = true;
            }

            if (controller->getVidasHero() <= 0) {
                timer->Enabled = false;
                MessageBox::Show("GAME OVER!\nTe atraparon.", "Derrota", MessageBoxButtons::OK, MessageBoxIcon::Error);
                this->Close();
            }
        }

        void MostrarPantallaTransicion() {
            gameState->addScore(500);
            MessageBox::Show("¡NIVEL 1 COMPLETADO!\nPreparándote para el NIVEL 2...", "¡Victoria!", MessageBoxButtons::OK, MessageBoxIcon::Information);
            gameState->nextLevel();
            this->Hide();
            Nivel2^ nivel2 = gcnew Nivel2();
            nivel2->ShowDialog();
            delete nivel2;
            this->Close();
        }

        void Nivel1_KeyDown(Object^ sender, KeyEventArgs^ e) {
            switch (e->KeyCode) {
            case Keys::A: controller->moveHero(buffer->Graphics, 'A'); break;
            case Keys::D: controller->moveHero(buffer->Graphics, 'D'); break;
            case Keys::W: controller->moveHero(buffer->Graphics, 'W'); break;
            case Keys::S: controller->moveHero(buffer->Graphics, 'S'); break;
            case Keys::Escape: timer->Enabled = false; if (MessageBox::Show("¿Volver al menú?", "Pausa", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) this->Close(); else timer->Enabled = true; break;
            }
        }
    };
}