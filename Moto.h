#pragma once
#include "utils.h"
#include <string>

/* ========================================
                CLASE MOTO
   ========================================*/

class Moto {
private:
    int y, x;
    bool turbo;
    int yAnterior;
    bool turboAnterior;

public:
    Moto();
    void actualizar(int nuevaY, bool nuevoTurbo);
    void borrarAnterior();
    void dibujar();
    int getY() const { return y; }
    int getX() const { return x; }
    bool getTurbo() const { return turbo; }
};