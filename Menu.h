#pragma once
#include "Juego.h"
#include "Ranking.h"
#include <string>
#include <vector>
/* ========================================
                MENÚ PRINCIPAL
   ========================================*/

class Menu {
public:
    void mostrar();
private:
    void mostrarControles();
    void mostrarOpciones(int opcion);
}; 
