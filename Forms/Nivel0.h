#pragma once
#include "../Controladores/Controller.h"
#include "../Controladores/GameStateManager.h"
#include "../Personajes/CollisionMap.h"
#include "Nivel1.h"

namespace JuegoFinal {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class Nivel0 : public Form
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
        Label^ lbInstrucciones;
        Label^ lbCoordMouse; // Para ver coordenadas
        Panel^ panelJuego;
        Panel^ panelHUD;
        Timer^ timer;

        int timeRemaining;
        int frameCount;
        int requiredTime;
        bool portalSpawned;
        bool storyShown; // Variable para controlar si ya se mostró la historia
        GameStateManager^ gameState;

    public:
        Nivel0(void)
        {
            InitializeComponent();
            InitializeGame();
        }

        ~Nivel0()
        {
            if (controller != nullptr) {
                delete controller;
            }
            if (collisionMap != nullptr) {
                delete collisionMap;
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

            this->Text = L"Nivel 1 - Aprende a Jugar";
            this->ClientSize = System::Drawing::Size(1200, 700);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->BackColor = Color::Black;
            this->KeyPreview = true;
            this->KeyDown += gcnew KeyEventHandler(this, &Nivel0::Nivel0_KeyDown);

            // Panel HUD
            panelHUD = gcnew Panel();
            panelHUD->Location = Point(0, 0);
            panelHUD->Size = Drawing::Size(1200, 80);
            panelHUD->BackColor = Color::FromArgb(20, 40, 20);
            this->Controls->Add(panelHUD);

            lbNivel = gcnew Label();
            lbNivel->Text = L"Nivel 1";
            lbNivel->Font = gcnew Drawing::Font("Arial", 18.0f, FontStyle::Bold);
            lbNivel->ForeColor = Color::LimeGreen;
            lbNivel->AutoSize = true;
            lbNivel->Location = Point(20, 25);
            panelHUD->Controls->Add(lbNivel);

            lbVidas = gcnew Label();
            lbVidas->Text = L"Vidas: 5";
            lbVidas->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            lbVidas->ForeColor = Color::Red;
            lbVidas->AutoSize = true;
            lbVidas->Location = Point(230, 28);
            panelHUD->Controls->Add(lbVidas);

            lbTiempo = gcnew Label();
            lbTiempo->Text = L"Tiempo: 30s";
            lbTiempo->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            lbTiempo->ForeColor = Color::Yellow;
            lbTiempo->AutoSize = true;
            lbTiempo->Location = Point(460, 28);
            panelHUD->Controls->Add(lbTiempo);

            lbPuntos = gcnew Label();
            lbPuntos->Text = L"Puntos: 0";
            lbPuntos->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            lbPuntos->ForeColor = Color::Gold;
            lbPuntos->AutoSize = true;
            lbPuntos->Location = Point(730, 28);
            panelHUD->Controls->Add(lbPuntos);

            lbObjetivo = gcnew Label();
            lbObjetivo->Text = L"¡Encuentra la SALIDA antes del tiempo!";
            lbObjetivo->Font = gcnew Drawing::Font("Arial", 12.0f, FontStyle::Bold);
            lbObjetivo->ForeColor = Color::LightGreen;
            lbObjetivo->AutoSize = true;
            lbObjetivo->Location = Point(880, 28);
            panelHUD->Controls->Add(lbObjetivo);

            // Label para coordenadas del mouse
            lbCoordMouse = gcnew Label();
            lbCoordMouse->Text = L"Mouse: (0, 0)";
            lbCoordMouse->Font = gcnew Drawing::Font("Arial", 11.0f, FontStyle::Bold);
            lbCoordMouse->ForeColor = Color::Cyan;
            lbCoordMouse->AutoSize = true;
            lbCoordMouse->Location = Point(20, 5);
            panelHUD->Controls->Add(lbCoordMouse);

            // Panel de juego
            panelJuego = gcnew Panel();
            panelJuego->Location = Point(0, 80);
            panelJuego->Size = Drawing::Size(1200, 620);
            panelJuego->BackColor = Color::Black;
            panelJuego->MouseMove += gcnew MouseEventHandler(this, &Nivel0::panelJuego_MouseMove);
            this->Controls->Add(panelJuego);

            // Timer
            timer = gcnew Timer(this->components);
            timer->Interval = 16;
            timer->Tick += gcnew EventHandler(this, &Nivel0::timer_Tick);

            this->ResumeLayout(false);
        }

        void InitializeGame()
        {
            gameState = GameStateManager::getInstance();
            timeRemaining = 30; // 30 segundos para encontrar la salida
            requiredTime = 0;
            frameCount = 0;
            portalSpawned = false;
            storyShown = false; // Inicializamos la bandera de la historia

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

            bmpFondo = gcnew Bitmap("Assets/Background/fondo0.png");

            // Crear mapa de colisiones
            collisionMap = new CollisionMap();
            collisionMap->cargarMapaNivel1();

            int selectedHero = gameState->selectedHero;
            controller = new Controller(selectedHero, bmpHero1, bmpHero2);

            // Establecer spawn inicial del tutorial
            controller->setInitialSpawn(500, 400);

            // Activar portal/puerta inmediatamente
            controller->spawnPortal(60, 290);

            // HACER EL PORTAL INVISIBLE (Requiere el cambio anterior en Controller.h)
            controller->setPortalVisible(false);

            portalSpawned = true;

            timer->Enabled = true;
        }

        void timer_Tick(Object^ sender, EventArgs^ e)
        {
            // ==========================================
            // HISTORIA AL INICIO DEL NIVEL
            // ==========================================
            if (!storyShown) {
                timer->Enabled = false; // Pausar juego para leer

                MessageBox::Show(
                    L"Qué sueño tan raro...",
                    L"Historia",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::None
                );

                MessageBox::Show(
                    L"Soñé que el mundo ahora estaba dominado por la IA...",
                    L"Historia",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information
                );

                MessageBox::Show(
                    L"Voy a salir a dar un paseo.",
                    L"Historia",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information
                );

                storyShown = true; // Marcar como leída
                timer->Enabled = true; // Reanudar juego
                return; // Salir de este tick para no procesar lógica extra
            }

            frameCount++;

            if (frameCount % 60 == 0 && timeRemaining > 0) {
                timeRemaining--;
                lbTiempo->Text = "Tiempo: " + timeRemaining.ToString() + "s";

                // Efecto visual si queda poco tiempo
                if (timeRemaining <= 10) {
                    lbTiempo->ForeColor = Color::Red;
                }
            }

            // ==========================================
            // CONDICIÓN DE DERROTA POR TIEMPO
            // ==========================================
            if (timeRemaining <= 0) {
                timer->Enabled = false;
                MessageBox::Show(
                    "¡SE ACABÓ EL TIEMPO!\n\n" +
                    "No lograste encontrar la salida a tiempo.\n" +
                    "Inténtalo de nuevo.",
                    "GAME OVER",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Error
                );
                this->Close();
                return;
            }

            controller->moveEverything(buffer->Graphics);
            controller->collision();

            int vidas = controller->getVidasHero();
            lbVidas->Text = "Vidas: " + vidas.ToString();

            if (vidas <= 2) {
                lbVidas->ForeColor = Color::Red;
            }
            else if (vidas <= 4) {
                lbVidas->ForeColor = Color::Orange;
            }
            else {
                lbVidas->ForeColor = Color::LimeGreen;
            }

            buffer->Graphics->Clear(Color::Black);
            buffer->Graphics->DrawImage(bmpFondo, 0, 0, panelJuego->Width, panelJuego->Height);

            // Dibujar instrucciones en pantalla
            DibujarInstrucciones();

            controller->drawEverything(buffer->Graphics, bmpHero1, bmpHero2,
                bmpEnemy1, bmpEnemy2, bmpEnemy3);

            buffer->Render(g);

            if (portalSpawned && controller->checkPortalCollision()) {
                timer->Enabled = false;
                MostrarPantallaTransicion();
                return;
            }

            // Derrota por vidas (aunque no hay enemigos en tutorial por ahora)
            if (controller->getVidasHero() <= 0) {
                timer->Enabled = false;
                this->Close();
            }
        }

        void DibujarInstrucciones()
        {
            System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 16.0f, FontStyle::Bold);
            SolidBrush^ brush = gcnew SolidBrush(Color::FromArgb(200, 255, 255, 255));

            String^ texto =
                "CONTROLES:\n\n" +
                "W - Arriba\n" +
                "A - Izquierda\n" +
                "S - Abajo\n" +
                "D - Derecha\n\n";

            buffer->Graphics->DrawString(texto, font, brush, 50.0f, 50.0f);

            delete font;
            delete brush;

            // Dibujar objetivo
            System::Drawing::Font^ font2 = gcnew System::Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            SolidBrush^ brush2 = gcnew SolidBrush(Color::Yellow);

            String^ objetivo = "¡VE LA PUERTA ANARANJADA!";
            buffer->Graphics->DrawString(objetivo, font2, brush2, 350, 520);

            delete font2;
            delete brush2;
        }

        void MostrarPantallaTransicion() {
            gameState->addScore(100);

            MessageBox::Show(
                "¡LO ENCONTRASTE!\n\n" +
                "Nivel 1 completado.\n" +
                "Puntuacion: " + gameState->score.ToString() + "\n\n" +
                "Preparate para el NIVEL 2...",
                "¡Excelente!",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information
            );

            gameState->nextLevel();

            this->Hide();
            Nivel1^ nivel1 = gcnew Nivel1();
            nivel1->ShowDialog();
            delete nivel1;
            this->Close();
        }

        void Nivel0_KeyDown(Object^ sender, KeyEventArgs^ e)
        {
            // Guardar posición anterior
            Rectangle heroRect = controller->getHeroRectangle();
            int posXAnterior = heroRect.X;
            int posYAnterior = heroRect.Y;

            // Realizar movimiento
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
                    "Salir del juego?",
                    "Pausa",
                    MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
                {
                    this->Close();
                }
                else {
                    timer->Enabled = true;
                }
                return;
            default:
                return;
            }

            // Obtener nueva posición
            Rectangle newRect = controller->getHeroRectangle();
            int posX = newRect.X;
            int posY = newRect.Y;
            int ancho = newRect.Width;
            int alto = newRect.Height;

            // Límites de pantalla
            int anchoFrm = (int)buffer->Graphics->VisibleClipBounds.Width;
            int altoFrm = (int)buffer->Graphics->VisibleClipBounds.Height;

            if (posX < 0) posX = 0;
            if (posY < 0) posY = 0;
            if (posX + ancho > anchoFrm)
                posX = anchoFrm - ancho;
            if (posY + alto > altoFrm)
                posY = altoFrm - alto;

            // Verificar colisión con paredes del mapa
            if (collisionMap->hayColision(posX, posY, ancho, alto)) {
                // Si hay colisión, revertir a posición anterior
                posX = posXAnterior;
                posY = posYAnterior;
            }

            // Aplicar posición final
            controller->setHeroPosition(posX, posY);
        }

        void panelJuego_MouseMove(Object^ sender, MouseEventArgs^ e) {
            // Mostrar coordenadas del mouse en tiempo real
            lbCoordMouse->Text = "Mouse: (" + e->X + ", " + e->Y + ")";
        }
    };
}