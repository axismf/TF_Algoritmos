#pragma once

using namespace System::Drawing;

class CollisionMap {
private:
    int murosX[50];
    int murosY[50];
    int murosAncho[50];
    int murosAlto[50];
    int cantidadMuros;

public:
    CollisionMap() {
        cantidadMuros = 0;
    }

    ~CollisionMap() {
    }

    void agregarMuro(int x, int y, int ancho, int alto) {
        if (cantidadMuros < 50) {
            murosX[cantidadMuros] = x;
            murosY[cantidadMuros] = y;
            murosAncho[cantidadMuros] = ancho;
            murosAlto[cantidadMuros] = alto;
            cantidadMuros++;
        }
    }

    bool hayColision(int x, int y, int ancho, int alto) {
        for (int i = 0; i < cantidadMuros; i++) {
            // Verificar si los rectangulos se intersectan
            if (x < murosX[i] + murosAncho[i] &&
                x + ancho > murosX[i] &&
                y < murosY[i] + murosAlto[i] &&
                y + alto > murosY[i]) {
                return true; // Hay colision
            }
        }
        return false; // No hay colision
    }

    void dibujarMuros(Graphics^ g) {
        // Brush translucido para ver las colisiones mientras ajustas
        SolidBrush^ brush = gcnew SolidBrush(Color::FromArgb(100, 255, 0, 0)); // Rojo semi-transparente
        Pen^ pen = gcnew Pen(Color::Red, 2.0f);

        for (int i = 0; i < cantidadMuros; i++) {
            g->FillRectangle(brush, murosX[i], murosY[i], murosAncho[i], murosAlto[i]);
            g->DrawRectangle(pen, murosX[i], murosY[i], murosAncho[i], murosAlto[i]);
        }

        delete brush;
        delete pen;
    }

    void cargarMapaTutorial() {
        cantidadMuros = 0;

        // PAREDES EXTERIORES (bordes del mapa)
        agregarMuro(40, 215, 300, 160);          // Arriba Izq
        agregarMuro(340, 212, 444, 44);          // Arriba Centro
        agregarMuro(784, 213, 350, 110);        // Arriba Derecha


        agregarMuro(0, 448, 800, 30);        // Abajo izq
        agregarMuro(668, 413, 800, 30);        // Abajo der
        agregarMuro(5, 378, 30, 100);           // Izquierda

        agregarMuro(1151, 240, 30, 200);           // Der
       

    
    }
};