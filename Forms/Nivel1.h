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

        Bitmap^ bmpHero1;
        Bitmap^ bmpHero2;
        Bitmap^ bmpEnemy1;
        Bitmap^ bmpEnemy2;
        Bitmap^ bmpEnemy3;
        Bitmap^ bmpFondo;

        Controller* controller;

        // UI Labels
        Label^ lbVidas;
        Label^ lbTiempo;
        Label^ lbPuntos;
        Label^ lbObjetivo;
        Label^ lbNivel;
        Panel^ panelJuego;
        Panel^ panelHUD;
        Timer^ timer;

        int timeRemaining;
        int frameCount;
        int requiredTime; // Tiempo requerido para spawn del portal
        bool portalSpawned;
        bool storyShown; // Variable para controlar la historia
        int storyDelayCounter; // Contador para esperar 3 segundos
        GameStateManager^ gameState;

    public:
        Nivel1(void)
        {
            InitializeComponent();
            InitializeGame();
        }

        ~Nivel1()
        {
            if (controller != nullptr) {
                delete controller;
            }
            if (components != nullptr) {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->SuspendLayout();

            // Configuración de la ventana
            this->Text = L"Nivel 1 - Dimensión del Caos";
            this->ClientSize = System::Drawing::Size(1200, 700);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->BackColor = Color::Black;
            this->KeyPreview = true;
            this->KeyDown += gcnew KeyEventHandler(this, &Nivel1::Nivel1_KeyDown);

            // Panel HUD (arriba)
            panelHUD = gcnew Panel();
            panelHUD->Location = Point(0, 0);
            panelHUD->Size = Drawing::Size(1200, 80);
            panelHUD->BackColor = Color::FromArgb(30, 30, 40);
            this->Controls->Add(panelHUD);

            // Label Nivel
            lbNivel = gcnew Label();
            lbNivel->Text = L"NIVEL 1";
            lbNivel->Font = gcnew Drawing::Font("Arial", 18.0f, FontStyle::Bold);
            lbNivel->ForeColor = Color::Cyan;
            lbNivel->AutoSize = true;
            lbNivel->Location = Point(20, 25);
            panelHUD->Controls->Add(lbNivel);

            // Label Vidas
            lbVidas = gcnew Label();
            lbVidas->Text = L"❤️ Vidas: 5";
            lbVidas->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            lbVidas->ForeColor = Color::Red;
            lbVidas->AutoSize = true;
            lbVidas->Location = Point(250, 28);
            panelHUD->Controls->Add(lbVidas);

            // Label Tiempo
            lbTiempo = gcnew Label();
            lbTiempo->Text = L"⏱️ Tiempo: 60s";
            lbTiempo->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            lbTiempo->ForeColor = Color::Yellow;
            lbTiempo->AutoSize = true;
            lbTiempo->Location = Point(480, 28);
            panelHUD->Controls->Add(lbTiempo);

            // Label Puntos
            lbPuntos = gcnew Label();
            lbPuntos->Text = L"⭐ Puntos: 0";
            lbPuntos->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            lbPuntos->ForeColor = Color::Gold;
            lbPuntos->AutoSize = true;
            lbPuntos->Location = Point(750, 28);
            panelHUD->Controls->Add(lbPuntos);

            // Label Objetivo
            lbObjetivo = gcnew Label();
            lbObjetivo->Text = L"🎯 Sobrevive 30 segundos";
            lbObjetivo->Font = gcnew Drawing::Font("Arial", 12.0f, FontStyle::Bold);
            lbObjetivo->ForeColor = Color::LightGreen;
            lbObjetivo->AutoSize = true;
            lbObjetivo->Location = Point(950, 30);
            panelHUD->Controls->Add(lbObjetivo);

            // Panel de juego (debajo del HUD)
            panelJuego = gcnew Panel();
            panelJuego->Location = Point(0, 80);
            panelJuego->Size = Drawing::Size(1200, 620);
            panelJuego->BackColor = Color::Black;
            this->Controls->Add(panelJuego);

            // Timer
            timer = gcnew Timer(this->components);
            timer->Interval = 16; // ~60 FPS
            timer->Tick += gcnew EventHandler(this, &Nivel1::timer_Tick);

            this->ResumeLayout(false);
        }

        void InitializeGame()
        {
            gameState = GameStateManager::getInstance();
            timeRemaining = 60;
            requiredTime = 30; // Sobrevivir 30 segundos para que aparezca el portal
            frameCount = 0;
            portalSpawned = false;
            storyShown = false; // Inicializar variable de historia
            storyDelayCounter = 0; // Reiniciar contador

            g = panelJuego->CreateGraphics();
            space = BufferedGraphicsManager::Current;
            buffer = space->Allocate(g, panelJuego->ClientRectangle);

            // Cargar sprites
            bmpHero1 = gcnew Bitmap("Assets/Sprites/prota.png");
            bmpHero1->MakeTransparent(bmpHero1->GetPixel(0, 0));

            bmpHero2 = gcnew Bitmap("Assets/Sprites/IA.png");
            bmpHero2->MakeTransparent(bmpHero2->GetPixel(0, 0));

            bmpEnemy1 = gcnew Bitmap("Assets/Sprites/roboto.png");
            bmpEnemy1->MakeTransparent(bmpEnemy1->GetPixel(0, 0));

            bmpEnemy2 = gcnew Bitmap("Assets/Sprites/roboto.png");
            bmpEnemy2->MakeTransparent(bmpEnemy2->GetPixel(0, 0));

            bmpEnemy3 = gcnew Bitmap("Assets/Sprites/roboto.png");
            bmpEnemy3->MakeTransparent(bmpEnemy3->GetPixel(0, 0));

            bmpFondo = gcnew Bitmap("Assets/Background/fondo1.png");

            int selectedHero = gameState->selectedHero;
            controller = new Controller(selectedHero, bmpHero1, bmpHero2);
            controller->setInitialSpawn(100, 300); // Spawn Nivel 1
            controller->createEnemies(bmpEnemy1, bmpEnemy2, bmpEnemy3);

            timer->Enabled = true;
        }

        void timer_Tick(Object^ sender, EventArgs^ e)
        {
            // ==========================================
            // HISTORIA CON RETRASO (3 Segundos)
            // ==========================================
            if (!storyShown) {
                storyDelayCounter++;

                // Dibujamos el fondo y personajes estáticos para que se vea el mapa
                buffer->Graphics->Clear(Color::Black);
                buffer->Graphics->DrawImage(bmpFondo, 0, 0, panelJuego->Width, panelJuego->Height);
                controller->drawEverything(buffer->Graphics, bmpHero1, bmpHero2, bmpEnemy1, bmpEnemy2, bmpEnemy3);
                buffer->Render(g);

                // Esperamos 180 frames (aprox 3 segundos) antes de mostrar el mensaje
                if (storyDelayCounter >= 180) {
                    timer->Enabled = false; // Pausar timer para que no siga contando mientras lees

                    MessageBox::Show(
                        "¡No puede ser!, No fue un sueño",
                        "Historia",
                        MessageBoxButtons::OK,
                        MessageBoxIcon::Exclamation
                    );

                    storyShown = true;
                    timer->Enabled = true; // Reanudar juego
                }

                // IMPORTANTE: Return aquí evita que se ejecute la lógica de movimiento/colisión
                // mientras esperamos, así no te matan.
                return;
            }

            // --- LÓGICA NORMAL DEL JUEGO (Se ejecuta después de la historia) ---

            frameCount++;

            // Actualizar tiempo cada segundo (60 frames)
            if (frameCount % 60 == 0 && timeRemaining > 0) {
                timeRemaining--;
                lbTiempo->Text = "⏱️ Tiempo: " + timeRemaining.ToString() + "s";

                // Agregar puntos por sobrevivir
                gameState->addScore(10);
                lbPuntos->Text = "⭐ Puntos: " + gameState->score.ToString();

                // Verificar si es momento de spawn del portal
                if (timeRemaining <= requiredTime && !portalSpawned) {
                    controller->spawnPortalCentro(panelJuego->Width, panelJuego->Height);
                    portalSpawned = true;
                    lbObjetivo->Text = "🌀 ¡PORTAL ABIERTO! Entra para avanzar";
                    lbObjetivo->ForeColor = Color::Magenta;
                }
            }

            // Mover enemigos y héroe
            controller->moveEverything(buffer->Graphics);
            controller->collision();

            // Actualizar vidas
            int vidas = controller->getVidasHero();
            lbVidas->Text = "❤️ Vidas: " + vidas.ToString();

            // Cambiar color de vidas según cantidad
            if (vidas <= 2) {
                lbVidas->ForeColor = Color::Red;
            }
            else if (vidas <= 4) {
                lbVidas->ForeColor = Color::Orange;
            }
            else {
                lbVidas->ForeColor = Color::LimeGreen;
            }

            // Dibujar todo
            buffer->Graphics->Clear(Color::Black);
            buffer->Graphics->DrawImage(bmpFondo, 0, 0, panelJuego->Width, panelJuego->Height);

            controller->drawEverything(buffer->Graphics, bmpHero1, bmpHero2,
                bmpEnemy1, bmpEnemy2, bmpEnemy3);

            buffer->Render(g);

            // Verificar colisión con portal
            if (portalSpawned && controller->checkPortalCollision()) {
                timer->Enabled = false;
                MostrarPantallaTransicion();
                return;
            }

            // Verificar victoria (tiempo completo)
            if (timeRemaining <= 0 && controller->getVidasHero() > 0) {
                if (!portalSpawned) {
                    controller->spawnPortalCentro(panelJuego->Width, panelJuego->Height);
                    portalSpawned = true;
                    lbObjetivo->Text = "🌀 ¡PORTAL ABIERTO! Entra para avanzar";
                    lbObjetivo->ForeColor = Color::Magenta;
                }
            }

            // Verificar derrota (sin vidas)
            if (controller->getVidasHero() <= 0) {
                timer->Enabled = false;
                MessageBox::Show(
                    "GAME OVER!\n\n" +
                    "Puntuación Final: " + gameState->score.ToString() + "\n" +
                    "Tiempo Sobrevivido: " + (60 - timeRemaining).ToString() + " segundos",
                    "Derrota",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Error
                );
                this->Close();
            }
        }

        void MostrarPantallaTransicion() {
            // Bonus por completar nivel
            gameState->addScore(500);

            MessageBox::Show(
                "¡NIVEL 1 COMPLETADO!\n\n" +
                "🎉 Entraste al portal\n" +
                "⭐ Puntuación: " + gameState->score.ToString() + "\n" +
                "⏱️ Tiempo: " + (60 - timeRemaining).ToString() + "s\n\n" +
                "Preparándote para el NIVEL 2...",
                "¡Victoria!",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );

            // Avanzar al siguiente nivel
            gameState->nextLevel();

            // Abrir Nivel 2
            this->Hide();
            Nivel2^ nivel2 = gcnew Nivel2();
            nivel2->ShowDialog();
            delete nivel2;
            this->Close();
        }

        void Nivel1_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            switch (e->KeyCode) {
            case Keys::A:
                controller->moveHero(buffer->Graphics, 'A');
                break;
            case Keys::D:
                controller->moveHero(buffer->Graphics, 'D');
                break;
            case Keys::W:
                controller->moveHero(buffer->Graphics, 'W');
                break;
            case Keys::S:
                controller->moveHero(buffer->Graphics, 'S');
                break;
            case Keys::Escape:
                timer->Enabled = false;
                if (MessageBox::Show(
                    "¿Volver al menú?\n\nPerderás tu progreso actual",
                    "Pausa",
                    MessageBoxButtons::YesNo,
                    MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
                {
                    this->Close();
                }
                else {
                    timer->Enabled = true;
                }
                break;
            }
        }
    };
}