#pragma once
#include "../Controladores/Controller.h"
#include "../Controladores/GameStateManager.h"
#include "../Personajes/CollisionMap.h"

namespace JuegoFinal {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class Nivel2 : public Form
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
        CollisionMap* collisionMap;

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
        int requiredTime;
        bool portalSpawned;
        bool storyShown;
        bool portalMessageShown;
        GameStateManager^ gameState;

    public:
        Nivel2(void)
        {
            InitializeComponent();
            InitializeGame();
        }

        ~Nivel2()
        {
            if (controller != nullptr) delete controller;
            if (collisionMap != nullptr) delete collisionMap;
            if (components != nullptr) delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->SuspendLayout();

            this->Text = L"Nivel 2 - Dimensión del Pasado";
            this->ClientSize = System::Drawing::Size(1200, 700);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->BackColor = Color::Black;
            this->KeyPreview = true;
            this->KeyDown += gcnew KeyEventHandler(this, &Nivel2::Nivel2_KeyDown);

            panelHUD = gcnew Panel();
            panelHUD->Location = Point(0, 0);
            panelHUD->Size = Drawing::Size(1200, 80);
            panelHUD->BackColor = Color::FromArgb(40, 20, 20);
            this->Controls->Add(panelHUD);

            lbNivel = gcnew Label();
            lbNivel->Text = L"NIVEL 2 - FINAL";
            lbNivel->Font = gcnew Drawing::Font("Arial", 18.0f, FontStyle::Bold);
            lbNivel->ForeColor = Color::Red;
            lbNivel->AutoSize = true;
            lbNivel->Location = Point(20, 25);
            panelHUD->Controls->Add(lbNivel);

            lbVidas = gcnew Label();
            lbVidas->Text = L"❤️ Vidas: 5";
            lbVidas->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            lbVidas->ForeColor = Color::Red;
            lbVidas->AutoSize = true;
            lbVidas->Location = Point(250, 28);
            panelHUD->Controls->Add(lbVidas);

            lbTiempo = gcnew Label();
            lbTiempo->Text = L"⏱️ Tiempo: 90s";
            lbTiempo->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            lbTiempo->ForeColor = Color::Yellow;
            lbTiempo->AutoSize = true;
            lbTiempo->Location = Point(480, 28);
            panelHUD->Controls->Add(lbTiempo);

            lbPuntos = gcnew Label();
            lbPuntos->Text = L"⭐ Puntos: 0";
            lbPuntos->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            lbPuntos->ForeColor = Color::Gold;
            lbPuntos->AutoSize = true;
            lbPuntos->Location = Point(750, 28);
            panelHUD->Controls->Add(lbPuntos);

            lbObjetivo = gcnew Label();
            lbObjetivo->Text = L"🎯 Sobrevive 45 segundos";
            lbObjetivo->Font = gcnew Drawing::Font("Arial", 12.0f, FontStyle::Bold);
            lbObjetivo->ForeColor = Color::Orange;
            lbObjetivo->AutoSize = true;
            lbObjetivo->Location = Point(950, 30);
            panelHUD->Controls->Add(lbObjetivo);

            panelJuego = gcnew Panel();
            panelJuego->Location = Point(0, 80);
            panelJuego->Size = Drawing::Size(1200, 620);
            panelJuego->BackColor = Color::Black;
            this->Controls->Add(panelJuego);

            timer = gcnew Timer(this->components);
            timer->Interval = 16;
            timer->Tick += gcnew EventHandler(this, &Nivel2::timer_Tick);

            this->ResumeLayout(false);
        }

        void InitializeGame()
        {
            gameState = GameStateManager::getInstance();
            timeRemaining = 90;
            requiredTime = 45;
            frameCount = 0;
            portalSpawned = false;
            storyShown = false;
            portalMessageShown = false;

            g = panelJuego->CreateGraphics();
            space = BufferedGraphicsManager::Current;
            buffer = space->Allocate(g, panelJuego->ClientRectangle);

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

            bmpFondo = gcnew Bitmap("Assets/Background/fondo2.png");

            collisionMap = new CollisionMap();
            collisionMap->cargarMapaNivel2();

            int selectedHero = gameState->selectedHero;
            controller = new Controller(selectedHero, bmpHero1, bmpHero2);
            controller->setLevel(2);
            controller->setInitialSpawn(200, 200);
            controller->createEnemies(bmpEnemy1, bmpEnemy2, bmpEnemy3);

            lbPuntos->Text = "⭐ Puntos: " + gameState->score.ToString();
            timer->Enabled = true;
        }

        void timer_Tick(Object^ sender, EventArgs^ e)
        {
            if (!storyShown) {
                buffer->Graphics->Clear(Color::Black);
                buffer->Graphics->DrawImage(bmpFondo, 0, 0, panelJuego->Width, panelJuego->Height);
                controller->drawEverything(buffer->Graphics, bmpHero1, bmpHero2, bmpEnemy1, bmpEnemy2, bmpEnemy3);
                buffer->Render(g);
                timer->Enabled = false;
                MessageBox::Show("Se ve como el pasado...", "Nivel 2", MessageBoxButtons::OK, MessageBoxIcon::Information);
                storyShown = true;
                timer->Enabled = true;
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

                    if (!portalMessageShown) {
                        portalMessageShown = true;
                        timer->Enabled = false;
                        MessageBox::Show("Otro portal...", "Nivel 2", MessageBoxButtons::OK, MessageBoxIcon::Information);
                        timer->Enabled = true;
                    }
                }
            }

            controller->moveEverything(buffer->Graphics);
            controller->collision();

            int vidas = controller->getVidasHero();
            lbVidas->Text = "❤️ Vidas: " + vidas.ToString();

            if (vidas <= 2) lbVidas->ForeColor = Color::Red;
            else if (vidas <= 4) lbVidas->ForeColor = Color::Orange;
            else lbVidas->ForeColor = Color::LimeGreen;

            buffer->Graphics->Clear(Color::Black);
            buffer->Graphics->DrawImage(bmpFondo, 0, 0, panelJuego->Width, panelJuego->Height);

            controller->drawEverything(buffer->Graphics, bmpHero1, bmpHero2, bmpEnemy1, bmpEnemy2, bmpEnemy3);

            buffer->Render(g);

            if (portalSpawned && controller->checkPortalCollision()) {
                timer->Enabled = false;
                MostrarPantallaVictoriaFinal();
                return;
            }

            if (timeRemaining <= 0 && controller->getVidasHero() > 0 && !portalSpawned) {
                controller->spawnPortalCentro(panelJuego->Width, panelJuego->Height);
                portalSpawned = true;
            }

            if (controller->getVidasHero() <= 0) {
                timer->Enabled = false;
                MessageBox::Show(
                    "GAME OVER!\n\n" +
                    "Puntuación Final: " + gameState->score.ToString() + "\n" +
                    "Llegaste al Nivel 2",
                    "Derrota",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Error
                );
                this->Close();
            }
        }

        void MostrarPantallaVictoriaFinal() {
            gameState->addScore(1000);

            MessageBox::Show("Continuará...", "Fin", MessageBoxButtons::OK, MessageBoxIcon::Information);

            MessageBox::Show(
                "╔════════════════════════════════╗\n" +
                "║     ¡JUEGO COMPLETADO!         ║\n" +
                "╚════════════════════════════════╝\n\n" +
                "🎉 ¡FELICIDADES! 🎉\n\n" +
                "Has completado todos los niveles\n" +
                "y escapado de las dimensiones!\n\n" +
                "════════════════════════════\n" +
                "📊 ESTADÍSTICAS FINALES:\n" +
                "════════════════════════════\n\n" +
                "⭐ Puntuación Total: " + gameState->score.ToString() + "\n" +
                "🏆 Niveles Completados: 2/2\n" +
                "⏱️ Tiempo Nivel 2: " + (90 - timeRemaining).ToString() + "s\n" +
                "❤️ Vidas Restantes: " + controller->getVidasHero().ToString() + "\n\n" +
                "════════════════════════════\n\n" +
                "¡ERES UN VERDADERO HÉROE!",
                "🏆 ¡VICTORIA TOTAL! 🏆",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );

            this->Close();
        }

        void Nivel2_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            Rectangle heroRect = controller->getHeroRectangle();
            int posXAnterior = heroRect.X;
            int posYAnterior = heroRect.Y;

            switch (e->KeyCode) {
            case Keys::A: controller->moveHero(buffer->Graphics, 'A'); break;
            case Keys::D: controller->moveHero(buffer->Graphics, 'D'); break;
            case Keys::W: controller->moveHero(buffer->Graphics, 'W'); break;
            case Keys::S: controller->moveHero(buffer->Graphics, 'S'); break;
            case Keys::Escape:
                timer->Enabled = false;
                if (MessageBox::Show("¿Volver al menú?\n\n¡Estás en el NIVEL FINAL!", "Pausa", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
                    this->Close();
                else
                    timer->Enabled = true;
                return;
            }

            Rectangle newRect = controller->getHeroRectangle();
            if (collisionMap->hayColision(newRect.X, newRect.Y, newRect.Width, newRect.Height)) {
                controller->setHeroPosition(posXAnterior, posYAnterior);
            }
        }
    };
}