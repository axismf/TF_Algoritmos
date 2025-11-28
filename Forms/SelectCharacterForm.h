#pragma once
#include "../Controladores/GameStateManager.h"
#include "Nivel1.h"  

namespace JuegoFinal {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SelectCharacterForm : public Form
    {
    public:
        SelectCharacterForm(void)
        {
            // ... código del constructor igual ...
        }

    private:
        void btnHero1_Click(Object^ sender, EventArgs^ e) {
            GameStateManager^ gameState = GameStateManager::getInstance();
            gameState->selectedHero = 1;
            gameState->resetGame();

            this->Hide();
            Nivel1^ nivel1 = gcnew Nivel1();  // ⬅️ Nivel1
            nivel1->ShowDialog();
            delete nivel1;
            this->Close();
        }

        void btnHero2_Click(Object^ sender, EventArgs^ e) {
            GameStateManager^ gameState = GameStateManager::getInstance();
            gameState->selectedHero = 2;
            gameState->resetGame();

            this->Hide();
            Nivel1^ nivel1 = gcnew Nivel1();  // ⬅️ Nivel1
            nivel1->ShowDialog();
            delete nivel1;
            this->Close();
        }

        void btnVolver_Click(Object^ sender, EventArgs^ e) {
            this->Close();
        }
    };
}
