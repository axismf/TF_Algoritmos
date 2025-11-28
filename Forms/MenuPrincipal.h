#pragma once
#include "SelectCharacterForm.h" 

namespace JuegoFinal {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MenuPrincipal : public Form
    {
    public:
        MenuPrincipal(void)
        {
            this->Text = L"Menu Principal";
            this->Size = Drawing::Size(800, 600);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;

            Button^ btnJugar = gcnew Button();
            btnJugar->Text = L"JUGAR";
            btnJugar->Location = Point(300, 250);
            btnJugar->Size = Drawing::Size(200, 50);
            btnJugar->Click += gcnew EventHandler(this, &MenuPrincipal::btnJugar_Click);
            this->Controls->Add(btnJugar);

            Button^ btnSalir = gcnew Button();
            btnSalir->Text = L"SALIR";
            btnSalir->Location = Point(300, 320);
            btnSalir->Size = Drawing::Size(200, 50);
            btnSalir->Click += gcnew EventHandler(this, &MenuPrincipal::btnSalir_Click);
            this->Controls->Add(btnSalir);
        }

    private:
        void btnJugar_Click(Object^ sender, EventArgs^ e) {
            SelectCharacterForm^ selectForm = gcnew SelectCharacterForm();
            selectForm->ShowDialog();
        }

        void btnSalir_Click(Object^ sender, EventArgs^ e) {
            Application::Exit();
        }
    };
}