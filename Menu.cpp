#include "Menu.h"
#include <conio.h>
#include <iostream>
#include <string>
using namespace std;

// Muestra el menú con flechas
void Menu::mostrarOpciones(int opcion) {
    system("cls");
    cout << "==============================================================" << endl;
    cout << "                          MOTO WHEELIE               " << endl;
    cout << "==============================================================" << endl << endl;
    cout << " Usa las flechas ↑ y ↓ para moverte. ENTER para elegir.\n\n";

    string opciones[4] = {
        "1. Iniciar juego",
        "2. Ver ranking",
        "3. Controles",
        "4. Salir"
    };

    for (int i = 0; i < 4; i++) {
        if (i == opcion)
            cout << " > " << opciones[i] << " <" << endl;
        else
            cout << "   " << opciones[i] << endl;
    }
}

// Muestra los controles del juego
void Menu::mostrarControles() {
    system("cls");
    cout << "==============================================================" << endl;
    cout << "                   CONTROLES DEL JUEGO                      " << endl;
    cout << "==============================================================" << endl << endl;
    cout << " W  - Mover hacia arriba" << endl;
    cout << " S  - Mover hacia abajo" << endl;
    cout << " ESPACIO - Activar/desactivar llanteo (x3 puntos)" << endl;
    cout << " ESC - Salir del juego" << endl << endl;
    cout << "Presiona cualquier tecla para volver...";
    _getch();
}

void Menu::mostrar() {
    int opcion = 0;
    while (true) {
        mostrarOpciones(opcion);

        int tecla = _getch();
        if (tecla == 224) { // Flechas
            tecla = _getch();
            if (tecla == 72) opcion = (opcion - 1 + 4) % 4; // Arriba
            if (tecla == 80) opcion = (opcion + 1) % 4;     // Abajo
        }
        else if (tecla == 13) { // ENTER
            if (opcion == 0) {
                Juego juego;
                juego.loop();
            }
            else if (opcion == 1) Ranking::mostrar();
            else if (opcion == 2) mostrarControles();
            else if (opcion == 3) break;
        }
    }
}