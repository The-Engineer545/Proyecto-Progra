#include "Moto.h"
#include <iostream>
using namespace std;

/* ========================================
            DIBUJO DE MOTOS
   ========================================*/

   // Moto en modo normal
void dibujarMotoNormal(int y, int x) {
    moverCursor(y, x);     cout << " | ";
    moverCursor(y + 1, x); cout << " o----o";
}

// Moto en modo Llanteo (más agresiva)
void dibujarMotoLlanteo(int y, int x) {
    moverCursor(y, x);     cout << " <=/o ";
    moverCursor(y + 1, x); cout << " {/o ";
}

Moto::Moto() : y(10), x(30), turbo(false), yAnterior(10), turboAnterior(false) {}

void Moto::actualizar(int nuevaY, bool nuevoTurbo) {
    yAnterior = y;
    turboAnterior = turbo;
    y = nuevaY;
    turbo = nuevoTurbo;
}

void Moto::borrarAnterior() {
    // Borra cualquier rastro de moto (cubre el tamaño mayor)
    if (y != yAnterior || turbo != turboAnterior) {
        moverCursor(yAnterior, x);     cout << "       "; // 7 espacios
        moverCursor(yAnterior + 1, x); cout << "       ";
    }
}

void Moto::dibujar() {
    // Dibuja la moto según el modo
    if (turbo)
        dibujarMotoLlanteo(y, x);
    else
        dibujarMotoNormal(y, x);
}