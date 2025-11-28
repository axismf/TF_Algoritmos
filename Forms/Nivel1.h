#pragma once
#include "../Controladores/Controller.h"
#include "../Controladores/GameStateManager.h"

namespace JuegoFinal {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class Nivel1 : public Form  // ⬅️ Nivel1 (no Nivel1Form)
    {
    private:
        Graphics^ g;
        BufferedGraphicsContext^ space;
        BufferedGraphics^ buffer;

        Bitmap^ bmpHero1;
        Bitmap^ bmpHero2;
        Bitmap^ bmpEnemy1;
        Bitmap^ bmpFondo;

        Controller* controller;

        Label^ lbVidas;
        Label^ lbTiempo;
        Panel^ panelJuego;
        Timer^ timer;

        int timeRemaining;
        int frameCount;
        GameStateManager^ gameState;

    public:
        Nivel1(void)  // ⬅️ Constructor con nombre Nivel1
        {
            InitializeComponent();
            InitializeGame();
        }

        ~Nivel1()
        {
            if (controller != nullptr) {
                delete controller;
            }
        }

    private:
        void InitializeComponent(void)
        {
            this->SuspendLayout();
            // 
            // Nivel1
            // 
            this->BackColor = System::Drawing::SystemColors::ActiveCaption;
            this->ClientSize = System::Drawing::Size(278, 244);
            this->Name = L"Nivel1";
            this->ResumeLayout(false);

        }

        void InitializeGame()
        {
            gameState = GameStateManager::getInstance();
            timeRemaining = 60;
            frameCount = 0;

            g = panelJuego->CreateGraphics();
            space = BufferedGraphicsManager::Current;
            buffer = space->Allocate(g, panelJuego->ClientRectangle);

            bmpHero1 = gcnew Bitmap("Assets/Sprites/prota.png");
            bmpHero1->MakeTransparent(bmpHero1->GetPixel(0, 0));

            bmpHero2 = gcnew Bitmap("Assets/Sprites/IA.png");
            bmpHero2->MakeTransparent(bmpHero2->GetPixel(0, 0));

            bmpEnemy1 = gcnew Bitmap("Assets/Sprites/roboto.png");
            bmpFondo = gcnew Bitmap("Assets/Backgrounds/fondo1.png");

            int selectedHero = gameState->selectedHero;
            controller = new Controller(selectedHero, bmpHero1, bmpHero2);
            controller->createEnemies(bmpEnemy1, bmpEnemy1, bmpEnemy1);

            timer->Enabled = true;
        }

        void timer_Tick(Object^ sender, EventArgs^ e)
        {
            frameCount++;

            if (frameCount % 60 == 0 && timeRemaining > 0) {
                timeRemaining--;
                lbTiempo->Text = "Tiempo: " + timeRemaining.ToString();
            }

            controller->moveEverything(buffer->Graphics);
            controller->collision();

            lbVidas->Text = "Vidas: " + controller->getVidasHero().ToString();

            buffer->Graphics->Clear(Color::Black);
            buffer->Graphics->DrawImage(bmpFondo, 0, 0, panelJuego->Width, panelJuego->Height);
            controller->drawEverything(buffer->Graphics, bmpHero1, bmpHero2,
                bmpEnemy1, bmpEnemy1, bmpEnemy1);
            buffer->Render(g);

            if (timeRemaining <= 0 && controller->getVidasHero() > 0) {
                timer->Enabled = false;
                MessageBox::Show("NIVEL 1 COMPLETADO!\n\nProximamente: Nivel 2",
                    "Victoria", MessageBoxButtons::OK, MessageBoxIcon::Information);
                this->Close();
            }

            if (controller->getVidasHero() <= 0) {
                timer->Enabled = false;
                MessageBox::Show("GAME OVER!\n\nVidas agotadas",
                    "Derrota", MessageBoxButtons::OK, MessageBoxIcon::Error);
                this->Close();
            }
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
                if (MessageBox::Show("Volver al menu?", "Pausa",
                    MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
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