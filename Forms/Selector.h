#pragma once
#include "../Controladores/GameStateManager.h"
#include "../Controladores/GameConfig.h"
#include "Nivel1.h"

namespace JuegoFinal {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Selector : public System::Windows::Forms::Form
	{
	public:
		Selector(void)
		{
			InitializeComponent();
			// El código de inicialización ahora está dentro de InitializeComponent
			// para que el diseñador lo reconozca.
		}

	protected:
		~Selector()
		{
			if (components)
			{
				delete components;
			}
		}

		// --- VARIABLES DE CONTROLES (Gestionadas por el editor) ---
	private:
		System::Windows::Forms::Label^ lblTitulo;
		System::Windows::Forms::Button^ btnHero1;
		System::Windows::Forms::Button^ btnHero2;
		System::Windows::Forms::Button^ btnVolver;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lblTitulo = (gcnew System::Windows::Forms::Label());
			this->btnHero1 = (gcnew System::Windows::Forms::Button());
			this->btnHero2 = (gcnew System::Windows::Forms::Button());
			this->btnVolver = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// lblTitulo
			// 
			this->lblTitulo->AutoSize = true;
			this->lblTitulo->BackColor = System::Drawing::Color::Transparent;
			this->lblTitulo->Font = (gcnew System::Drawing::Font(L"Arial", 28, System::Drawing::FontStyle::Bold));
			this->lblTitulo->ForeColor = System::Drawing::Color::White;
			// Centrado aproximado (puedes ajustarlo visualmente después)
			this->lblTitulo->Location = System::Drawing::Point(420, 50);
			this->lblTitulo->Name = L"lblTitulo";
			this->lblTitulo->Size = System::Drawing::Size(350, 44);
			this->lblTitulo->TabIndex = 0;
			this->lblTitulo->Text = L"ELIGE TU HÉROE";
			// 
			// btnHero1
			// 
			this->btnHero1->BackColor = System::Drawing::Color::LightSkyBlue;
			this->btnHero1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnHero1->Font = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Bold));
			this->btnHero1->Location = System::Drawing::Point(150, 150);
			this->btnHero1->Name = L"btnHero1";
			this->btnHero1->Size = System::Drawing::Size(300, 400);
			this->btnHero1->TabIndex = 1;
			this->btnHero1->Text = L"HÉROE 1\n(Rápido)";
			this->btnHero1->UseVisualStyleBackColor = false;
			this->btnHero1->Click += gcnew System::EventHandler(this, &Selector::btnHero1_Click);
			// 
			// btnHero2
			// 
			this->btnHero2->BackColor = System::Drawing::Color::LightGreen;
			this->btnHero2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnHero2->Font = (gcnew System::Drawing::Font(L"Arial", 14, System::Drawing::FontStyle::Bold));
			this->btnHero2->Location = System::Drawing::Point(750, 150); // Ajustado para 1200 ancho
			this->btnHero2->Name = L"btnHero2";
			this->btnHero2->Size = System::Drawing::Size(300, 400);
			this->btnHero2->TabIndex = 2;
			this->btnHero2->Text = L"HÉROE 2\n(Tanque)";
			this->btnHero2->UseVisualStyleBackColor = false;
			this->btnHero2->Click += gcnew System::EventHandler(this, &Selector::btnHero2_Click);
			// 
			// btnVolver
			// 
			this->btnVolver->BackColor = System::Drawing::Color::Gray;
			this->btnVolver->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btnVolver->ForeColor = System::Drawing::Color::White;
			this->btnVolver->Location = System::Drawing::Point(500, 600);
			this->btnVolver->Name = L"btnVolver";
			this->btnVolver->Size = System::Drawing::Size(200, 50);
			this->btnVolver->TabIndex = 3;
			this->btnVolver->Text = L"VOLVER";
			this->btnVolver->UseVisualStyleBackColor = false;
			this->btnVolver->Click += gcnew System::EventHandler(this, &Selector::btnVolver_Click);
			// 
			// Selector
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Black;
			// Tamaño fijado desde GameConfig
			this->ClientSize = System::Drawing::Size(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT);
			this->Controls->Add(this->btnVolver);
			this->Controls->Add(this->btnHero2);
			this->Controls->Add(this->btnHero1);
			this->Controls->Add(this->lblTitulo);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"Selector";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Selección de Personaje";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// --- LOGICA DEL JUEGO (Eventos) ---
	private:
		System::Void btnHero1_Click(System::Object^ sender, System::EventArgs^ e) {
			iniciarNivel(1);
		}

	private:
		System::Void btnHero2_Click(System::Object^ sender, System::EventArgs^ e) {
			iniciarNivel(2);
		}

	private:
		System::Void btnVolver_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Close();
		}

		// Función auxiliar para iniciar el nivel
		void iniciarNivel(int heroType) {
			GameStateManager::getInstance()->selectedHero = heroType;
			GameStateManager::getInstance()->resetGame();

			Nivel1^ nivel = gcnew Nivel1();

			// Transición invisible
			nivel->StartPosition = FormStartPosition::Manual;
			nivel->Location = this->Location; // Mantiene la posición de la ventana

			this->Hide();
			nivel->ShowDialog();

			delete nivel;
			this->Close(); // Cierra el selector al volver del juego
		}
	};
}