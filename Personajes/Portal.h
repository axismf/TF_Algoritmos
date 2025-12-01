#pragma once

using namespace System::Drawing;

class Portal {
private:
    int x, y;
    int width, height;
    int animationFrame;
    bool isActive;
    bool visible; // Nuevo atributo

public:
    Portal(int xPos, int yPos) {
        x = xPos;
        y = yPos;
        width = 80;
        height = 100;
        animationFrame = 0;
        isActive = false;
        visible = true; // Visible por defecto
    }

    ~Portal() {}

    void activate() {
        isActive = true;
    }

    // Nuevo método para controlar visibilidad
    void setVisible(bool v) {
        visible = v;
    }

    bool getIsActive() {
        return isActive;
    }

    void draw(Graphics^ g) {
        // Si no está activo O no es visible, no dibujar
        if (!isActive || !visible) return;

        // Animación del portal (efecto de rotación)
        animationFrame++;
        if (animationFrame > 360) animationFrame = 0;

        // Círculos concéntricos animados
        int centerX = x + width / 2;
        int centerY = y + height / 2;

        // Efecto de resplandor
        for (int i = 3; i > 0; i--) {
            int radius = 30 + i * 10 + (animationFrame % 20);
            int alpha = 100 - (i * 30);
            Color glowColor = Color::FromArgb(alpha, 138, 43, 226); // Púrpura
            SolidBrush^ glowBrush = gcnew SolidBrush(glowColor);
            g->FillEllipse(glowBrush,
                centerX - radius,
                centerY - radius,
                radius * 2,
                radius * 2);
            delete glowBrush;
        }

        // Portal principal (anillo giratorio)
        Pen^ portalPen = gcnew Pen(Color::MediumPurple, 5.0f);
        g->DrawEllipse(portalPen, x, y, width, height);
        delete portalPen;

        // Círculo interior
        SolidBrush^ innerBrush = gcnew SolidBrush(Color::FromArgb(150, 75, 0, 130));
        g->FillEllipse(innerBrush,
            x + 15,
            y + 15,
            width - 30,
            height - 30);
        delete innerBrush;

        // Partículas giratorias
        for (int i = 0; i < 8; i++) {
            double angle = (animationFrame + i * 45) * 3.14159 / 180.0;
            int particleX = centerX + (int)(30 * System::Math::Cos(angle));
            int particleY = centerY + (int)(30 * System::Math::Sin(angle));

            SolidBrush^ particleBrush = gcnew SolidBrush(Color::Cyan);
            g->FillEllipse(particleBrush, particleX - 3, particleY - 3, 6, 6);
            delete particleBrush;
        }

        // Texto "PORTAL"
        System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 12.0f, FontStyle::Bold);
        SolidBrush^ textBrush = gcnew SolidBrush(Color::White);
        g->DrawString("PORTAL", font, textBrush, (float)(x + 10), (float)(y + height + 5));
        delete font;
        delete textBrush;
    }

    Rectangle getRectangle() {
        return Rectangle(x, y, width, height);
    }

    int getX() { return x; }
    int getY() { return y; }
};