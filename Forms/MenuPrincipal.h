#pragma once
#include "SelectCharacterForm.h" 

namespace JuegoFinal {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MenuPrincipal : public Form
    {
    private:
        Label^ lblTitulo;
        Button^ btnJugar;
        Button^ btnAyuda;
        Button^ btnSalir;

    public:
        MenuPrincipal(void)
        {
            InitializeComponent();
        }

    private:
        void InitializeComponent()
        {
            this->Text = L"Menu Principal - Juego 2D";
            this->Size = Drawing::Size(800, 600);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->BackColor = Color::FromArgb(20, 20, 30);

            // Título del juego
            lblTitulo = gcnew Label();
            lblTitulo->Text = L"AVENTURA 2D";
            lblTitulo->Font = gcnew Drawing::Font("Arial", 36.0f, FontStyle::Bold);
            lblTitulo->ForeColor = Color::White;
            lblTitulo->AutoSize = true;
            lblTitulo->Location = Point(220, 100);
            this->Controls->Add(lblTitulo);

            // Botón JUGAR
            btnJugar = gcnew Button();
            btnJugar->Text = L"JUGAR";
            btnJugar->Location = Point(300, 250);
            btnJugar->Size = Drawing::Size(200, 50);
            btnJugar->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            btnJugar->BackColor = Color::FromArgb(0, 120, 215);
            btnJugar->ForeColor = Color::White;
            btnJugar->FlatStyle = FlatStyle::Flat;
            btnJugar->FlatAppearance->BorderSize = 0;
            btnJugar->Cursor = Cursors::Hand;
            btnJugar->Click += gcnew EventHandler(this, &MenuPrincipal::btnJugar_Click);
            this->Controls->Add(btnJugar);

            // Botón AYUDA
            btnAyuda = gcnew Button();
            btnAyuda->Text = L"AYUDA";
            btnAyuda->Location = Point(300, 320);
            btnAyuda->Size = Drawing::Size(200, 50);
            btnAyuda->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            btnAyuda->BackColor = Color::FromArgb(0, 150, 136);
            btnAyuda->ForeColor = Color::White;
            btnAyuda->FlatStyle = FlatStyle::Flat;
            btnAyuda->FlatAppearance->BorderSize = 0;
            btnAyuda->Cursor = Cursors::Hand;
            btnAyuda->Click += gcnew EventHandler(this, &MenuPrincipal::btnAyuda_Click);
            this->Controls->Add(btnAyuda);

            // Botón SALIR
            btnSalir = gcnew Button();
            btnSalir->Text = L"SALIR";
            btnSalir->Location = Point(300, 390);
            btnSalir->Size = Drawing::Size(200, 50);
            btnSalir->Font = gcnew Drawing::Font("Arial", 14.0f, FontStyle::Bold);
            btnSalir->BackColor = Color::FromArgb(183, 28, 28);
            btnSalir->ForeColor = Color::White;
            btnSalir->FlatStyle = FlatStyle::Flat;
            btnSalir->FlatAppearance->BorderSize = 0;
            btnSalir->Cursor = Cursors::Hand;
            btnSalir->Click += gcnew EventHandler(this, &MenuPrincipal::btnSalir_Click);
            this->Controls->Add(btnSalir);

            // Efectos hover para botones
            btnJugar->MouseEnter += gcnew EventHandler(this, &MenuPrincipal::btnJugar_MouseEnter);
            btnJugar->MouseLeave += gcnew EventHandler(this, &MenuPrincipal::btnJugar_MouseLeave);

            btnAyuda->MouseEnter += gcnew EventHandler(this, &MenuPrincipal::btnAyuda_MouseEnter);
            btnAyuda->MouseLeave += gcnew EventHandler(this, &MenuPrincipal::btnAyuda_MouseLeave);

            btnSalir->MouseEnter += gcnew EventHandler(this, &MenuPrincipal::btnSalir_MouseEnter);
            btnSalir->MouseLeave += gcnew EventHandler(this, &MenuPrincipal::btnSalir_MouseLeave);
        }

        // ============ EVENT HANDLERS ============

        void btnJugar_Click(Object^ sender, EventArgs^ e) {
            SelectCharacterForm^ selectForm = gcnew SelectCharacterForm();
            selectForm->ShowDialog();
        }

        void btnAyuda_Click(Object^ sender, EventArgs^ e) {
            MostrarVentanaAyuda();
        }

        void btnSalir_Click(Object^ sender, EventArgs^ e) {
            Application::Exit();
        }

        // ============ EFECTOS HOVER ============

        void btnJugar_MouseEnter(Object^ sender, EventArgs^ e) {
            btnJugar->BackColor = Color::FromArgb(0, 150, 255);
        }

        void btnJugar_MouseLeave(Object^ sender, EventArgs^ e) {
            btnJugar->BackColor = Color::FromArgb(0, 120, 215);
        }

        void btnAyuda_MouseEnter(Object^ sender, EventArgs^ e) {
            btnAyuda->BackColor = Color::FromArgb(0, 180, 166);
        }

        void btnAyuda_MouseLeave(Object^ sender, EventArgs^ e) {
            btnAyuda->BackColor = Color::FromArgb(0, 150, 136);
        }

        void btnSalir_MouseEnter(Object^ sender, EventArgs^ e) {
            btnSalir->BackColor = Color::FromArgb(211, 47, 47);
        }

        void btnSalir_MouseLeave(Object^ sender, EventArgs^ e) {
            btnSalir->BackColor = Color::FromArgb(183, 28, 28);
        }

        // ============ VENTANA DE AYUDA ============

        void MostrarVentanaAyuda() {
            Form^ ventanaAyuda = gcnew Form();
            ventanaAyuda->Text = L"Ayuda - Instrucciones del Juego";
            ventanaAyuda->Size = Drawing::Size(600, 500);
            ventanaAyuda->StartPosition = FormStartPosition::CenterParent;
            ventanaAyuda->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            ventanaAyuda->MaximizeBox = false;
            ventanaAyuda->MinimizeBox = false;
            ventanaAyuda->BackColor = Color::White;

            // Panel de contenido
            Panel^ panelContenido = gcnew Panel();
            panelContenido->Location = Point(20, 20);
            panelContenido->Size = Drawing::Size(540, 380);
            panelContenido->AutoScroll = true;
            ventanaAyuda->Controls->Add(panelContenido);

            // Título
            Label^ lblTituloAyuda = gcnew Label();
            lblTituloAyuda->Text = L"📖 CÓMO JUGAR";
            lblTituloAyuda->Font = gcnew Drawing::Font("Arial", 18.0f, FontStyle::Bold);
            lblTituloAyuda->ForeColor = Color::FromArgb(0, 120, 215);
            lblTituloAyuda->AutoSize = true;
            lblTituloAyuda->Location = Point(10, 10);
            panelContenido->Controls->Add(lblTituloAyuda);

            // Historia del juego
            Label^ lblHistoria = gcnew Label();
            lblHistoria->Text = L"🎮 HISTORIA";
            lblHistoria->Font = gcnew Drawing::Font("Arial", 12.0f, FontStyle::Bold);
            lblHistoria->AutoSize = true;
            lblHistoria->Location = Point(10, 50);
            panelContenido->Controls->Add(lblHistoria);

            Label^ lblHistoriaTexto = gcnew Label();
            lblHistoriaTexto->Text = L"Eres un héroe atrapado en diferentes dimensiones.\n" +
                L"Debes sobrevivir a hordas de enemigos y encontrar portales\n" +
                L"para escapar de cada mundo.";
            lblHistoriaTexto->Font = gcnew Drawing::Font("Arial", 10.0f);
            lblHistoriaTexto->AutoSize = true;
            lblHistoriaTexto->Location = Point(10, 75);
            panelContenido->Controls->Add(lblHistoriaTexto);

            // Controles
            Label^ lblControles = gcnew Label();
            lblControles->Text = L"⌨️ CONTROLES";
            lblControles->Font = gcnew Drawing::Font("Arial", 12.0f, FontStyle::Bold);
            lblControles->AutoSize = true;
            lblControles->Location = Point(10, 135);
            panelContenido->Controls->Add(lblControles);

            Label^ lblControlesTexto = gcnew Label();
            lblControlesTexto->Text =
                L"W - Mover arriba\n" +
                L"A - Mover izquierda\n" +
                L"S - Mover abajo\n" +
                L"D - Mover derecha\n" +
                L"ESC - Pausar juego";
            lblControlesTexto->Font = gcnew Drawing::Font("Arial", 10.0f);
            lblControlesTexto->AutoSize = true;
            lblControlesTexto->Location = Point(10, 160);
            panelContenido->Controls->Add(lblControlesTexto);

            // Personajes
            Label^ lblPersonajes = gcnew Label();
            lblPersonajes->Text = L"👤 PERSONAJES";
            lblPersonajes->Font = gcnew Drawing::Font("Arial", 12.0f, FontStyle::Bold);
            lblPersonajes->AutoSize = true;
            lblPersonajes->Location = Point(10, 255);
            panelContenido->Controls->Add(lblPersonajes);

            Label^ lblPersonajesTexto = gcnew Label();
            lblPersonajesTexto->Text =
                L"HÉROE 1 - Rápido pero frágil\n" +
                L"  • Velocidad: Alta\n" +
                L"  • Vidas: 5\n\n" +
                L"HÉROE 2 - Lento pero resistente\n" +
                L"  • Velocidad: Baja\n" +
                L"  • Vidas: 8";
            lblPersonajesTexto->Font = gcnew Drawing::Font("Arial", 10.0f);
            lblPersonajesTexto->AutoSize = true;
            lblPersonajesTexto->Location = Point(10, 280);
            panelContenido->Controls->Add(lblPersonajesTexto);

            // Objetivo
            Label^ lblObjetivo = gcnew Label();
            lblObjetivo->Text = L"🎯 OBJETIVO";
            lblObjetivo->Font = gcnew Drawing::Font("Arial", 12.0f, FontStyle::Bold);
            lblObjetivo->AutoSize = true;
            lblObjetivo->Location = Point(10, 390);
            panelContenido->Controls->Add(lblObjetivo);

            Label^ lblObjetivoTexto = gcnew Label();
            lblObjetivoTexto->Text =
                L"• Sobrevive el tiempo requerido en cada nivel\n" +
                L"• Evita a los enemigos o colisiona estratégicamente\n" +
                L"• Encuentra y entra al portal para avanzar\n" +
                L"• Completa los 3 niveles para ganar";
            lblObjetivoTexto->Font = gcnew Drawing::Font("Arial", 10.0f);
            lblObjetivoTexto->AutoSize = true;
            lblObjetivoTexto->Location = Point(10, 415);
            panelContenido->Controls->Add(lblObjetivoTexto);

            // Botón cerrar
            Button^ btnCerrar = gcnew Button();
            btnCerrar->Text = L"CERRAR";
            btnCerrar->Location = Point(230, 415);
            btnCerrar->Size = Drawing::Size(120, 35);
            btnCerrar->Font = gcnew Drawing::Font("Arial", 10.0f, FontStyle::Bold);
            btnCerrar->BackColor = Color::FromArgb(0, 120, 215);
            btnCerrar->ForeColor = Color::White;
            btnCerrar->FlatStyle = FlatStyle::Flat;
            btnCerrar->FlatAppearance->BorderSize = 0;
            btnCerrar->Cursor = Cursors::Hand;
            btnCerrar->Click += gcnew EventHandler(this, &MenuPrincipal::btnCerrarAyuda_Click);
            btnCerrar->Tag = ventanaAyuda; // Guardamos referencia a la ventana
            ventanaAyuda->Controls->Add(btnCerrar);

            ventanaAyuda->ShowDialog();
        }

        void btnCerrarAyuda_Click(Object^ sender, EventArgs^ e) {
            Button^ btn = safe_cast<Button^>(sender);
            Form^ ventana = safe_cast<Form^>(btn->Tag);
            ventana->Close();
        }
    };
}