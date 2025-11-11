#include "Juego.h"
#include <conio.h>
#include <iostream>
#include <algorithm>
#include <windows.h>
using namespace std;

/* ========================================
            PUNTUACIÓN POR TIEMPO
   ========================================*/

   // FUNCIÓN MODIFICADA:
void Juego::actualizarScore(bool modoLlanteo) {
    framesContadorNivel++;
    if (framesContadorNivel >= framesParaSubirNivel) {
        multiplicador++;
        framesContadorNivel = 0;
        cajaVelocidad = multiplicador / 2 + 1;
        // REDUCIR SPAWN INTERVALO
        if (SPAWN_INTERVALO > 15) {
            SPAWN_INTERVALO -= 3;
            if (SPAWN_INTERVALO < 15) SPAWN_INTERVALO = 15;
        }
    }
    if (frame % 8 == 0) {
        int puntosBase = modoLlanteo ? 3 : 1;
        score += puntosBase * multiplicador;
    }
}

void Juego::dibujarCarretera() {
    // --- ANIMACIÓN DE CARRETERA (líneas centrales móviles) ---
    moverCursor(14, 0);
    if (frame % 2 == 0) {
        cout << " =======                  =======                   =======            " << endl << endl;
    }
    else {
        cout << "              =======                 =======                   =======" << endl << endl;
    }
}

void Juego::dibujarUI() {
    // --- MOSTRAR SCORE ---
    moverCursor(2, 2);
    cout << "SCORE: " << score << " pts ";

    // --- MOSTRAR MULTIPLICADOR ---
    moverCursor(2, 50);
    cout << "MULT: x" << multiplicador << " ";

    // --- MARCO INFERIOR (fijo) ---
    moverCursor(22, 0);
    cout << "==================================================================";
    
    // --- INFO EN PANTALLA ---
    moverCursor(27, 2);
    cout << "W=arriba S=abajo: Mover | ESPACIO: Llatear (" << (moto.getTurbo() ? "ON " : "OFF") << ") | ESC: Salir";
}

Juego::Juego() {
    score = 0;
    multiplicador = 1;
    framesContadorNivel = 0;
    framesParaSubirNivel = 80; // Cada 10 segundos
    cajaVelocidad = 1;
    SPAWN_INTERVALO = 30; // ~3.75 segundos
    frame = 0;
    frameCajaSpawn = 0;
    ocultarCursor();
}

void Juego::loop() {
    system("cls");
    cout << "\t\t\t\t\t\t\t\t========================================" << endl;
    cout << "\t\t\t\t\t\t\t\t Moto Wheelie " << endl;
    cout << "\t\t\t\t\t\t\t\t========================================" << endl << endl << endl;
    // --- MARCO SUPERIOR ---
    cout << "==================================================================" << endl;

    /* ========================================
               BUCLE PRINCIPAL DEL JUEGO
       ========================================*/

    int limiteSuperior = 6;
    int limiteInferior = 20;
    int posicionY = 10;
    bool turbo = false;

    while (true) {
        // --- 1. ENTRADA DEL TECLADO ---
        if (_kbhit()) {
            char tecla = _getch();
            if (tecla == 'w' || tecla == 'W') {
                if (posicionY > limiteSuperior) posicionY--;
            }
            else if (tecla == 's' || tecla == 'S') {
                if (posicionY < limiteInferior) posicionY++;
            }
            else if (tecla == ' ') {
                turbo = !turbo; // Alternar turbo llanteo
            }
            else if (tecla == 27) { // ESC = Salir
                break;
            }
        }

        moto.actualizar(posicionY, turbo);
        moto.borrarAnterior();
        moto.dibujar();

        actualizarScore(turbo);
        obstaculos.setVelocidad(cajaVelocidad);

        // --- GENERAR NUEVA CAJA ---
        frameCajaSpawn++;
        if (frameCajaSpawn >= SPAWN_INTERVALO) {
            obstaculos.crearCaja(posicionY);
            frameCajaSpawn = 0;
        }

        // --- MOVER CAJAS Y COMPROBAR COLISIÓN ---
        if (obstaculos.moverYColision(moto, score, multiplicador)) {
            moverCursor(25, 2);
            cout << "¡CHOQUE! GAME OVER ";
            Sleep(1500);
            break;
        }

        dibujarCarretera();
        dibujarUI();

        // --- CONTROL DE VELOCIDAD ---
        frame++;
        Sleep(120); // ~8 FPS
    }

    // --- LIMPIAR PANTALLA AL SALIR ---
    system("cls");
    cout << "Juego terminado Puntuacion final: " << score << " pts" << endl;
    // --- PEDIR NOMBRE ---
    string nombre;
    cout << "Ingresa tu nombre (max 10 letras): ";
    getline(cin, nombre);
    if (nombre.empty()) nombre = "Anonimo";
    if (nombre.length() > 10) nombre = nombre.substr(0, 10);

    Ranking::agregarYGuardar(score, nombre);

    // --- MOSTRAR TOP 10 ---
    auto ranking = Ranking::cargar();
    cout << "\n=== TOP 10 GLOBAL ===" << endl;
    int tuPosicion = -1;
    for (int i = 0; i < min(10, (int)ranking.size()); i++) {
        if (ranking[i].nombre == nombre && ranking[i].puntos == score) {
            tuPosicion = i + 1;
            cout << "[" << (i + 1) << "] * " << ranking[i].nombre << " - " << ranking[i].puntos << " pts" << endl;
        }
        else {
            cout << (i + 1) << ". " << ranking[i].nombre << " - " << ranking[i].puntos << " pts" << endl;
        }
    }

    // --- MENSAJE FINAL ---
    if (tuPosicion != -1 && tuPosicion <= 3) {
        cout << "\nTOP 3! ¡ÉLITE!" << endl;
    }
    else if (tuPosicion != -1 && tuPosicion <= 5) {
        cout << "\nTOP 5! ¡Excelente!" << endl;
    }
    else if (tuPosicion != -1) {
        cout << "\nTOP 10! ¡Entra al ranking!" << endl;
    }
    else {
        cout << "\n¡Sigue jugando para entrar al TOP 10!" << endl;
    }
    cout << "\n¡Gracias por jugar Moto Wheelie! - Josué & Fabricio" << endl;
    _getch();
}