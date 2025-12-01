#pragma once
#include "../Controladores/GameStateManager.h"
#include "Nivel0.h"

namespace JuegoFinal {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SelectCharacterForm : public Form
    {
    private:
        Label^ lblTitulo;
        Panel^ panelHero1;
        Panel^ panelHero2;
        Panel^ panelIA;
        Button^ btnHero1;
        Button^ btnHero2;
        Button^ btnIA;
        Button^ btnVolver;
        Label^ lblHero1Info;
        Label^ lblHero2Info;
        Label^ lblIAInfo;

    public:
        SelectCharacterForm(void)
        {
            InitializeComponent();
        }

    private:
        void InitializeComponent()
        {
            this->Text = L"Seleccionar Personaje";
            this->Size = Drawing::Size(900, 600);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->BackColor = Color::FromArgb(25, 25, 35);

            // Título
            lblTitulo = gcnew Label();
            lblTitulo->Text = L"ELIGE TU PERSONAJE";
            lblTitulo->Font = gcnew Drawing::Font("Arial", 28.0f, FontStyle::Bold);
            lblTitulo->ForeColor = Color::White;
            lblTitulo->AutoSize = true;
            lblTitulo->Location = Point(250, 30);
            this->Controls->Add(lblTitulo);

            // ============ PANEL HERO 1 ============
            panelHero1 = gcnew Panel();
            panelHero1->Location = Point(50, 120);
            panelHero1->Size = Drawing::Size(230, 320);
            panelHero1->BackColor = Color::FromArgb(40, 40, 50);
            panelHero1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->Controls->Add(panelHero1);

            Label^ lblHero1Titulo = gcnew Label();
            lblHero1Titulo->Text = L"HÉROE 1";
            lblHero1Titulo->Font = gcnew Drawing::Font("Arial", 16.0f, FontStyle::Bold);
            lblHero1Titulo->ForeColor = Color::FromArgb(0, 150, 255);
            lblHero1Titulo->AutoSize = true;
            lblHero1Titulo->Location = Point(65, 15);
            panelHero1->Controls->Add(lblHero1Titulo);

            Label^ lblHero1Nombre = gcnew Label();
            lblHero1Nombre->Text = L"\"VELOCISTA\"";
            lblHero1Nombre->Font = gcnew Drawing::Font("Arial", 12.0f, FontStyle::Italic);
            lblHero1Nombre->ForeColor = Color::LightGray;
            lblHero1Nombre->AutoSize = true;
            lblHero1Nombre->Location = Point(60, 45);
            panelHero1->Controls->Add(lblHero1Nombre);

            // Imagen placeholder Hero1
            PictureBox^ imgHero1 = gcnew PictureBox();
            imgHero1->Location = Point(40, 80);
            imgHero1->Size = Drawing::Size(150, 100);
            imgHero1->BackColor = Color::FromArgb(0, 120, 215);
            imgHero1->SizeMode = PictureBoxSizeMode::CenterImage;
            panelHero1->Controls->Add(imgHero1);

            lblHero1Info = gcnew Label();
            lblHero1Info->Text = L"⚡ VELOCIDAD: Alta\n❤️ VIDAS: 5\n\n💨 Perfecto para jugadores\n   ágiles y estratégicos";
            lblHero1Info->Font = gcnew Drawing::Font("Arial", 10.0f);
            lblHero1Info->ForeColor = Color::White;
            lblHero1Info->AutoSize = true;
            lblHero1Info->Location = Point(15, 195);
            panelHero1->Controls->Add(lblHero1Info);

            btnHero1 = gcnew Button();
            btnHero1->Text = L"SELECCIONAR";
            btnHero1->Location = Point(40, 270);
            btnHero1->Size = Drawing::Size(150, 35);
            btnHero1->Font = gcnew Drawing::Font("Arial", 11.0f, FontStyle::Bold);
            btnHero1->BackColor = Color::FromArgb(0, 150, 255);
            btnHero1->ForeColor = Color::White;
            btnHero1->FlatStyle = FlatStyle::Flat;
            btnHero1->FlatAppearance->BorderSize = 0;
            btnHero1->Cursor = Cursors::Hand;
            btnHero1->Click += gcnew EventHandler(this, &SelectCharacterForm::btnHero1_Click);
            panelHero1->Controls->Add(btnHero1);

            // ============ PANEL HERO 2 ============
            panelHero2 = gcnew Panel();
            panelHero2->Location = Point(335, 120);
            panelHero2->Size = Drawing::Size(230, 320);
            panelHero2->BackColor = Color::FromArgb(40, 40, 50);
            panelHero2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->Controls->Add(panelHero2);

            Label^ lblHero2Titulo = gcnew Label();
            lblHero2Titulo->Text = L"HÉROE 2";
            lblHero2Titulo->Font = gcnew Drawing::Font("Arial", 16.0f, FontStyle::Bold);
            lblHero2Titulo->ForeColor = Color::FromArgb(76, 175, 80);
            lblHero2Titulo->AutoSize = true;
            lblHero2Titulo->Location = Point(65, 15);
            panelHero2->Controls->Add(lblHero2Titulo);

            Label^ lblHero2Nombre = gcnew Label();
            lblHero2Nombre->Text = L"\"TANQUE\"";
            lblHero2Nombre->Font = gcnew Drawing::Font("Arial", 12.0f, FontStyle::Italic);
            lblHero2Nombre->ForeColor = Color::LightGray;
            lblHero2Nombre->AutoSize = true;
            lblHero2Nombre->Location = Point(70, 45);
            panelHero2->Controls->Add(lblHero2Nombre);

            // Imagen placeholder Hero2
            PictureBox^ imgHero2 = gcnew PictureBox();
            imgHero2->Location = Point(40, 80);
            imgHero2->Size = Drawing::Size(150, 100);
            imgHero2->BackColor = Color::FromArgb(76, 175, 80);
            imgHero2->SizeMode = PictureBoxSizeMode::CenterImage;
            panelHero2->Controls->Add(imgHero2);

            lblHero2Info = gcnew Label();
            lblHero2Info->Text = L"🛡️ VELOCIDAD: Baja\n❤️ VIDAS: 8\n\n🏋️ Ideal para principiantes\n   y jugadores defensivos";
            lblHero2Info->Font = gcnew Drawing::Font("Arial", 10.0f);
            lblHero2Info->ForeColor = Color::White;
            lblHero2Info->AutoSize = true;
            lblHero2Info->Location = Point(15, 195);
            panelHero2->Controls->Add(lblHero2Info);

            btnHero2 = gcnew Button();
            btnHero2->Text = L"SELECCIONAR";
            btnHero2->Location = Point(40, 270);
            btnHero2->Size = Drawing::Size(150, 35);
            btnHero2->Font = gcnew Drawing::Font("Arial", 11.0f, FontStyle::Bold);
            btnHero2->BackColor = Color::FromArgb(76, 175, 80);
            btnHero2->ForeColor = Color::White;
            btnHero2->FlatStyle = FlatStyle::Flat;
            btnHero2->FlatAppearance->BorderSize = 0;
            btnHero2->Cursor = Cursors::Hand;
            btnHero2->Click += gcnew EventHandler(this, &SelectCharacterForm::btnHero2_Click);
            panelHero2->Controls->Add(btnHero2);

            // ============ PANEL IA ============
            panelIA = gcnew Panel();
            panelIA->Location = Point(620, 120);
            panelIA->Size = Drawing::Size(230, 320);
            panelIA->BackColor = Color::FromArgb(40, 40, 50);
            panelIA->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->Controls->Add(panelIA);

            Label^ lblIATitulo = gcnew Label();
            lblIATitulo->Text = L"INTELIGENCIA";
            lblIATitulo->Font = gcnew Drawing::Font("Arial", 15.0f, FontStyle::Bold);
            lblIATitulo->ForeColor = Color::FromArgb(255, 152, 0);
            lblIATitulo->AutoSize = true;
            lblIATitulo->Location = Point(50, 15);
            panelIA->Controls->Add(lblIATitulo);

            Label^ lblIANombre = gcnew Label();
            lblIANombre->Text = L"\"ARTIFICIAL\"";
            lblIANombre->Font = gcnew Drawing::Font("Arial", 12.0f, FontStyle::Italic);
            lblIANombre->ForeColor = Color::LightGray;
            lblIANombre->AutoSize = true;
            lblIANombre->Location = Point(60, 45);
            panelIA->Controls->Add(lblIANombre);

            // Imagen placeholder IA
            PictureBox^ imgIA = gcnew PictureBox();
            imgIA->Location = Point(40, 80);
            imgIA->Size = Drawing::Size(150, 100);
            imgIA->BackColor = Color::FromArgb(255, 152, 0);
            imgIA->SizeMode = PictureBoxSizeMode::CenterImage;
            panelIA->Controls->Add(imgIA);

            lblIAInfo = gcnew Label();
            lblIAInfo->Text = L"🤖 VELOCIDAD: ???\n❤️ VIDAS: ???\n\n⚠️ ADVERTENCIA:\n   Los humanos no pueden\n   vencer a la IA...";
            lblIAInfo->Font = gcnew Drawing::Font("Arial", 10.0f);
            lblIAInfo->ForeColor = Color::FromArgb(255, 200, 100);
            lblIAInfo->AutoSize = true;
            lblIAInfo->Location = Point(15, 195);
            panelIA->Controls->Add(lblIAInfo);

            btnIA = gcnew Button();
            btnIA->Text = L"SELECCIONAR";
            btnIA->Location = Point(40, 270);
            btnIA->Size = Drawing::Size(150, 35);
            btnIA->Font = gcnew Drawing::Font("Arial", 11.0f, FontStyle::Bold);
            btnIA->BackColor = Color::FromArgb(255, 152, 0);
            btnIA->ForeColor = Color::White;
            btnIA->FlatStyle = FlatStyle::Flat;
            btnIA->FlatAppearance->BorderSize = 0;
            btnIA->Cursor = Cursors::Hand;
            btnIA->Click += gcnew EventHandler(this, &SelectCharacterForm::btnIA_Click);
            panelIA->Controls->Add(btnIA);

            // Botón Volver
            btnVolver = gcnew Button();
            btnVolver->Text = L"⬅ VOLVER";
            btnVolver->Location = Point(360, 480);
            btnVolver->Size = Drawing::Size(180, 40);
            btnVolver->Font = gcnew Drawing::Font("Arial", 12.0f, FontStyle::Bold);
            btnVolver->BackColor = Color::FromArgb(183, 28, 28);
            btnVolver->ForeColor = Color::White;
            btnVolver->FlatStyle = FlatStyle::Flat;
            btnVolver->FlatAppearance->BorderSize = 0;
            btnVolver->Cursor = Cursors::Hand;
            btnVolver->Click += gcnew EventHandler(this, &SelectCharacterForm::btnVolver_Click);
            this->Controls->Add(btnVolver);

            // Efectos hover
            btnHero1->MouseEnter += gcnew EventHandler(this, &SelectCharacterForm::btn_MouseEnter);
            btnHero1->MouseLeave += gcnew EventHandler(this, &SelectCharacterForm::btn_MouseLeave);

            btnHero2->MouseEnter += gcnew EventHandler(this, &SelectCharacterForm::btn_MouseEnter);
            btnHero2->MouseLeave += gcnew EventHandler(this, &SelectCharacterForm::btn_MouseLeave);

            btnIA->MouseEnter += gcnew EventHandler(this, &SelectCharacterForm::btn_MouseEnter);
            btnIA->MouseLeave += gcnew EventHandler(this, &SelectCharacterForm::btn_MouseLeave);
        }

        // ============ EVENT HANDLERS ============

        void btnHero1_Click(Object^ sender, EventArgs^ e) {
            GameStateManager^ gameState = GameStateManager::getInstance();
            gameState->selectedHero = 1;
            gameState->resetGame();

            this->Hide();
            Nivel0^ nivel0 = gcnew Nivel0();
            nivel0->ShowDialog();
            delete nivel0;
            this->Close();
        }

        void btnHero2_Click(Object^ sender, EventArgs^ e) {
            GameStateManager^ gameState = GameStateManager::getInstance();
            gameState->selectedHero = 2;
            gameState->resetGame();

            this->Hide();
            Nivel0^ nivel0 = gcnew Nivel0();
            nivel0->ShowDialog();
            delete nivel0;
            this->Close();
        }

        void btnIA_Click(Object^ sender, EventArgs^ e) {
            MostrarPantallaDerrota();
        }

        void btnVolver_Click(Object^ sender, EventArgs^ e) {
            this->Close();
        }

        // ============ EFECTOS HOVER ============

        void btn_MouseEnter(Object^ sender, EventArgs^ e) {
            Button^ btn = safe_cast<Button^>(sender);
            btn->BackColor = Color::FromArgb(
                Math::Min(btn->BackColor.R + 30, 255),
                Math::Min(btn->BackColor.G + 30, 255),
                Math::Min(btn->BackColor.B + 30, 255)
            );
        }

        void btn_MouseLeave(Object^ sender, EventArgs^ e) {
            Button^ btn = safe_cast<Button^>(sender);
            if (btn == btnHero1) {
                btn->BackColor = Color::FromArgb(0, 150, 255);
            }
            else if (btn == btnHero2) {
                btn->BackColor = Color::FromArgb(76, 175, 80);
            }
            else if (btn == btnIA) {
                btn->BackColor = Color::FromArgb(255, 152, 0);
            }
        }

        // ============ PANTALLA DE DERROTA ============

        void MostrarPantallaDerrota() {
            Form^ pantallaDerrota = gcnew Form();
            pantallaDerrota->Text = L"GAME OVER";
            pantallaDerrota->Size = Drawing::Size(600, 400);
            pantallaDerrota->StartPosition = FormStartPosition::CenterParent;
            pantallaDerrota->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
            pantallaDerrota->BackColor = Color::Black;

            // Animación de derrota
            Label^ lblDerrota = gcnew Label();
            lblDerrota->Text = L"⚠️ DERROTA INEVITABLE ⚠️";
            lblDerrota->Font = gcnew Drawing::Font("Arial", 28.0f, FontStyle::Bold);
            lblDerrota->ForeColor = Color::Red;
            lblDerrota->AutoSize = true;
            lblDerrota->Location = Point(80, 50);
            pantallaDerrota->Controls->Add(lblDerrota);

            Label^ lblMensaje1 = gcnew Label();
            lblMensaje1->Text = L"La Inteligencia Artificial es\nSUPERIOR en todos los aspectos...";
            lblMensaje1->Font = gcnew Drawing::Font("Arial", 16.0f, FontStyle::Bold);
            lblMensaje1->ForeColor = Color::FromArgb(255, 100, 100);
            lblMensaje1->AutoSize = true;
            lblMensaje1->TextAlign = ContentAlignment::MiddleCenter;
            lblMensaje1->Location = Point(120, 120);
            pantallaDerrota->Controls->Add(lblMensaje1);

            Label^ lblMensaje2 = gcnew Label();
            lblMensaje2->Text = L"🤖 La IA ha ganado automáticamente 🤖";
            lblMensaje2->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Italic);
            lblMensaje2->ForeColor = Color::Orange;
            lblMensaje2->AutoSize = true;
            lblMensaje2->Location = Point(110, 190);
            pantallaDerrota->Controls->Add(lblMensaje2);

            Label^ lblEstadisticas = gcnew Label();
            lblEstadisticas->Text =
                L"═══════════════════════════\n" +
                L"   ESTADÍSTICAS FINALES\n" +
                L"═══════════════════════════\n\n" +
                L"   Tiempo sobrevivido: 0.00s\n" +
                L"   Enemigos derrotados: 0\n" +
                L"   Puntuación: 0\n\n" +
                L"   Resultado: HUMILLANTE";
            lblEstadisticas->Font = gcnew Drawing::Font("Courier New", 9.0f);
            lblEstadisticas->ForeColor = Color::Gray;
            lblEstadisticas->AutoSize = true;
            lblEstadisticas->Location = Point(140, 230);
            pantallaDerrota->Controls->Add(lblEstadisticas);

            // Botón aceptar derrota
            Button^ btnAceptar = gcnew Button();
            btnAceptar->Text = L"ACEPTAR DERROTA";
            btnAceptar->Location = Point(200, 340);
            btnAceptar->Size = Drawing::Size(200, 40);
            btnAceptar->Font = gcnew Drawing::Font("Arial", 11.0f, FontStyle::Bold);
            btnAceptar->BackColor = Color::DarkRed;
            btnAceptar->ForeColor = Color::White;
            btnAceptar->FlatStyle = FlatStyle::Flat;
            btnAceptar->FlatAppearance->BorderSize = 0;
            btnAceptar->Cursor = Cursors::Hand;
            btnAceptar->Click += gcnew EventHandler(this, &SelectCharacterForm::btnAceptarDerrota_Click);
            btnAceptar->Tag = pantallaDerrota;
            pantallaDerrota->Controls->Add(btnAceptar);

            pantallaDerrota->ShowDialog();
        }

        void btnAceptarDerrota_Click(Object^ sender, EventArgs^ e) {
            Button^ btn = safe_cast<Button^>(sender);
            Form^ ventana = safe_cast<Form^>(btn->Tag);
            ventana->Close();
        }
    };
}