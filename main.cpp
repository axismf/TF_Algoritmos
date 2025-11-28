#include "Forms/MenuPrincipal.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew JuegoFinal::MenuPrincipal());
    return 0;
}