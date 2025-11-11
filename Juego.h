#pragma once
#include "Moto.h"
#include "Obstaculos.h"
#include "Ranking.h"
#include <windows.h>   // ← para Sleep()
#include <conio.h>     // ← para _kbhit() y _getch()
#include <algorithm>   // ← para min()



/* ========================================
          FUNCIÓN PRINCIPAL DEL JUEGO
   ========================================*/

class Juego {
private:
    Moto moto;
    Obstaculos obstaculos;
    int score, multiplicador;
    int framesContadorNivel, framesParaSubirNivel;
    int cajaVelocidad, SPAWN_INTERVALO;
    int frame, frameCajaSpawn;

    // FUNCIÓN MODIFICADA:
    void actualizarScore(bool modoLlanteo);
    void dibujarCarretera();
    void dibujarUI();

public:
    Juego();
    void loop();
};