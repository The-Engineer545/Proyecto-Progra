#pragma once
#include "utils.h"
#include "Moto.h"

/* ========================================
       OBSTÁCULOS: CAJAS (2 POR SPAWN)
   ========================================*/

class Obstaculos {
private:
    static const int MAX_CAJAS = 10;
    int cajaX[MAX_CAJAS];
    int cajaY[MAX_CAJAS];
    bool cajaActiva[MAX_CAJAS];
    int velocidad;

    void dibujarCaja(int y, int x);
    void borrarCaja(int y, int x);

public:
    Obstaculos();
    void crearCaja(int motoY);
    bool moverYColision(const Moto& moto, int& score, int multiplicador);
    void setVelocidad(int v) { velocidad = v; }
};