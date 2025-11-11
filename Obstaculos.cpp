#include "Obstaculos.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

Obstaculos::Obstaculos() {
    for (int i = 0; i < MAX_CAJAS; i++) cajaActiva[i] = false;
    velocidad = 1;
    srand(time(0));
}

void Obstaculos::dibujarCaja(int y, int x) {
    moverCursor(y, x); cout << " [===] ";
    moverCursor(y + 1, x); cout << " [===] ";
}

void Obstaculos::borrarCaja(int y, int x) {
    moverCursor(y, x); cout << "        ";
    moverCursor(y + 1, x); cout << "        ";
}

// **CREA 2 CAJAS**: 1 en motoY + 1 al azar
void Obstaculos::crearCaja(int motoY) {
    // === CAJA 1: SIEMPRE en la misma altura que la moto ===
    for (int i = 0; i < MAX_CAJAS; i++) {
        if (!cajaActiva[i]) {
            cajaX[i] = 70; // Desde la derecha
            cajaY[i] = motoY; // ¡OBLIGATORIA: misma Y que moto!
            cajaActiva[i] = true;
            break;
        }
    }
    // === CAJA 2: POSICIÓN ALEATORIA cerca de la moto ===
    for (int i = 0; i < MAX_CAJAS; i++) {
        if (!cajaActiva[i]) {
            cajaX[i] = 70;
            cajaY[i] = motoY + (rand() % 9 - 4); // Rango: motoY-4 a motoY+4
            if (cajaY[i] < 9) cajaY[i] = 9; // No sale de pantalla
            if (cajaY[i] > 19) cajaY[i] = 19;
            cajaActiva[i] = true;
            break;
        }
    }
}

bool Obstaculos::moverYColision(const Moto& moto, int& score, int multiplicador) {
    for (int i = 0; i < MAX_CAJAS; i++) {
        if (!cajaActiva[i]) continue;
        borrarCaja(cajaY[i], cajaX[i]);
        cajaX[i] -= velocidad;
        // +10 × mult si esquivas
        if (cajaX[i] + 6 < moto.getX() && cajaX[i] + 6 + velocidad >= moto.getX()) {
            score += 10 * multiplicador;
            moverCursor(25, 2);
            cout << "+ " << (10 * multiplicador) << " pts! ";
        }
        if (cajaX[i] < 0) {
            cajaActiva[i] = false;
            continue;
        }
        dibujarCaja(cajaY[i], cajaX[i]);
        // Colisión
        if (cajaY[i] >= moto.getY() - 1 && cajaY[i] <= moto.getY() + 1 &&
            cajaX[i] + 5 >= moto.getX() && cajaX[i] <= moto.getX() + 6) {
            return true;
        }
    }
    return false;
}