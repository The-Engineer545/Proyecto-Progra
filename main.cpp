#include "Menu.h"
#include <windows.h>
#include <iostream>
using namespace std;

int main() {
    // Forzar UTF-8 para que se vean las flechas
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    system("chcp 65001 > nul");

    Menu menu;
    menu.mostrar();

    system("cls");
    cout << "Gracias por jugar Moto Wheelie\n";
    cout << "   Josué & Fabricio - 2025\n";
    Sleep(1500);
    return 0;
}